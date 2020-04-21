//libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "Texture2D.h"
#include "Constants.h"
#include "Commons.h"
#include "Source.h"
#include "GameScreenManager.h"
#include "LivesSystem.h"

//namespaces
using namespace::std;

//class variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;

//define methods
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

//main function
int main(int argc, char* args[])
{
	//Check if SDL was set up correctly
	if (InitSDL())
	{
	}
	
	//loads screen
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);

	//gets time between frames
	gOldTime = SDL_GetTicks();

	//flag to check if game is quiting
	bool quit = false;

	//game loop
	while (!quit)
	{
		Render();
		quit = Update();
	}

	//closes window and free resources
	CloseSDL();
	return 0;
}

//initialises SDL
bool InitSDL()
{
	//if vidio or audio did not initialise then throw error
	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();

		return false;
	}
	else
	{
		//initialise the mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}

		//create window
		gWindow = SDL_CreateWindow("Mario Bros",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//check window created
		if (gWindow == NULL)
		{
			//window not created
			cout << "window was not created. Error: " << SDL_GetError();
			return false;
		}

		//create renderer and check if it loaded
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

		}
		//render failed to load
		else
		{
			cout << "SDL_Image could not initialise. Error: " << SDL_GetError();
			return false;
		}

		return true;
	}
}

//closes SDL and frees resources
void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//quits the program
	IMG_Quit();
	SDL_Quit();


	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//destroy game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;
}

//updates the program
bool Update()
{
	//Get new time
	Uint32 newTime = SDL_GetTicks();

	//Event handler
	SDL_Event e;

	//get the events
	SDL_PollEvent(&e);

	//check buttonpresses
	switch (e.type)
	{
		//if quit button was pressed exit program
	case SDL_QUIT:
		return true;
		break;

		
	}

	//updates screen manager 
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	return false;
}

//renders game
void Render()
{
	//Clear screen - black
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	//Set where to render the image
	gameScreenManager->Render();

	//update screen
	SDL_RenderPresent(gRenderer);
}


