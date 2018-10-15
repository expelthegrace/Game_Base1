#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "glew.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_WINDOWEVENT) {
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) glViewport(0, 0, event.window.data1, event.window.data2);
	}

	// TODO 1: Make the application properly close when ESC is pressed (do not use exit())


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}