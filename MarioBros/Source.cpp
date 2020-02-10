#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

#include "Texture2D.h"
#include "Constants.h"
#include "Commons.h"
#include "Source.h"
#include "GameScreenManager.h"

using namespace::std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Texture2D* gTexture = NULL;
//SDL_Texture* LoadTextureFromFile(const std::string& path);
GameScreenManager* gameScreenManager;
Uint32 gOldTime;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
//void FreeTexture();

int flip = 10;

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		//pauses for a few seconds
		//SDL_Delay(5000);
	}

	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
	gOldTime = SDL_GetTicks();

	//flag to check if game is quit
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

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();

		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Mario Bros",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//window created
		if (gWindow == NULL)
		{
			//window not created
			cout << "window was not created. Error: " << SDL_GetError();
			return false;
		}

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

			////Load the background texture
			//gTexture = new Texture2D(gRenderer);
			//if (!gTexture->LoadTextureFromFile("Images/test.bmp"))
			//{
			//	return false;
			//}

		}
		else
		{
			cout << "SDL_Image could not initialise. Error: " << SDL_GetError();
			return false;
		}

		return true;
	}
}

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

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDL_MOUSEBUTTONDOWN:
			cout << "mouse click" << endl;
		}
	case SDL_KEYDOWN:
		flip++;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	return false;
}

void Render()
{
	//Clear screen - black
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	////Set where to render the image
	//gTexture->Render(Vector2D(), SDL_FLIP_NONE);

	gameScreenManager->Render();

	//update screen
	SDL_RenderPresent(gRenderer);
}

