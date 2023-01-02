#include "main.h"
#include "LookAt.h"
#include "MainCamera.h"

MainCamera::MainCamera()
{
	//other init
	m_Val1 = 0;


	//create camera component
	CameraDescription desc;
	//desc.ZNear = 10;
	//desc.ZFar = 25;
	m_Camera = new Camera(this, desc);

	//create LookAt
	m_LookAt = new LookAt(this);

	//set main camera
	CameraManager::SetMainCamera(m_Camera);

	//create camera polygon
	Polygon3DDescription polyDesc;
	polyDesc.DrawObjDesc.Shader = SHADER_UNLIT;
	//polyDesc.DrawObjDesc.DepthEnable = false;
	polyDesc.ModelID = MDLID_CUBE;
	//m_Polygon3D = new Polygon3D(this, polyDesc);


	//transform init
	m_Transform3D->SetPosition(10, 14, -10);
	//m_Transform3D->SetScale(m_Camera->Width, m_Camera->Height, 1);
}

MainCamera::~MainCamera()
{
	CameraManager::SetMainCamera(nullptr);
}

void MainCamera::UpdateGameObject()
{
	//test
	//make loop move
	D3DXVECTOR3 pos = m_Transform3D->GetPosition();
	m_Val1 -= 0.01f;
	pos.x = 7.0f * sinf(m_Val1);
	m_Transform3D->SetPosition(pos);

	//update render main camera data
	Renderer::SetCamera(m_Camera->CameraData);
}


