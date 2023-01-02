#include "main.h"
#include "MainLight.h"

MainLight::MainLight()
{
	//set rotate speed
	m_RotateSpeed = 180.0f / 240.0f * PI / 180.0f;

	//set position
	m_Transform3D->SetPosition(5, 5, -5);

	//create light component
	LightDescription desc;
	desc.LightData.Diffuse = { 1.0f,1.0f,1,1 };
	desc.LightData.Ambient = { 3.0f,3.0f,3.23f,0.1f };
	desc.ZNear = 1;
	desc.ZFar = 15;
	m_MyLight = new MyLight(this, desc);

	//set main light
	LightManager::SetMainLight(m_MyLight);
}

MainLight::~MainLight()
{
	LightManager::SetMainLight(nullptr);
}

void MainLight::UpdateGameObject()
{
	//test
	//make light move loop
	m_Val1 += 0.01f;
	D3DXVECTOR3 pos = m_Transform3D->GetPosition();
	pos.x = 5.0f * sinf(m_Val1);
	//m_Transform3D->SetPosition(pos);

	//update render main light data
	Renderer::SetLight(m_MyLight->LightData);
}

