#include "main.h"
#include "cameraManager.h"

Camera* CameraManager::m_MainCamera;

void CameraManager::SetMainCamera(Camera* cmr)
{
	m_MainCamera = cmr;
}

Camera* CameraManager::GetMainCamera()
{
	return m_MainCamera;
}

void CameraManager::SelectMainCameraView()
{
	CAMERA camera = m_MainCamera->CameraData;
	Renderer::SetViewMatrix(&camera.ViewMatrix);
	Renderer::SetProjectionMatrix(&camera.ProjectionMatrix);
}
