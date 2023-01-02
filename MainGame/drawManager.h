#pragma once

/*********************************************************
* @brief	四角インスタンスの最大数
********************************************************/
const size_t INSTANCE_SQUARE_MAX=10000;

/*********************************************************
* @brief	テキスチャーID
********************************************************/
const short TEXID_NUMBER_0 = 0;
const short TEXID_FIELD004 = 1;
const short TEXID_HINT = 2;
const short TEXID_CIRCLE_0 = 3;

/*********************************************************
* @brief	モデルID
********************************************************/
enum ModelID
{
	MDLID_TORUS,
	MDLID_CUBE,
	MDLID_MAN,

	MDLID_MAX,
};

/*********************************************************
* @brief	シェーダータイプ
********************************************************/
enum ShaderType
{
	SHADER_BLINN,
	SHADER_SHADOW,
	SHADER_UNLIT,
	SHADER_UNLIT_INSTANCE,

	SHADER_MAX,
};

#include "DrawObject.h"
#include <list>
#include <map>

/*********************************************************
* @brief	描画対象　ヘッダー
********************************************************/
#include "Polygon2D.h"
#include "Polygon2DMany.h"
#include "Polygon3D.h"
#include "PolygonUI.h"
#include "DrawLine.h"



class DrawManager
{
	/*********************************************************
	* @brief	描画対象を一斉に管理する
	********************************************************/
private:
	static std::list<DrawObject*> m_DrawObjects[];
public:
	static std::map<short, ID3D11ShaderResourceView*> Textures;
	static std::map<short, Model*> Models;
	static ID3D11Buffer* SquareVertexBuffer;
	static ID3D11Buffer* SquareInstanceBuffer;
	static ID3D11ShaderResourceView* StructuredBufferSRV;

	static ID3D11VertexShader* VertexShader[];
	static ID3D11PixelShader* PixelShader[];
	static ID3D11InputLayout* VertexLayout[];

	static Polygon2DMany* DrawPolygon2DMany;
public:
	static void Load();
	static void Unload();

	static void DrawAll();
	static void DrawShadowDepth();

	static void Register(DrawObject* drawObj);
	static void Quit(DrawObject* drawObj);
};
