#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{


	//spot light, point light
#if 1
	//�P�@VP=��������s�N�Z���ւ̐��K���x�N�g��
	float3	litPixelVec = normalize(In.WorldPosition.xyz - Light.Position.xyz);
	//�Q�@angle=���C�g�̃x�N�g����VP�Ƃ̊p�x
	float	angle = acos(dot(litPixelVec.xyz, Light.Direction.xyz));
	//�R�@spot=�͈͓��ł̃s�N�Z���̖��邳 �p�x���傫���قǌ�������
	float	spot = pow(saturate(1.0f - (1.0f / Light.Angle.x) * abs(angle)), 1.0f / 1.0f);
	//float	spot = step(abs(angle), Light.Angle.x);
	//�S�@========����������Ƃ��Ƃ̃s�N�Z���P�ʂ̌����v�Z+��===========
#endif


	//light and specular
#if 1
	//�����ł̐F�����ʂ̃e�N�X�`�������_�F���쐬���Ă���
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

	//��������
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

	//�X�y�L�����̌v�Z
	float3 eyePixelDir = In.WorldPosition.xyz - Camera.Position.xyz;
	eyePixelDir = normalize(eyePixelDir); //���K������
	float3 refDir = reflect(Light.Direction.xyz, normal);
	refDir = normalize(refDir); //���K������
	float specular = -dot(eyePixelDir, refDir); //���ʔ��˂̌v�Z
	specular = saturate(specular); //�l���T�`�����[�g
	specular = pow(specular, 20); //�����ł�20�悵�Ă݂�

	//�T�@�X�|�b�g���C�g�͈̔͂��l�����Čv�Z����悤�ɕύX
	diffuse.rgb *= spot;

	//����
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
	In.ShadowPosition.xyz /= In.ShadowPosition.w; //���e�ʂł̃s�N�Z���̍��W����
	In.ShadowPosition.x = (In.ShadowPosition.x + 1.0f) * 0.5f; //�e�N�X�`�����W�ɕϊ�
	In.ShadowPosition.y = -(In.ShadowPosition.y - 1.0f) * 0.5f; //Y�͕����𔽓]���Ă���

	//�V���h�E�}�b�v�e�N�X�`�����A���C�g�J��������s�N�Z���܂ł̋����i�[�x�l�j���擾
	float depth = g_TextureShadowDepth.Sample(g_SamplerState,In.ShadowPosition.xy);

	//�擾�l���v�Z��̃s�N�Z���ւ̋�����菬����
	if (depth < In.ShadowPosition.z-0.01f) //0.01��Z�t�@�C�e�B���O�␳�l�i��q�j
	{
		float litPixelDist = length(Light.Position.xyz - In.WorldPosition.xyz);
		float ratio = saturate( litPixelDist / 20.0f);
		outDiffuse.rgb *= ratio; //�F���Â�����
		outDiffuse.rgb *= Light.Ambient.rgb * (1 - ratio);
	}
	else
	{
		//�U�@�X�y�L�����l���f�t���[�Y�Ƃ��đ�������
		outDiffuse.rgb += (specular * spot);
	}

	outDiffuse.a *= In.Diffuse.a; //���ʌv�Z

#endif
}


