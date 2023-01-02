#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>

#pragma warning(push)
#pragma warning(disable:4005)
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
#pragma warning(pop)

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")

#include "dlllib/Input.h"
//#pragma comment (lib, "IInput.lib")


#include "Math.h"
#include "Collision.h"
#include "debugInfo.h"
#include "renderer.h"
#include "resource.h"
#include "drawManager.h"
#include "colliderManager.h"
#include "lightManager.h"
#include "cameraManager.h"
#include "inputManager.h"
#include "uiSystem.h"
#include "gameObjectManager.h"


#pragma region ========== common macro definition ==========
/*********************************************************
* @brief	ウィンドウサイズ情報
********************************************************/
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const char* const CLASS_NAME = "AppClass";
const char* const WINDOW_NAME = "EFP";

/*********************************************************
* @brief	FPS
********************************************************/
const unsigned int FPS = 60;

#pragma endregion

/*********************************************************
* @brief	ウィンドウのハンドルを取得
********************************************************/
HWND GetWindow();

/*********************************************************
* @brief	FPSを取得
********************************************************/
DWORD GetFrameRate();

