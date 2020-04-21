//libraies
#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

//namespaces
using namespace::std;

//constructor
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;

	int mWidth = 0;
	int mHeight = 0;
}

//destructor
Texture2D::~Texture2D()
{
	//free up memory
	Free();
	mRenderer = NULL;
}

//loads texture from an image file
bool Texture2D::LoadTextureFromFile(std::string path)
{
	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	//if image loads
	if (pSurface != NULL)
	{
		//set dimensions
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		//Colour key the image - the colour to be transparent
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		//create the texture from the pixels on the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}

		//Remove the loaded surface now that there is a texture
		SDL_FreeSurface(pSurface);
	}
	//if image failed to load throw error
	else
	{
		cout << "Unable to create image from path: " << path << "\t Error: " << IMG_GetError() << endl;
	}

	//return whether the process was successful
	return mTexture != NULL;
}

//frees memory
void Texture2D::Free()
{
	mWidth = 0;
	mHeight = 0;
}

//render texture
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y , mWidth, mHeight };

	//render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

//render texture with rect
void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}
