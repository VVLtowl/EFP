#pragma once
#include <stack>
#include <string>

enum BehaviourID
{
	BHID_STEP_GAME_START,
	BHID_STEP_RPS,
	BHID_STEP_BAD_MAN_ACT,
	BHID_STEP_GOOD_MAN_ACT,
	BHID_STEP_TURN_END,
	BHID_STEP_TEST_INSERT,

	BHID_PLAYER_NULL,
	BHID_PLAYER_INPUT_HAND, //
	BHID_PLAYER_SELECT_ACT,
	BHID_PLAYER_CLEAR_POINT,
	
	//BHID_PLAYER_UPDATE_STATE,
	BHID_PLAYER_OPEN_STATUS,
	BHID_PLAYER_CAUGHT,
	BHID_PLAYER_GET_TOOL,

	BHID_PLAYER_MOVE,
	BHID_PLAYER_GIVE_TOOL,
	BHID_PLAYER_CATCH,
	BHID_PLAYER_STEAL_TOOL,
	BHID_PLAYER_USE_TOOL,
	BHID_PLAYER_THEN_ACT,
	BHID_PLAYER_END_ACT,

	BHID_ANIME_PIECE_INIT,
	BHID_ANIME_PIECE_MOVE,
};

class Excuter;

class Behaviour
{
protected:
	enum State
	{
		START,
		UPDATE,
		END,

		MAX,
	};
	int m_State = START;

private:
	Behaviour* m_Next = nullptr;
	Excuter* m_Excuter = nullptr;

protected:
	virtual void Start() {};
	virtual void MainUpdate() { NextState(); };
	virtual void End() {};
	virtual int ID() = 0;

protected:
	void Print(std::string info);
	void NextState() { m_State++; };
	void ResetState() { m_State = START; };

public:
	void Update();
	void SetNext(Behaviour* next) { m_Next = next; };
	void SetExcuter(Excuter* ex) { m_Excuter = ex; };
};

