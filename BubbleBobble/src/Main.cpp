#include "pch.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "BubbleBobble.h"

int main(int, char*[])
{
	BubbleBobble game;
	game.Run();
	return 0;
}
