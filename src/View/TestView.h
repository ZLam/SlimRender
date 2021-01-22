#pragma once

#include "Core/BaseView.h"

#include "SDL.h"
#include "imgui.h"
#include "Core/Render.h"

class TestView : public BaseView
{
private:
	SDL_Texture* Tex;
	ImVec2 TexSize;

	SDL_Texture* Tex_Try;
	Render* Render_Try;
	
public:
	TestView(const std::string& InName);
	virtual ~TestView();

	bool Init() override;
	void Draw() override;
};
