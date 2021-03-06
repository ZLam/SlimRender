#include "App.h"

#include <iostream>
#include <thread>
#include "imgui.h"
#include "imgui_sdl.h"

App::~App()
{
	if (MyViewMgr)
	{
		delete MyViewMgr;
		MyViewMgr = nullptr;
	}
	
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

App& App::GetInstance()
{
	static App Instance;
	return Instance;
}

bool App::Init(const std::string& InName, const uint32& InScreenWidth, const uint32& InScreenHeight)
{
	Name = InName;
	ScreenWidth = InScreenWidth;
	ScreenHeight = InScreenHeight;
	FixedFrameTime = 1000000000 / MaxFps;
	MyViewMgr = new ViewMgr();
	MyViewMgr->RegisterViews();
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "[SDL] init fail" << std::endl;
		return false;
	}

	Window = SDL_CreateWindow(
		Name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		ScreenWidth,
		ScreenHeight,
		SDL_WINDOW_SHOWN		//SDL_WINDOW_RESIZABLE
	);
	if (!Window)
	{
		std::cout << "[SDL] create window fail" << "(" << SDL_GetError() << ")" << std::endl;
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (!Renderer)
	{
		std::cout << "[SDL] create renderer fail" << "(" << SDL_GetError() << ")" << std::endl;
		return false;
	}

	ImGui::CreateContext();
	ImGuiSDL::Initialize(Renderer, ScreenWidth, ScreenHeight);

	// ImGui::StyleColorsClassic();

	if (!MyViewMgr->InitViews())
	{
		return false;
	}
	
	return true;
}

void App::Run()
{
	if (bRunning)
	{
		return;
	}

	StartTimePoint = std::chrono::steady_clock::now();
	PrevTimePoint = StartTimePoint;
	bRunning = true;

	while (bRunning)
	{
		auto CurTimePoint = std::chrono::steady_clock::now();
		auto DiffTime = std::chrono::duration_cast<std::chrono::nanoseconds>(CurTimePoint - PrevTimePoint).count();
		PrevTimePoint = CurTimePoint;
		
		if (DiffTime <= 0)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			continue;
		}

		if (ElapsedTime < FixedFrameTime)
		{
			ElapsedTime += DiffTime;
			SumDiffTime += DiffTime;
		}
		else
		{
			// std::cout << ElapsedTime << "  " << DiffTime << "  " << FixedFrameTime << std::endl;
			
			DeltaTime = static_cast<float>(SumDiffTime) / 1000000000.0f;
			ElapsedTime -= FixedFrameTime;
			if (ElapsedTime < FixedFrameTime)
			{
				SumDiffTime = 0;
			}

			ImGuiIO& IO = ImGui::GetIO();

			// handle event
			SDL_Event Event;
			while (SDL_PollEvent(&Event))
			{
				if (Event.type == SDL_QUIT)
				{
					bRunning = false;
				}
				else if (Event.type == SDL_WINDOWEVENT)
				{
					if (Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						IO.DisplaySize.x = static_cast<float>(Event.window.data1);
						IO.DisplaySize.y = static_cast<float>(Event.window.data2);
					}
				}
				else if (Event.type == SDL_MOUSEWHEEL)
				{
					if (Event.wheel.x > 0) IO.MouseWheelH += 1;
					if (Event.wheel.x < 0) IO.MouseWheelH -= 1;
					if (Event.wheel.y > 0) IO.MouseWheel += 1;
					if (Event.wheel.y < 0) IO.MouseWheel -= 1;
				}
				else if (Event.type == SDL_TEXTINPUT)
				{
					IO.AddInputCharactersUTF8(Event.text.text);
				}
				else if (Event.type == SDL_KEYDOWN || Event.type == SDL_KEYUP)
				{
					int key = Event.key.keysym.scancode;
					IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(IO.KeysDown));
					IO.KeysDown[key] = (Event.type == SDL_KEYDOWN);
					IO.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
					IO.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
					IO.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
#ifdef _WIN32
					IO.KeySuper = false;
#else
					IO.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
#endif

					if (IO.KeysDown[SDL_SCANCODE_ESCAPE])
					{
						bRunning = false;
					}
				}
			}

			// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)
			int mouseX, mouseY;
			const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
			IO.DeltaTime = DeltaTime;
			IO.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
			IO.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
			IO.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

			// new frame
			ImGui::NewFrame();

			// draw demo
			// ImGui::ShowDemoWindow();

			// draw something
			MyViewMgr->DrawViews();

			// clear renderer
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderClear(Renderer);

			// handle render
			ImGui::Render();
			ImGuiSDL::Render(ImGui::GetDrawData());

			// now draw a point in (1, 1), because drag imgui window could lag, problem may be in imguiSDL(https://github.com/Tyyppi77/imgui_sdl)
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderDrawPoint(Renderer, 1, 1);

			// show renderer
			SDL_RenderPresent(Renderer);
		}
	}
}
