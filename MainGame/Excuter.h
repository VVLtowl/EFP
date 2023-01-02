#pragma once
#include "Behaviour.h"

class Excuter
{
private:
	Behaviour* ExcuteBehaviour = nullptr;
public:
	void Excute()
	{
		if (ExcuteBehaviour != nullptr)
		{
			ExcuteBehaviour->Update();
		}
	};
	void SetExcute(Behaviour* bh)
	{ 
		ExcuteBehaviour = bh;
	};
	void JumpTo(Behaviour* bh) 
	{
		bh->SetNext(ExcuteBehaviour);
		ExcuteBehaviour = bh; 
	};
};
