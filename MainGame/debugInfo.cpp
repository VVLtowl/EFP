

#include "imgui/imgui.h"
#include "debugInfo.h"

std::string DebugInfo::m_Info[BDEBUG_INFO_MAX];

void DebugInfo::Update()
{
	ImGui::Begin("Debug Info Window"); 
	int id = 0;
	while(id < BDEBUG_INFO_MAX)
	{
		ImGui::Text("%s\n", m_Info[id].c_str());
		id++;
	}
	ImGui::End();
}

void DebugInfo::Print(std::string info)
{
	static int m_id;

	m_Info[m_id] = info;
	int next = (m_id + 1) % BDEBUG_INFO_MAX;
	m_Info[next] = "----------------------";

	m_id = (m_id + 1) % BDEBUG_INFO_MAX;
}
