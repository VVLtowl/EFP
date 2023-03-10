#pragma once
#include "Component.h"

/*********************************************************
* @brief	カメラ対象を作るための説明
********************************************************/
struct CameraDescription
{
	CAMERA CameraData;
	class Transform3D* LookAtTransform = nullptr;
	float Fovy = 25.0f;
	float Width = 16;
	float Height = 9;
	float ZNear = 1.0f;
	float ZFar = 1000.0f;
};


class Camera :
	public Component
{
public:
	CAMERA CameraData;
	class Transform3D* LookAt;
	float Fovy;
	float Width;
	float Height;
	float ZNear;
	float ZFar;

public:
	void Update()override;
	Camera(
		class GameObject* owner, 
		CameraDescription cmrDesc, 
		int order = COMP_CAMERA);
};

