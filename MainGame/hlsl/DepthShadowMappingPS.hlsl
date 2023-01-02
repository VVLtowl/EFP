#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{


	//spot light, point light
#if 1
	//１　VP=光源からピクセルへの正規化ベクトル
	float3	litPixelVec = normalize(In.WorldPosition.xyz - Light.Position.xyz);
	//２　angle=ライトのベクトルとVPとの角度
	float	angle = acos(dot(litPixelVec.xyz, Light.Direction.xyz));
	//３　spot=範囲内でのピクセルの明るさ 角度が大きいほど減衰する
	float	spot = pow(saturate(1.0f - (1.0f / Light.Angle.x) * abs(angle)), 1.0f / 1.0f);
	//float	spot = step(abs(angle), Light.Angle.x);
	//４　========ここからもともとのピクセル単位の光源計算+α===========
#endif


	//light and specular
#if 1
	//日向での色＝普通のテクスチャ＊頂点色を作成しておく
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

	//光源処理
	float3 normal = normalize(In.Normal.xyz);
	float light = -dot(normal, Light.Direction.xyz);
	float4 diffuse = light;
	if (light < 0)
	{
		diffuse.rgb = Light.Ambient.rgb;
		diffuse.rgb *= (-light);
	}
	else
	{
		diffuse.rgb *= Light.Diffuse.rgb;
		diffuse.rgb *= light;
	}

	//スペキュラの計算
	float3 eyePixelDir = In.WorldPosition.xyz - Camera.Position.xyz;
	eyePixelDir = normalize(eyePixelDir); //正規化する
	float3 refDir = reflect(Light.Direction.xyz, normal);
	refDir = normalize(refDir); //正規化する
	float specular = -dot(eyePixelDir, refDir); //鏡面反射の計算
	specular = saturate(specular); //値をサチュレート
	specular = pow(specular, 20); //ここでは20乗してみる

	//５　スポットライトの範囲を考慮して計算するように変更
	diffuse.rgb *= spot;

	//環境光
	float3 ambient = Light.Ambient.rgb * Light.Ambient.a;
	diffuse.rgb += ambient;

	//outline
	float cmr = -dot(normal, Camera.Direction.xyz);
	if (cmr < 0.5f)
	{
		//diffuse.rgb *= Light.Ambient.rgb;
		diffuse.rgb *= (0.5f - cmr);
	}

	outDiffuse.rgb *= diffuse.rgb;

	//shadow map
	//xyz/w -> 2D xy square projection, value:(-1~1)
	//3D z -> distance projection, 
	In.ShadowPosition.xyz /= In.ShadowPosition.w; //投影面でのピクセルの座標つくる
	In.ShadowPosition.x = (In.ShadowPosition.x + 1.0f) * 0.5f; //テクスチャ座標に変換
	In.ShadowPosition.y = -(In.ShadowPosition.y - 1.0f) * 0.5f; //Yは符号を反転しておく

	//シャドウマップテクスチャより、ライトカメラからピクセルまでの距離（深度値）を取得
	float depth = g_TextureShadowDepth.Sample(g_SamplerState,In.ShadowPosition.xy);

	//取得値が計算上のピクセルへの距離より小さい
	if (depth < In.ShadowPosition.z-0.01f) //0.01はZファイティング補正値（後述）
	{
		float litPixelDist = length(Light.Position.xyz - In.WorldPosition.xyz);
		float ratio = saturate( litPixelDist / 20.0f);
		outDiffuse.rgb *= ratio; //色を暗くする
		outDiffuse.rgb *= Light.Ambient.rgb * (1 - ratio);
	}
	else
	{
		//６　スペキュラ値をデフューズとして足しこむ
		outDiffuse.rgb += (specular * spot);
	}

	outDiffuse.a *= In.Diffuse.a; //α別計算

#endif
}


