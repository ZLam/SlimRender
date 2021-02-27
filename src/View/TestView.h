#pragma once

#include "Core/BaseView.h"

#include "SDL.h"
#include "imgui.h"
#include "Core/Render.h"
#include "Core/Camera.h"
#include "Core/Viewport.h"

class TestView : public BaseView
{
private:
	SDL_Texture* Tex;
	ImVec2 TexSize = ImVec2(100.0f, 100.0f);

	SDL_Texture* Tex_Try;
	Render* Render_Try;
	Vec2i Size_Try = Vec2i(700, 700);
	Camera* Cam_Try;
	Viewport* ViewPort_Try;
	
public:
	TestView(const std::string& InName);
	virtual ~TestView() override;

	bool Init() override;
	void Draw() override;
};
