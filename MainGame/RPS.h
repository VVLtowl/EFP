#pragma once
#include <string>

class Hand
{
public:
	enum HandType
	{
		HAND_NONE,
		HAND_ROCK,
		HAND_PAPER,
		HAND_SCISSORS,
		HAND_KING,

		HAND_MAX,
	};

public:
	static std::string const m_HandName[HAND_MAX];

public:
	static std::string const HandName(HandType type);
};

class RPS
{
public:
	enum ResultType
	{
		RESULT_NONE = -2,
		RESULT_LOSE = -1,
		RESULT_DRAW = 0,
		RESULT_WIN = 1,
	};
private:
	static ResultType const Result[Hand::HAND_MAX][Hand::HAND_MAX];
public:
	static ResultType Battle(Hand::HandType main, Hand::HandType rival);
};

#pragma region ========== definition ==========
std::string const Hand::m_HandName[Hand::HAND_MAX] =
{
{"  "},
{"rock"},
{"paper"},
{"scissors"},
{"king"},
};

inline std::string const Hand::HandName(HandType type)
{
	return m_HandName[type];
}

RPS::ResultType const RPS::Result[Hand::HAND_MAX][Hand::HAND_MAX] =
{					  //self hand
	{{RESULT_NONE},{RESULT_NONE},{RESULT_NONE},{RESULT_NONE},{RESULT_NONE},},//none
	{{RESULT_NONE},{RESULT_DRAW},{RESULT_LOSE},{RESULT_WIN},{RESULT_LOSE},},//rock
	{{RESULT_NONE},{RESULT_WIN},{RESULT_DRAW},{RESULT_LOSE},{RESULT_LOSE},},//paper
	{{RESULT_NONE},{RESULT_LOSE},{RESULT_WIN},{RESULT_DRAW},{RESULT_LOSE},},//scissors
	{{RESULT_NONE},{RESULT_WIN},{RESULT_WIN},{RESULT_WIN},{RESULT_WIN},},//king
};

inline RPS::ResultType RPS::Battle(Hand::HandType main, Hand::HandType rival)
{
	return Result[main][rival];
}
#pragma endregion