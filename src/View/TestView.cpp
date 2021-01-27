#include "TestView.h"

#include <iostream>
#include "Core/Math.h"
#include "Core/Functions.h"
#include "Core/RandomHelper.h"
#include "Core/App.h"

TestView::TestView(const std::string& InName) :
BaseView(InName),
TexSize(100, 100)
{
	
}

TestView::~TestView()
{
	if (Tex)
	{
		SDL_DestroyTexture(Tex);
		Tex = nullptr;
	}
	if (Tex_Try)
	{
		SDL_DestroyTexture(Tex_Try);
		Tex_Try = nullptr;
	}
	if (Render_Try)
	{
		delete Render_Try;
		Render_Try = nullptr;
	}
}

bool TestView::Init()
{
	auto Renderer = App::GetInstance().Get_SDL_Renderer();
	
	Tex = SDL_CreateTexture(
		Renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_TARGET,
		static_cast<int>(TexSize.x),
		static_cast<int>(TexSize.y)
	);

	Render_Try = new Render(500, 500);

	Tex_Try = SDL_CreateTexture(
		Renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		static_cast<int>(Render_Try->GetWidth()),
		static_cast<int>(Render_Try->GetHeight())
	);

	return true;
}

void TestView::Draw()
{
	auto Renderer = App::GetInstance().Get_SDL_Renderer();
	SDL_SetRenderTarget(Renderer, Tex);
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(Renderer, 10, 10, 490, 490);
	SDL_SetRenderTarget(Renderer, nullptr);

	Render_Try->CleanColorBuffer();
	Render_Try->DrawPixel(0, 0, Color::Red);
	Render_Try->DrawPixel(Render_Try->GetWidth() / 2, Render_Try->GetHeight() / 2, Color::Green);
	Render_Try->DrawPixel(Render_Try->GetWidth() - 1, Render_Try->GetHeight() - 1, Color::Blue);
	// Render_Try->DrawLine(50, 50, 200, 100, Color::Red);
	// Render_Try->DrawLine(50, 50, 200, 200, Color::Red);
	// Render_Try->DrawLine(50, 50, 200, 300, Color::Red);
	// Render_Try->DrawLine(50, 50, 200, 400, Color::Red);
	// Render_Try->DrawLine(50, 50, 100, 400, Color::Red);
	// Render_Try->DrawLine(150, 150, 50, 250, Color::Red);
	// Render_Try->DrawLine(150, 150, 79, 220, Color::Red);
	uint32 OriginX = 150;
	uint32 OriginY = 150;
	float r = 100;
	float a = 0;
	while (a < 360)
	{
		// std::cout << ANGLE_TO_RADIAN(a) << std::endl;
		auto ToX = static_cast<uint32>(OriginX + cos(ANGLE_TO_RADIAN(a)) * r);
		auto ToY = static_cast<uint32>(OriginY + sin(ANGLE_TO_RADIAN(a)) * r);
		// std::cout << OriginX << " " << OriginY << " " << ToX << " " << ToY << std::endl;
		Render_Try->DrawLine(OriginX, OriginY, ToX, ToY, Color::Red);
		a += 10;
	}
	
	void* Pixels = nullptr;
	int Pitch;
	SDL_LockTexture(Tex_Try, nullptr, &Pixels, &Pitch);
	memcpy(Pixels, Render_Try->GetColorBuffer(), Render_Try->GetColorBufferSize());
	SDL_UnlockTexture(Tex_Try);

	if (ImGui::Begin(Name.c_str()))
	{
		ImGui::Image(Tex, TexSize);
		if (ImGui::Button("Test"))
		{
			std::cout << "haha" << std::endl;
			std::cout << Random(0u, 10u) << std::endl;
			std::cout << Random(0.0f, 10.0f) << std::endl;
			auto c1 = Color::RandomColor();
			std::cout << c1 << std::endl;
		}
	}
	ImGui::End();

	if (ImGui::Begin("Test Soft Render", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Image(
			Tex_Try,
			ImVec2(
				static_cast<float>(Render_Try->GetWidth()),
				static_cast<float>(Render_Try->GetHeight())
			)
		);
	}
	ImGui::End();
}
