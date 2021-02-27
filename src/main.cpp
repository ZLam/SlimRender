#include "Core/App.h"

int main(int argc, char** argv)
{
	auto& MyApp = App::GetInstance();
	if (MyApp.Init("SlimRender", 1600, 900))
	{
		MyApp.Run();
	}
	return 0;
}
