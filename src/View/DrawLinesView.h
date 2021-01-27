#pragma once

#include "Core/BaseView.h"
#include "SDL.h"
#include "Core/Render.h"

class DrawLinesView : public BaseView
{
private:
	SDL_Texture* Tex_Lines;
	Render* Render_Lines;
	uint32 OriginX = 150;
	uint32 OriginY = 150;
	
public:
	DrawLinesView(const std::string& InName);
	virtual ~DrawLinesView();
	bool Init() override;
	void Draw() override;
};
