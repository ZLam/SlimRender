#include "StatView.h"

#include "Core/App.h"

extern App* SlimRender;

StatView::StatView(const std::string& InName) :
BaseView(InName)
{
	
}

StatView::~StatView()
{
	
}

bool StatView::Init()
{
	auto& IO = ImGui::GetIO();
	WindowFlags =	ImGuiWindowFlags_NoDecoration |
					ImGuiWindowFlags_AlwaysAutoResize |
					ImGuiWindowFlags_NoSavedSettings |
					ImGuiWindowFlags_NoFocusOnAppearing |
					ImGuiWindowFlags_NoNav |
					ImGuiWindowFlags_NoMove;
	Pos = ImVec2(IO.DisplaySize.x - 10.0f, 10.0f);
	Pivot = ImVec2(1.0f, 0.0f);
	return true;
}

void StatView::Draw()
{
	ImGui::SetNextWindowPos(Pos, ImGuiCond_Always, Pivot);
	ImGui::SetNextWindowBgAlpha(0.7f);
	if (ImGui::Begin(Name.c_str(), nullptr, WindowFlags))
	{
		ImGui::Text("Stat");
		ImGui::Separator();
		ImGui::Text("FPS : %d", SlimRender->GetFPS());
		ImGui::Text("DeltaTime : %f", SlimRender->GetDeltaTime());
	}
	ImGui::End();
}
