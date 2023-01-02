#include "main.h"
#include "renderer.h"
#include "Transform3D.h"
#include "GameObject.h"
#include "Camera.h"

Camera::Camera(class GameObject* owner, CameraDescription cmrDesc, int order):
	Component(owner,order)
{
	CameraData = cmrDesc.CameraData;
	LookAt = cmrDesc.LookAtTransform;
	Fovy = cmrDesc.Fovy;
	Width = cmrDesc.Width;
	Height = cmrDesc.Height;
	ZNear = cmrDesc.ZNear;
	ZFar = cmrDesc.ZFar;
}

void Camera::Update()
{
	Transform3D* trans = GetGameObject()->GetTransform();
	D3DXVECTOR3 pos = trans->GetPosition();
	D3DXVECTOR3 up = V3_AXIS_Y;
	D3DXVECTOR3 forwardPos = pos + trans->GetForward() * 1.0f;
	D3DXVECTOR3 lookAtPos =
		(LookAt == nullptr ? forwardPos : LookAt->GetPosition());
	D3DXVECTOR3 dir = (lookAtPos - pos);
	D3DXVec3Normalize(&dir, &dir);
	pos -= dir * 4;

	CameraData.Direction = D3DXVECTOR4(dir, 0);
	CameraData.Position = D3DXVECTOR4(pos, 0);
	D3DXMatrixLookAtLH(
		&CameraData.ViewMatrix,
		&pos,
		&lookAtPos,
		&up
	);


#if 0
	//Perspective
	D3DXMATRIX* cmrProjection = &Cmr.ProjectionMatrix;
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float radian = m_Fovy * PI / 180.0f;
	D3DXMatrixPerspectiveFovLH(
		&m_Camera.ProjectionMatrix,
		radian,
		aspect,
		ZNear,
		ZFar
	);
#endif

#if 1
	//orthographic
	D3DXMatrixOrthoLH(
		&CameraData.ProjectionMatrix,
		Width,//w
		Height,//h
		ZNear,//near 
		ZFar//far
	);
#endif

}
