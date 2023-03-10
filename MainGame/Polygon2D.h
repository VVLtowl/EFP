#pragma once

#include "DrawObject.h"
#include <string>

/*********************************************************
* @brief	2D描画対象を作るための説明
********************************************************/
struct Polygon2DDescription
{
	DrawObjectDescription DrawObjDesc;
	D3DXVECTOR2 Size = { 1,1 };
	D3DXVECTOR4 Color = { 1,1,1,1 };
	std::string TextureName = "asset\\texture\\number.dds";//give up
	short TextureID = 0;
};


/*********************************************************
* @brief	四角形のポリゴン
********************************************************/
class Polygon2D:
	public DrawObject
{
private:
	/*********************************************************
	* @brief	描画に必須な要素
	* @details	動的確保する要素
	********************************************************/
	ID3D11Buffer* m_VertexBuffer;

public:
	/*********************************************************
	* @brief	好み設定のできる要素
	********************************************************/
	D3DXVECTOR2 Size = {1,1};
	D3DXVECTOR4 Color = {1,1,1,1};
	ID3D11ShaderResourceView* Texture;

public:
	void Draw()override;
	Polygon2D(
		class GameObject* owner,
		const Polygon2DDescription& polygon2DDesc,
		int order = COMP_POLYGON2D);
	~Polygon2D();
};

