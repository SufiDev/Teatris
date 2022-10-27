/*
 * Teatris
 * Tetris game prototype for C++ and SDL2 practice.
**/


// INCLUDES

// System librares
#include <SDL.h>
#include <iostream>
#include <time.h>
#include <vector>

// User librares
#include "constants.h"
#include "variables.h"
#include "structs.h"
#include "piece.h"


// FUNCTIONS

// Initialize SDL and create window
void init();

// Frees media and shuts down SDL
void close();


// OBJECTS

// The field
Field field;

// Randomly generated moving piece
Piece piece;


// MAIN FUNCTION

int main(int argc, char* args[])
{
	// Initialize SDL
	init();

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event event;

	// Counter for total frames drawed
	short frameCount = 0;

	//Current time start time
	Uint32 startTime = 0;

	// Create field
	field.create();

	// Spawn pseudo random piece based on miliseconds elapsed from execution start
	time_t t;
	srand((unsigned)time(&t));
	piece.spawn(SPAWN_X, SPAWN_Y);

	// Game loop
	while (!quit)
	{
		// Hhandle events
		SDL_PollEvent(&event);

		// User requests quit
		if (event.type == SDL_QUIT)
		{
			quit = true;
			break;
		}

		// Clear window
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(gRenderer);

		// User presses a key
		if (event.type == SDL_KEYDOWN)
		{
			// Move piece based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				printf("Key u pressed.");
				piece.rotate();
				break;

			case SDLK_DOWN:
				printf("Key d pressed.");
				//field = piece.movePiece(field, 3);
				break;

			case SDLK_LEFT:
				field = piece.movePiece(field, 2);
				break;

			case SDLK_RIGHT:
				field = piece.movePiece(field, 0);
				break;
			case SDLK_RETURN:
				printf("Seconds since start: %d .", (SDL_GetTicks() - startTime) / 1000);
				break;
			default:
				printf("Other Key pressed.");
				break;
			}
		}
		// Fall one row every 20 frames
		if (frameCount % 20 == 0)
		{
			// Move piece down
			field = piece.movePiece(field, -1);

			// Reset framecount
			frameCount = 0;
		}

		// Draw current field
		field.draw();

		// Render scene
		SDL_RenderPresent(gRenderer);

		// Increase framecount
		frameCount++;

		// Delay to limit framerate
		SDL_Delay(25);
	}

	// Quit SDL
	close();

	return 0;
}


// FUNCTION DEFINITION

void init()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create window
	gWindow = SDL_CreateWindow("Teatris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	// Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

	// Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void close()
{
	// Destroy window and renderer
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = nullptr;
	gRenderer = nullptr;

	// Quit SDL
	SDL_Quit();
}