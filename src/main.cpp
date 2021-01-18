#include <iostream>

#include "SDL.h"
#undef main

#include "imgui.h"
#include "imgui_sdl.h"

#define G_SCREEN_W 1280
#define G_SCREEN_H 720

int main()
{	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "[SDL] init fail" << std::endl;
		return  -1;
	}
	
	SDL_Window* window = SDL_CreateWindow(
		"SlimRender",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		G_SCREEN_W, G_SCREEN_H,
		SDL_WINDOW_RESIZABLE
	);
	if (!window)
	{
		std::cout << "[SDL] create window fail" << "(" << SDL_GetError() << ")" << std::endl;
		return -1;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "[SDL] create renderer fail" << "(" << SDL_GetError() << ")" << std::endl;
		return -1;
	}

	ImGui::CreateContext();
	ImGuiSDL::Initialize(renderer, G_SCREEN_W, G_SCREEN_H);

	// ImGui::StyleColorsClassic();

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
	{
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, nullptr);
	}

	SDL_Texture* texture_pic = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 300, 300);
	{
		SDL_SetRenderTarget(renderer, texture_pic);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
		SDL_RenderDrawLine(renderer, 10, 10, 290, 290);
		SDL_SetRenderTarget(renderer, nullptr);
	}

	bool run = true;
	while (run)
	{
		ImGuiIO& io = ImGui::GetIO();

		int wheel = 0;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) run = false;
			else if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					io.DisplaySize.x = static_cast<float>(e.window.data1);
					io.DisplaySize.y = static_cast<float>(e.window.data2);
				}
			}
			else if (e.type == SDL_MOUSEWHEEL)
			{
				wheel = e.wheel.y;
			}
		}

		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

		io.DeltaTime = 1.0f / 60.0f;
		io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
		io.MouseWheel = static_cast<float>(wheel);

		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		if (ImGui::Begin("Image"))
		{
			ImGui::Image(texture, ImVec2(100, 100));
		}
		ImGui::End();

		if (ImGui::Begin("Image_Pic"))
		{
			ImGui::Image(texture_pic, ImVec2(300, 300));
		}
		ImGui::End();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer, 50, 50);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(renderer, 50, 200, 600, 100);

		SDL_RenderPresent(renderer);
	}

	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}