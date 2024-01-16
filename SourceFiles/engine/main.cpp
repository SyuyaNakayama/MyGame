#include "MyGame.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::unique_ptr<WristerEngine::Framework> game = std::make_unique<MyGame>();
	game->Run();
	return 0;
}