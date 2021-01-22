#pragma once

#include "Core/BaseView.h"

#include "imgui.h"

class StatView : public BaseView
{
private:
	ImGuiWindowFlags WindowFlags;
	ImVec2 Pos;
	ImVec2 Pivot;
	
public:
	StatView(const std::string& InName);
	virtual ~StatView();

	bool Init() override;
	void Draw() override;
};
