#include "glew.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		


		if (RESIZABLE_WINDOW == true) flags |= SDL_WINDOW_RESIZABLE;

		// TODO 2: Create options for RESIZABLE, SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE,
		// SDL_WINDOW_FULLSCREEN_DESKTOP (same way as with FULLSCREEN)

		// OPEN GL INIT
		

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		flags |= SDL_WINDOW_OPENGL;

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags); // crear window

		context = SDL_GL_CreateContext(window);

	

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);

			//GLEW INIT
			GLenum err = glewInit();
			LOG("Using Glew %s", glewGetString(GLEW_VERSION));
		
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glClearDepth(1.0f);
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_DEPTH_TEST);
			glFrontFace(GL_CCW);
			glEnable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_2D);
			glViewport(0, 0,SCREEN_WIDTH, SCREEN_HEIGHT);
			glClearDepth(1.0f);
			glClearColor(0.3f, 0.3f, 0.3f, 1.f); 
		}
	}

	return ret;
}


// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	SDL_GL_DeleteContext(context);

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

