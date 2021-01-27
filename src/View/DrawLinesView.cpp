#include "DrawLinesView.h"
#include "imgui.h"
#include "Core/Math.h"
#include "Core/App.h"

DrawLinesView::DrawLinesView(const std::string& InName) :
BaseView(InName)
{
	
}

DrawLinesView::~DrawLinesView()
{
	if (Render_Lines)
	{
		delete Render_Lines;
		Render_Lines = nullptr;
	}
	if (Tex_Lines)
	{
		SDL_DestroyTexture(Tex_Lines);
		Tex_Lines = nullptr;
	}
}

bool DrawLinesView::Init()
{
	Render_Lines = new Render(800, 600);
	
	auto Renderer = App::GetInstance().Get_SDL_Renderer();
	Tex_Lines = SDL_CreateTexture(
		Renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		Render_Lines->GetWidth(),
		Render_Lines->GetHeight()
	);

	OriginX = Render_Lines->GetWidth() / 2;
	OriginY = Render_Lines->GetHeight() / 2;
	
	return true;
}

void DrawLinesView::Draw()
{
	Render_Lines->CleanColorBuffer();
	
	float r = 100;
	float a = 0;
	while (a < 360)
	{
		// std::cout << ANGLE_TO_RADIAN(a) << std::endl;
		auto ToX = static_cast<uint32>(OriginX + cos(ANGLE_TO_RADIAN(a)) * r);
		auto ToY = static_cast<uint32>(OriginY + sin(ANGLE_TO_RADIAN(a)) * r);
		// std::cout << OriginX << " " << OriginY << " " << ToX << " " << ToY << std::endl;
		Render_Lines->DrawLine(OriginX, OriginY, ToX, ToY, Color::Red);
		a += 10;
	}

	void* Pixels = nullptr;
	int Pitch;
	SDL_LockTexture(Tex_Lines, nullptr, &Pixels, &Pitch);
	memcpy(Pixels, Render_Lines->GetColorBuffer(), Render_Lines->GetColorBufferSize());
	SDL_UnlockTexture(Tex_Lines);

	if (ImGui::Begin(Name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Image(
			Tex_Lines,
			ImVec2(
				static_cast<float>(Render_Lines->GetWidth()),
				static_cast<float>(Render_Lines->GetHeight())
			)
		);
	}
	ImGui::End();
}
