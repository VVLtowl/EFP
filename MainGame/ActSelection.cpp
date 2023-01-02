#include "main.h"
#include "Button.h"
#include "TransformAnime.h"
#include "LookAtCamera.h"
#include "ActSelection.h"

ActSelection::ActSelection(const D3DXVECTOR3& pos, const D3DXVECTOR3& scl):
	GameObject(),
	m_OriginalPosition(pos),
	m_OriginalScale(scl)
{	
	//init transform
	m_Transform3D->SetPosition(pos);
	m_Transform3D->SetScale(scl);

	//create polygon2D
	Polygon2DDescription polyDesc;
	polyDesc.DrawObjDesc.DepthEnable = false;
	polyDesc.DrawObjDesc.Layer = LAYER_WORLD_SHADOW_ALPHA;
	polyDesc.DrawObjDesc.Shader = SHADER_UNLIT;
	polyDesc.TextureID = TEXID_HINT;
	polyDesc.Size = ACTSELECTION_IDLE_SIZE;
	m_Polygon2D = new Polygon2D(this, polyDesc);

	//create boxCollider
	BoxColliderDescription boxDesc;
	boxDesc.AABBData.Min = {
		-ACTSELECTION_IDLE_SIZE.x / 2.0f,
		-ACTSELECTION_IDLE_SIZE.y / 2.0f,
		-1
	};
	boxDesc.AABBData.Max = {
		ACTSELECTION_IDLE_SIZE.x / 2.0f,
		ACTSELECTION_IDLE_SIZE.y / 2.0f,
		1
	};
	m_BoxCollider = new BoxCollider(this, boxDesc);

	//create button
	{
		m_Button = new Button(this);
		m_Button->AddEnterEvent([this]()
			{
				m_Polygon2D->Color = { 1,0,0,1 };

				TransformAnimeDescripition transDesc(m_Transform3D);
				transDesc.LoopCount = 1;
				transDesc.DurationCount = 15;
				transDesc.EndScale = m_OriginalScale * ACTSELECTION_HIGHLIGHT_SCALE;
				transDesc.EndPosition = m_OriginalPosition + ACTSELECTION_HIGHLIGHT_MOVE;
				SlowLerpAnime slowLerp;
				new TransformAnime(this, transDesc, slowLerp);

				DebugInfo::Print("highlight button");
			});
		m_Button->AddExitEvent([this]()
			{
				m_Polygon2D->Color = { 1,1,1,1 };

				TransformAnimeDescripition transDesc(m_Transform3D);
				transDesc.LoopCount = 1;
				transDesc.DurationCount = 15;
				transDesc.EndScale = m_OriginalScale;
				transDesc.EndPosition = m_OriginalPosition;
				SlowLerpAnime slowLerp;
				new TransformAnime(this, transDesc, slowLerp);
				
				DebugInfo::Print("reset button");
			});
	}



	//create lookAtCamera
	{
		Camera* cmr = CameraManager::GetMainCamera();
		m_LookAtCamera = new LookAtCamera(this, cmr);
	}

	//create draw line
	{
		Camera* cmr = CameraManager::GetMainCamera();
		DrawLineDescription drawlDesc;
		drawlDesc.Color = { 3,0,0,1 };
		drawlDesc.Size = 0.05f;
		drawlDesc.StartPos = cmr->GetGameObject()->GetTransform()->GetPosition();
		drawlDesc.LocalPos = false;
		m_DrawLine = new DrawLine(this, drawlDesc);
	}

	//create hint
	m_Hint = GameObjectManager::Create<Emitter>();
}

ActSelection::~ActSelection()
{
	m_Hint->SetState(DEAD);
}

void ActSelection::UpdateGameObject()
{
	//mouse
	{
		POINT pt = Input::Mouse.GetMouseWinPos();
		Camera* cmr = CameraManager::GetMainCamera();
		D3DXVECTOR3 startPos =
		{
			(float)(pt.x - SCREEN_WIDTH / 2) / SCREEN_WIDTH * cmr->Width,
			(float)(SCREEN_HEIGHT / 2 - pt.y) / SCREEN_HEIGHT * cmr->Height,
			0 
		};
		D3DXVECTOR3 endPos = startPos;
		endPos.z += 100;

		D3DXMATRIX cmrWorld = cmr->GetGameObject()->GetTransform()->GetWorldMatrix();
		D3DXVec3TransformCoord(&startPos, &startPos, &cmrWorld);
		D3DXVec3TransformCoord(&endPos, &endPos, &cmrWorld);

		m_DrawLine->StartPos = startPos;
		m_DrawLine->EndPos = endPos;
		m_Hint->GetTransform()->SetPosition(startPos);
		
		Collision::Line line(startPos, endPos);
		Collision::AABB aabb =m_BoxCollider->AABBData;
		D3DXMATRIX boxWorld = m_Transform3D->GetWorldMatrix();

		float outDist;
		D3DXVECTOR3 outPoint;
		D3DXVECTOR3 outNormal;
		if (Collision::Intersect(line, aabb, boxWorld,
			&outDist, &outPoint, &outNormal))
		{
			m_Button->SetState(Button::HIGHLIGHTED);
		}
		else
		{
			m_Button->SetState(Button::IDLE);
		}
	}
}
