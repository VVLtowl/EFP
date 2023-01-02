#include "main.h"

#include "resource.h"
#include "drawManager.h"
#include "cameraManager.h"
#include "lightManager.h"
#include "transformManager.h"
#include "gameObjectManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include <time.h>

#include "LookAt.h"
#include "LookAtCamera.h"
#include "TransformAnime.h"
#include "MoveControl.h"
#include "BoxCollider.h"
#include "GameManager.h"

#pragma region ========== prototype declaration ==========
/*********************************************************
* @brief	ウィンドウズプログラムに必要な関数
********************************************************/
// @detail	メッセージ処理でimguiのプロセス更新も行う
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

/*********************************************************
* @brief	imguiに必要な関数：imguiのプロセス更新
********************************************************/
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/*********************************************************
* @brief	メインサイクル
********************************************************/
void Init();
void Update();
void Uninit();
#pragma endregion

#pragma region ========== window ==========
/*********************************************************
* @brief	ウィンドウズインスタンス
********************************************************/
HWND g_Window;
DWORD g_FrameRate;

/*********************************************************
* @brief	ウィンドウ関数定義
********************************************************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

#pragma region ========== create window ==========

		WNDCLASSEX wcex =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WndProc,
			0,
			0,
			hInstance,
			NULL,
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			NULL,
			CLASS_NAME,
			NULL
		};

		RegisterClassEx(&wcex);
		RECT rc = { 0,0,(LONG)SCREEN_WIDTH ,(LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0,
			CLASS_NAME,
			WINDOW_NAME,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rc.right-rc.left,
			//(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
			rc.bottom-rc.top,
			//(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
			NULL,
			NULL,
			hInstance,
			NULL);


		ShowWindow(g_Window, nCmdShow);
		UpdateWindow(g_Window);
#pragma endregion

#pragma region ========== main cycle ==========

		//main init 
		Init();


		//time init
		DWORD dwExecLastTime;
		DWORD dwCurrentTime;
		DWORD dwFPSLastTime;
		DWORD dwFrameCount;
		timeBeginPeriod(1);
		dwFPSLastTime = dwExecLastTime = timeGetTime();
		dwCurrentTime = 0;
		dwFrameCount = 0;


		MSG msg;
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				dwCurrentTime = timeGetTime();

				if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
				{
					dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
					g_FrameRate = dwFrameCount;
					dwFrameCount = 0;							// カウントをクリア
				}

				if ((dwCurrentTime - dwExecLastTime) >= (1000 / FPS))
				{
					//time update
					{
						dwFrameCount++;
						dwExecLastTime = dwCurrentTime;
					}

					//update
					Update();
				}

			}
		}

		//uninit
		Uninit();

		timeEndPeriod(1);
#pragma endregion

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//imgui
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
HWND GetWindow()
{
	return g_Window;
}
DWORD GetFrameRate()
{
	return g_FrameRate;
}
#pragma endregion






#pragma region ========== main cycle ==========
/*********************************************************
* @brief	メインサイクル関数定義
********************************************************/
void Init()
{
	//other 
	srand((unsigned int)time(0));

	//renderer init
	Renderer::Init();

	//input init
	Input::Init();

	//flyweight pattern
	DrawManager::Load();

	//imgui init
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(g_Window);
		ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());
	}

	//test create obj
	if(1)
	{
		//test plane
			Plane* plane = GameObjectManager::Create<Plane>();
			plane->GetTransform()->SetRotation(PI / 2.0f, 0, 0);
			plane->GetTransform()->SetPosition(0, 0, 0);

		//test light
			MainLight* lit = GameObjectManager::Create<MainLight>();

		//test camera
			MainCamera* cmr = GameObjectManager::Create<MainCamera>();
			cmr->GetCamera()->LookAt = plane->GetTransform();

		//test obj
		if (0)
		{
			Torus* t = GameObjectManager::Create<Torus>();
			Torus* t2 = GameObjectManager::Create<Torus>();
			Torus* t3 = GameObjectManager::Create<Torus>();

			t2->GetTransform()->SetParent(t->GetTransform());
			t2->GetTransform()->SetPosition(1, 1, 0);
			t2->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);

			t3->GetTransform()->SetParent(t2->GetTransform());
			t3->GetTransform()->SetPosition(0, 1, 0);
			t3->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);

			//test line painter
			DrawLineDescription dldesc;
			dldesc.StartTransform = t3->GetTransform();
			dldesc.EndTransform = t->GetTransform();
			dldesc.Color = { 5,2,2,1 };
			dldesc.Size = 0.01f;
			LinePainter::Instance()->MakeLine(dldesc);

			//test transform anime
			if (0)
			{
				TransformAnimeDescripition tadesc(t->GetTransform(), t->GetTransform());
				tadesc.LoopCount = INT_MAX;
				tadesc.EndPosition = { 0,3,0 };
				D3DXQuaternionRotationYawPitchRoll(&tadesc.EndRotation, PI / 3, PI / 2, PI / 4);
				tadesc.EndScale = V3_ONE * 0.5f;
				new TransformAnime(t, tadesc);
			}
		}

		//test depth UI for shadow map
		if (1)
		{
			DepthUI* depthUI = GameObjectManager::Create<DepthUI>();
		}

		//test cube and collision
		if (0)
		{
			Cube* cb = GameObjectManager::Create<Cube>();
			cb->GetTransform()->SetPosition(0, 3, 2);
			cb->GetTransform()->SetRotation(PI / 3, PI / 3, 0);
			cb->GetTransform()->SetScale(1, 1, 0.5f);
		}

		//test ActSelection button
		if (0)
		{
			D3DXVECTOR3 actSelectPos = { -3,2,-0.5f };
			D3DXVECTOR3 actSelectScl = V3_ONE;
			ActSelection* actSelect = new ActSelection(actSelectPos, actSelectScl);
		}

		//test particle system
		if (0)
		{
			ParticleSystem* ps = GameObjectManager::Create<ParticleSystem>();
			ps->GetTransform()->SetPosition(0, 0, 0);
			ParticleSystem* ps2 = GameObjectManager::Create<ParticleSystem>();
			ps2->GetTransform()->SetPosition(-2, 2, 0);
			ParticleSystem* ps3 = GameObjectManager::Create<ParticleSystem>();
			ps3->GetTransform()->SetPosition(2, 1, 0);
		}
	}

	//Manager::Init();
	GameManager::Instance()->Start();
}
void Update()
{
	//input update
	Input::Update();

	//test
	{
		if (Input::Mouse.IsButtonDown(MOUSE_LEFT))
		{
			POINT pt = Input::Mouse.GetMouseWinPos();
			std::string info = "mouse :("+
				std::to_string(pt.x)+
				","+
				std::to_string(pt.y)+
				")";
			DebugInfo::Print(info);
		}
	}

	//logic update
	GameManager::Instance()->Update();

	//update gameobject
	GameObjectManager::Update();

#if 1
	//shadow depth draw
	Renderer::BeginDepth();

	//ライトカメラの行列をセット
	LightManager::SelectMainLightView();
	//CameraManager::SelectMainCameraView();

	//影を落としたいオブジェクトを描画(一応地面も)
	DrawManager::DrawShadowDepth();
#endif

#if 1
	//test render tex
	Renderer::BeginTest();
	LightManager::SelectMainLightView();
	DrawManager::DrawAll();
#endif

	//prepare for draw
	Renderer::Begin();

	//メインカメラの行列をセット
	CameraManager::SelectMainCameraView();
	//LightManager::SelectMainLightView();

	//draw game view
	DrawManager::DrawAll();


	//draw imgui
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DebugInfo::Update();


		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	//test reset instance count
	Polygon2DMany::Instance()->EndFrame();

	//draw over
	Renderer::End();
}
void Uninit() 
{
	//DrawManager::Clear();
	//CameraManager::Clear();
	DrawManager::Unload();
	TextureFactory::Clear();
	ModelFactory::Clear();


	//imgui uninit
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//renderer uninit
	Renderer::Uninit();

	//input uninit
	Input::Uninit();

	//other 
	GameManager::Instance()->End();
	GameObjectManager::Clear();

}
#pragma endregion