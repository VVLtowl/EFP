#pragma once
#include "Component.h"
#include <string>

/*********************************************************
* @brief	�`�惌�C���[
********************************************************/
enum LayerType
{
	LAYER_WORLD_SHADOW_NORMAL,
	LAYER_WORLD_SHADOW_ALPHA,
	LAYER_WORLD_NORMAL,
	LAYER_WORLD_ALPHA,

	LAYER_WORLD_LINE_TOOL,

	LAYER_SCREEN_UI,

	LAYER_MAX,
};

/*********************************************************
* @brief	�`��Ώۂ���邽�߂̐���
********************************************************/
struct DrawObjectDescription
{
	LayerType Layer = LAYER_WORLD_NORMAL;
	ShaderType Shader = SHADER_BLINN;
	bool DepthEnable = true;
};

/*********************************************************
* @brief	��ʂɕ`�悷��Ώ�
********************************************************/
class DrawObject:
	public Component
{
public:
	virtual void Draw() = 0;
	DrawObject(
		class GameObject* owner, 
		const DrawObjectDescription& drawObjDesc,
		int order = COMP_COUNT);
	virtual ~DrawObject();

protected:
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	bool m_DepthEnable;

public:
	LayerType Layer;
};