#include "main.h"
#include "debugInfo.h"
#include "Excuter.h"
#include "Behaviour.h"


void Behaviour::Print(std::string info)
{
	DebugInfo::Print(
		"BH-" + std::to_string(ID()) + ": "
		+ info);
}


void Behaviour::Update()
{
	if (m_State == START)
	{
		Start();
		NextState();
		Print("start");
	}
	else if (m_State == UPDATE)
	{
		//need NextState() in MainUpdate()
		MainUpdate();
	}
	else if (m_State == END)
	{
		ResetState(); 
		if (m_Excuter!=nullptr)
		{
			m_Excuter->SetExcute(m_Next);
		}
		Print("finished");
		End();
	}
}
