#include "main.h"
#include "DepthUI.h"

DepthUI::DepthUI()
{
	//create polygonUI
	PolygonUIDescription desc;
	desc.Size = D3DXVECTOR2(1280, 720)*0.25f;
	m_PolygonUI = new PolygonUI(this, desc);

	//set render shadow depth texture
	m_PolygonUI->Texture = Renderer::m_MainSRV;// Renderer::GetShadowDepthTexture();
}

void DepthUI::UpdateGameObject()
{
}