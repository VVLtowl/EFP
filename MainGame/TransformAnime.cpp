#include "main.h"
#include "TransformAnime.h"

TransformAnime::TransformAnime(
	GameObject* owner, 
	TransformAnimeDescripition desc,
	ComputeFrameTransformDataFunc& computeDataFunc,
	int order) :
	Component(owner, order),
	m_StartPosition(desc.StartPosition),
	m_StartRotation(desc.StartRotation),
	m_StartScale(desc.StartScale),
	m_EndPosition(desc.EndPosition),
	m_EndRotation(desc.EndRotation),
	m_EndScale(desc.EndScale),
	m_LoopCount(desc.LoopCount),
	m_Duration(desc.DurationCount),
	m_FrameCount(0)
{
	m_NowPosition = m_StartPosition;
	m_NowRotation = m_StartRotation;
	m_NowScale = m_StartScale;

	//æŒvŽZ
	computeDataFunc(this);
}

TransformAnime::~TransformAnime()
{
}

void TransformAnime::Update()
{
	if (m_LoopCount > 0)
	{
#if 0
		if (m_Duration - m_FrameCount > 0)
		{
			float ratio = m_FrameCount / m_Duration;
			
			//D3DXVECTOR3 deltaPos = (m_EndPosition - m_NowPosition) / (m_DurationCount - m_FrameCount);
			D3DXVec3Lerp(&m_NowPosition, &m_NowPosition, &m_EndPosition, ratio);
			D3DXQuaternionSlerp(&m_NowRotation, &m_NowRotation, &m_EndRotation, ratio);
			D3DXVec3Lerp(&m_NowScale, &m_NowScale, &m_EndScale, ratio);

			//set owner transform
			m_Owner->GetTransform()->SetPosition(m_NowPosition);
			m_Owner->GetTransform()->SetRotation(m_NowRotation);
			m_Owner->GetTransform()->SetScale(m_NowScale);
			m_Owner->GetTransform()->UpdateTransform();
			m_Owner->GetTransform()->DisableUpdateThisFrame();

			m_FrameCount += 1;
		}
		else
		{
			m_LoopCount--; 
			m_FrameCount = 0;

			m_Owner->GetTransform()->SetPosition(m_EndPosition);
			m_Owner->GetTransform()->SetRotation(m_EndRotation);
			m_Owner->GetTransform()->SetScale(m_EndScale);
			m_Owner->GetTransform()->UpdateTransform();
			m_Owner->GetTransform()->DisableUpdateThisFrame();
			m_NowPosition = m_StartPosition;
			m_NowRotation = m_StartRotation;
			m_NowScale = m_StartScale;
		}
#else 
		if (m_Duration - m_FrameCount > 0)
		{
			float ratio = m_FrameCount / m_Duration;

			//set owner transform
			m_Owner->GetTransform()->SetPosition(m_AnimePositions[m_FrameCount]);
			m_Owner->GetTransform()->SetRotation(m_AnimeRotations[m_FrameCount]);
			m_Owner->GetTransform()->SetScale(m_AnimeScales[m_FrameCount]);
			m_Owner->GetTransform()->UpdateTransform();
			m_Owner->GetTransform()->DisableUpdateThisFrame();

			m_FrameCount += 1;
		}
		else
		{
			m_LoopCount--;
			m_FrameCount = 0;

			m_Owner->GetTransform()->SetPosition(m_EndPosition);
			m_Owner->GetTransform()->SetRotation(m_EndRotation);
			m_Owner->GetTransform()->SetScale(m_EndScale);
			m_Owner->GetTransform()->UpdateTransform();
			m_Owner->GetTransform()->DisableUpdateThisFrame();
		}
#endif
	}
	else
	{
		m_Owner->GetTransform()->SetPosition(m_EndPosition);
		m_Owner->GetTransform()->SetRotation(m_EndRotation);
		m_Owner->GetTransform()->SetScale(m_EndScale);
		m_Owner->GetTransform()->UpdateTransform();
		m_Owner->GetTransform()->DisableUpdateThisFrame();

		StartDestroy();
	}
}

void TransformAnime::Destroy()
{
	StartDestroy();
}

void SlowLerpAnime::operator()(TransformAnime* ani)
{
	for (int i = 0; i < ani->m_Duration; i++)
	{
		float ratio = i / ani->m_Duration;

		D3DXVec3Lerp(&ani->m_NowPosition, &ani->m_NowPosition, &ani->m_EndPosition, ratio);
		D3DXQuaternionSlerp(&ani->m_NowRotation, &ani->m_NowRotation, &ani->m_EndRotation, ratio);
		D3DXVec3Lerp(&ani->m_NowScale, &ani->m_NowScale, &ani->m_EndScale, ratio);

		ani->m_AnimePositions.emplace_back(ani->m_NowPosition);
		ani->m_AnimeRotations.emplace_back(ani->m_NowRotation);
		ani->m_AnimeScales.emplace_back(ani->m_NowScale);
	}
}
