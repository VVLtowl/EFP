#include "main.h"
#include "renderer.h"
#include "GameObject.h"
#include "Transform3D.h"
#include "MyLight.h"

MyLight::MyLight(GameObject* owner, LightDescription litDesc, int order) :
	Component(owner,order)
{
	LightData = litDesc.LightData;	
	LookAt = litDesc.LookAtTransform;
	Fovy = litDesc.Fovy;
	Width = litDesc.Width;
	Height = litDesc.Height;
	ZNear = litDesc.ZNear;
	ZFar = litDesc.ZFar;
	Angle = litDesc.Angle;
}

void MyLight::Update()
{
	Transform3D* transform = GetGameObject()->GetTransform();

	//ライトカメラのビュー行列を作成
	Transform3D* trans = m_Owner->GetTransform();
	D3DXVECTOR3 pos = trans->GetPosition();
	D3DXVECTOR3 forwardPos = { 0,0,0 };//pos + trans->GetForward() * 10.0f;
	D3DXVECTOR3 lookAtPos =
		(LookAt == nullptr ? forwardPos : LookAt->GetPosition());
	D3DXVECTOR3 up = V3_AXIS_Y;
	D3DXMatrixLookAtLH(
		&LightData.ViewMatrix, 
		&pos, 
		&lookAtPos, 
		&up
	);

	//視錐計算と設定


	//ライトカメラのプロジェクション行列を作成
	D3DXMatrixOrthoLH(
		&LightData.ProjectionMatrix, 
		Width, 
		Height,
		ZNear, 
		ZFar
	);
#if 0
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	D3DXMatrixPerspectiveFovLH(
		&LightData.ProjectionMatrix,
		Fovy,
		aspect,
		ZNear,
		ZFar
	);
#endif

	//compute direction
	D3DXVECTOR3 dir = lookAtPos - pos;
	D3DXVec3Normalize(&dir, &dir);
	LightData.Direction = D3DXVECTOR4(dir, 0);

	//set position
	LightData.Position = D3DXVECTOR4(pos, 1);

	//set angle
	//float radian = Angle * PI / 180.0f;
	float angleX = Angle * PI / 180.0f;// fabsf(cosf(radian));
	LightData.Angle = D3DXVECTOR4(angleX, 1, 1, 1);
}
