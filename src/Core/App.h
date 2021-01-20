#pragma once

#include <string>
#include <chrono>

#include "SDL.h"
#undef main
#include "ViewMgr.h"

class App
{
private:
	std::string Name;
	int ScreenWidth;
	int ScreenHeight;
	
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	
	bool bRunning = false;
	std::chrono::time_point<std::chrono::steady_clock> StartTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> PrevTimePoint;
	int MaxFps = 60;
	long long FixedFrameTime;
	long long ElapsedTime = 0;
	float DeltaTime = 0;

	ViewMgr* MyViewMgr;

public:
	App(const std::string& InName, const int& InScreenWidth, const int& InScreenHeight);
	~App();
	App(const App&) = delete;
	App(App&&) = delete;
	
	bool Init();
	void Run();

	float GetDeltaTime() { return DeltaTime; }
	int GetFPS() { return static_cast<int>(1.0f / DeltaTime); }

	SDL_Window* GetWindow() { return Window; }
	SDL_Renderer* GetRenderer() { return Renderer; }
};