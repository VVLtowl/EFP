#include "main.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* owner,
	BoxColliderDescription boxColDesc,
	int updateOrder):
	Collider(owner, updateOrder),
	AABBData(boxColDesc.AABBData)
{
	m_ColliderType = COL_AABB;
	m_BoxVertex[0] = { AABBData.Min[0],AABBData.Max[1],AABBData.Max[2] };
	m_BoxVertex[1] = { AABBData.Max[0],AABBData.Max[1],AABBData.Max[2] };
	m_BoxVertex[2] = { AABBData.Min[0],AABBData.Max[1],AABBData.Min[2] };
	m_BoxVertex[3] = { AABBData.Max[0],AABBData.Max[1],AABBData.Min[2] };
	m_BoxVertex[4] = { AABBData.Min[0],AABBData.Min[1],AABBData.Max[2] };
	m_BoxVertex[5] = { AABBData.Max[0],AABBData.Min[1],AABBData.Max[2] };
	m_BoxVertex[6] = { AABBData.Min[0],AABBData.Min[1],AABBData.Min[2] };
	m_BoxVertex[7] = { AABBData.Max[0],AABBData.Min[1],AABBData.Min[2] };

	for (int i = 0; i < 12; i++)
	{
		DrawLineDescription desc;
		desc.Size = 0.05f;
		desc.Color = { 10,1,1,1 };
		m_DrawLine[i] = new DrawLine(m_Owner, desc);
	}
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	//prepare draw box by line
	if(1)
	{
		m_DrawLine[0]->LineData.Start = m_BoxVertex[0]; 
		m_DrawLine[0]->LineData.End = m_BoxVertex[1];
		m_DrawLine[1]->LineData.Start = m_BoxVertex[1]; 
		m_DrawLine[1]->LineData.End = m_BoxVertex[3];
		m_DrawLine[2]->LineData.Start = m_BoxVertex[3];
		m_DrawLine[2]->LineData.End = m_BoxVertex[2];
		m_DrawLine[3]->LineData.Start = m_BoxVertex[2];
		m_DrawLine[3]->LineData.End = m_BoxVertex[0];


		m_DrawLine[4]->LineData.Start = m_BoxVertex[0];
		m_DrawLine[4]->LineData.End = m_BoxVertex[4];
		m_DrawLine[5]->LineData.Start = m_BoxVertex[1];
		m_DrawLine[5]->LineData.End = m_BoxVertex[5];
		m_DrawLine[6]->LineData.Start = m_BoxVertex[3];
		m_DrawLine[6]->LineData.End = m_BoxVertex[7];
		m_DrawLine[7]->LineData.Start = m_BoxVertex[2];
		m_DrawLine[7]->LineData.End = m_BoxVertex[6];


		m_DrawLine[8]->LineData.Start = m_BoxVertex[4];
		m_DrawLine[8]->LineData.End = m_BoxVertex[5];
		m_DrawLine[9]->LineData.Start = m_BoxVertex[5];
		m_DrawLine[9]->LineData.End = m_BoxVertex[7];
		m_DrawLine[10]->LineData.Start = m_BoxVertex[7];
		m_DrawLine[10]->LineData.End = m_BoxVertex[6];
		m_DrawLine[11]->LineData.Start = m_BoxVertex[6];
		m_DrawLine[11]->LineData.End = m_BoxVertex[4];

	}
}
