#pragma once
#include "Component.h"
#include <vector>
#include <functional>

/*********************************************************
* @brief    各フレームのデータの計算関数
********************************************************/
class ComputeFrameTransformDataFunc
{
public:
    virtual void operator()(class TransformAnime* ani) = 0;
};

class SlowLerpAnime :
    public ComputeFrameTransformDataFunc
{
public:
    void operator()(class TransformAnime* ani);
};

//class  :
//    public ComputeFrameTransformDataFunc
//{
//public:
//    void operator()(TransformAnime* ani);
//};


/*********************************************************
* @brief    変換アニメの情報
********************************************************/
struct TransformAnimeDescripition
{
    D3DXVECTOR3 StartPosition = V3_ZERO;
    D3DXQUATERNION StartRotation = QUAT_IDENTITY;
    D3DXVECTOR3 StartScale = V3_ONE;
    D3DXVECTOR3 EndPosition = V3_ZERO;
    D3DXQUATERNION EndRotation = QUAT_IDENTITY;
    D3DXVECTOR3 EndScale = V3_ONE;

    int LoopCount = 1;//INT_MAX:infinity loop
    int Duration = 60;

    SlowLerpAnime computeFunc;
    ComputeFrameTransformDataFunc& ComputeAniDataFunc = computeFunc;
    std::function<void()> EndEvent = []() {; };



    TransformAnimeDescripition() {};
    TransformAnimeDescripition(
        D3DXVECTOR3 startPos, 
        D3DXVECTOR3 endPos) 
    {
        StartPosition = startPos;
        EndPosition = endPos;
    };
    TransformAnimeDescripition(
        class Transform3D* start, 
        class Transform3D* end)
    {
        if (start != nullptr)
        {
            StartPosition = start->GetPosition();
            StartRotation = start->GetRotation();
            StartScale = start->GetScale();
        }

        if (end != nullptr)
        {
            EndPosition = end->GetPosition();
            EndRotation = end->GetRotation();
            EndScale = end->GetScale();
        }
    }
};

class TransformAnime :
    public Component
{
public:
    TransformAnime(
        class GameObject* owner,
        TransformAnimeDescripition desc,
        int order = COMP_TRANSFORMANIME);
    ~TransformAnime();
    void Update() override;

    void Destroy();

private:
    std::function<void()> m_EndEvent;

public:
    D3DXVECTOR3 m_StartPosition;
    D3DXQUATERNION m_StartRotation;
    D3DXVECTOR3 m_StartScale;
    D3DXVECTOR3 m_EndPosition;
    D3DXQUATERNION m_EndRotation;
    D3DXVECTOR3 m_EndScale;

    D3DXVECTOR3 m_NowPosition;
    D3DXQUATERNION m_NowRotation;
    D3DXVECTOR3 m_NowScale;

    int m_LoopCount;
    const float m_Duration;
    float m_FrameCount;

    // @brief   生成する時全フレームのデータを計算して生成
    std::vector<D3DXVECTOR3> m_AnimePositions;
    std::vector<D3DXQUATERNION> m_AnimeRotations;
    std::vector<D3DXVECTOR3> m_AnimeScales;
};

