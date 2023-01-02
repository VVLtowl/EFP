#include "main.h"
#include "renderer.h"
#include "resource.h"
#include "drawManager.h"
#include "GameObject.h"
#include "PolygonUI.h"

void PolygonUI::Draw()
{	
	//anime pic slide
	{
		float x = 0;
		float y = 0;
		float w = 1;
		float h = 1;

		Transform3D* trans = GetGameObject()->GetTransform();
		float leftTopX = trans->GetPosition().x;
		float leftTopY = trans->GetPosition().y;
		float z = trans->GetPosition().z;
		float width = Size.x;
		float height = Size.y;

		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(
			m_VertexBuffer,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&msr
		);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = { leftTopX,leftTopY,z };
		vertex[0].Normal = { 0,1,0 };
		vertex[0].Diffuse = Color;
		vertex[0].TexCoord = { x,y };

		vertex[1].Position = { leftTopX + width,leftTopY,z };
		vertex[1].Normal = { 0,1,0 };
		vertex[1].Diffuse = Color;
		vertex[1].TexCoord = { x + w,y };

		vertex[2].Position = { leftTopX,leftTopY + height,z };
		vertex[2].Normal = { 0,1,0 };
		vertex[2].Diffuse = Color;
		vertex[2].TexCoord = { x,y + h };

		vertex[3].Position = { leftTopX + width,leftTopY + height,z };
		vertex[3].Normal = { 0,1,0 };
		vertex[3].Diffuse = Color;
		vertex[3].TexCoord = { x + w,y + h };

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	}

	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	Renderer::SetWorldViewProjection2D();

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Renderer::GetDeviceContext()->Draw(4, 0);
}

PolygonUI::PolygonUI(GameObject* owner, const PolygonUIDescription& polygonUIDesc, int order):
	DrawObject(owner,polygonUIDesc.DrawObjDesc,order)
{
	Size = polygonUIDesc.Size;
	Color = polygonUIDesc.Color;
	Texture = TextureFactory::Load(polygonUIDesc.TextureName);

	//四角プリゴン
	VERTEX_3D vertex[4];
	float width = Size.x;
	float height = Size.y;

	//左上の頂点
	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = Color;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//右上の頂点
	vertex[1].Position = D3DXVECTOR3(width, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = Color;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	//左下の頂点
	vertex[2].Position = D3DXVECTOR3(0.0f, height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = Color;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	//右下の頂点
	vertex[3].Position = D3DXVECTOR3(width, height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = Color;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

PolygonUI::~PolygonUI()
{
	m_VertexBuffer->Release();
}
