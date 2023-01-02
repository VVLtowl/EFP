#pragma once

/*********************************************************
* @brief	�l�p�C���X�^���X�̍ő吔
********************************************************/
const size_t INSTANCE_SQUARE_MAX=10000;

/*********************************************************
* @brief	�e�L�X�`���[ID
********************************************************/
const short TEXID_NUMBER_0 = 0;
const short TEXID_FIELD004 = 1;
const short TEXID_HINT = 2;
const short TEXID_CIRCLE_0 = 3;

/*********************************************************
* @brief	���f��ID
********************************************************/
enum ModelID
{
	MDLID_TORUS,
	MDLID_CUBE,
	MDLID_MAN,

	MDLID_MAX,
};

/*********************************************************
* @brief	�V�F�[�_�[�^�C�v
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
* @brief	�`��Ώہ@�w�b�_�[
********************************************************/
#include "Polygon2D.h"
#include "Polygon2DMany.h"
#include "Polygon3D.h"
#include "PolygonUI.h"
#include "DrawLine.h"



class DrawManager
{
	/*********************************************************
	* @brief	�`��Ώۂ���ĂɊǗ�����
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
