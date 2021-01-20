#include "TestView.h"

#include "Core/App.h"

extern App* SlimRender;

TestView::TestView(const std::string& InName) :
BaseView(InName),
TexSize(500, 500)
{
	
}

TestView::~TestView()
{
	if (Tex)
	{
		SDL_DestroyTexture(Tex);
		Tex = nullptr;
	}
}

bool TestView::Init()
{
	auto Renderer = SlimRender->GetRenderer();
	Tex = SDL_CreateTexture(
		Renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_TARGET,
		static_cast<int>(TexSize.x),
		static_cast<int>(TexSize.y)
	);
	return true;
}

void TestView::Draw()
{
	auto Renderer = SlimRender->GetRenderer();
	SDL_SetRenderTarget(Renderer, Tex);
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(Renderer, 10, 10, 490, 490);
	SDL_SetRenderTarget(Renderer, nullptr);

	if (ImGui::Begin(Name.c_str()))
	{
		ImGui::Image(Tex, TexSize);
	}
	ImGui::End();
}

