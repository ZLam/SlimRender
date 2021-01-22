#pragma once

#include <string>
#include <chrono>

#include "SDL.h"
#undef main
#include "Types.h"
#include "ViewMgr.h"

class App
{
private:
	std::string Name;
	uint32 ScreenWidth;
	uint32 ScreenHeight;
	
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	
	bool bRunning = false;
	std::chrono::time_point<std::chrono::steady_clock> StartTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> PrevTimePoint;
	uint32 MaxFps = 60;
	long long FixedFrameTime;
	long long ElapsedTime;
	float DeltaTime;

	ViewMgr* MyViewMgr;

private:
	App() = default;
	~App();

public:
	App(const App&) = delete;
	App(App&&) = delete;

	static App& GetInstance();
	
	bool Init(const std::string& InName, const uint32& InScreenWidth, const uint32& InScreenHeight);
	void Run();

	float GetDeltaTime() { return DeltaTime; }
	uint32 GetFPS() { return static_cast<uint32>(1.0f / DeltaTime); }
	uint32 GetScreenWidth() { return ScreenWidth; }
	uint32 GetScreenHeight() { return ScreenHeight; }

	SDL_Window* Get_SDL_Window() { return Window; }
	SDL_Renderer* Get_SDL_Renderer() { return Renderer; }
};
