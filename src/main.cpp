#include "Core/App.h"

App* SlimRender;

int main(int argc, char** argv)
{
	SlimRender = new App("SlimRender", 1280, 720);
	if (SlimRender->Init())
	{
		SlimRender->Run();
	}
	delete SlimRender;
	SlimRender = nullptr;
	return 0;
}
