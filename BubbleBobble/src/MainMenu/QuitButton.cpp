#include "pch.h"
#include "QuitButton.h"

#include <SDL.h>

void QuitButton::Execute()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}
