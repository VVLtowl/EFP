#pragma once
#include <list>

/*********************************************************
* @brief	カメラ　ヘッダー
********************************************************/
#include "Camera.h"

class CameraManager
{
private:
	static Camera* m_MainCamera;

public:
	static void SetMainCamera(Camera* cmr);
	static Camera* GetMainCamera();
	static void SelectMainCameraView();
};
