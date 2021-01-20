#pragma once

#include "Core/BaseView.h"

#include "SDL.h"
#include "imgui.h"

class TestView : public BaseView
{
private:
	SDL_Texture* Tex;
	ImVec2 TexSize;
	
public:
	TestView(const std::string& InName);
	virtual ~TestView();

	bool Init() override;
	void Draw() override;
};