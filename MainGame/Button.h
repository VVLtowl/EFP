#pragma once
#include "Component.h"
#include <string>
#include <functional>

class Button :
    public Component
{
    /*********************************************************
    * @brief    component override
    ********************************************************/
public:
    Button(class GameObject* owner, 
        int order = COMP_BUTTON);

    /*********************************************************
    * @brief    button event
    ********************************************************/
private:
    void OnClick();
    void OnEnter();
    void OnExit();
public:
    void AddClickEvent(std::function<void()> onClick);
    void AddEnterEvent(std::function<void()> onEnter);
    void AddExitEvent(std::function<void()> onExit);
private:
    std::list<std::function<void()>> m_OnClicks;
    std::list<std::function<void()>> m_OnEnters;
    std::list<std::function<void()>> m_OnExits;

    /*********************************************************
    * @brief    button state
    ********************************************************/
public:
    enum State
    {
        IDLE,
        HIGHLIGHTED,
        CLICKED,
    };
public:
    void SetState(State state);
private:
    State m_State;
};

