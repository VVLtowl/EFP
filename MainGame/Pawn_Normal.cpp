#include "main.h"
#include "Pawn_Normal.h"

Pawn_Normal::Pawn_Normal()
{
	//create polygon2d
	Polygon2DDescription desc;
	desc.DrawObjDesc.Layer = LAYER_WORLD_SHADOW_ALPHA;
	desc.DrawObjDesc.Shader = SHADER_SHADOW;
	desc.TextureID = TEXID_NUMBER_0;
	desc.DrawObjDesc.DepthEnable = true;
	desc.Size = { 1.5f,1.5f };
	m_Polygon2D = new Polygon2D(this, desc);
}

void Pawn_Normal::UpdateGameObject()
{
	//test
	D3DXMATRIX view =
		CameraManager::GetMainCamera()->CameraData.ViewMatrix;
	m_Transform3D->LookAtView(view);
	//m_Transform3D->LookAt(CameraManager::GetMainCamera()->GetGameObject()->GetTransform()->GetPosition());

}