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

// FUNCTIONS

// Initialize SDL and create window
void init();

// Render scene
void render();

// Frees media and shuts down SDL
void close();

void update();

// Handle user input
void input(SDL_Event event);

// OBJECTS

// The field
Field field;

// MAIN FUNCTION

int main(int argc, char* args[])
{
	// Initialize SDL
	init();

	// Event handler
	SDL_Event event;

	// Update frame counter
	int lastTime = 0;
	lastFrame = SDL_GetTicks();
	if (lastFrame >= (lastTime + 1000))
	{
		lastTime = lastFrame;
		fps = frameCount;
		frameCount = 0;
	}

	// Create field
	field.create();

	// Spawn pseudo random piece based on miliseconds elapsed from execution start
	time_t t;
	srand((unsigned)time(&t));
	cur = blocks[rand() % 7];

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

		// If user presses a key
		input(event);

		// Update current piece position
		update();

		// Render scene
		render();
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

void render()
{
	// Clear window
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(gRenderer);

	// Increase framecount
	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60))
	{
		SDL_Delay((1000 / 60) - timerFPS);
	}

	// Draw current field
	field.draw(cur);

	// Render scene
	SDL_RenderPresent(gRenderer);
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

void update()
{
	if (left)
	{
		if (cur.x >= 1)
		{
			cur.x--;
		}
	}

	if (right)
	{
		if (cur.x + cur.size < 10)
		{
			cur.x++;
		}
	}
	if (down)
	{
		cur.y++;
	}
		
	if (up) rotate();
	left = false;
	right = false;
	down = false;
	up = false;
}

void input(SDL_Event event)
{
	// User presses a key
	if (event.type == SDL_KEYDOWN)
	{
		// Move piece based on key press
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			up = true;
			break;

		case SDLK_DOWN:
			down = true;
			//field = piece.movePiece(field, 3);
			break;

		case SDLK_LEFT:
			left = true;
			break;

		case SDLK_RIGHT:
			right = true;
			break;
		case SDLK_RETURN:
			printf("Seconds since start: %d .", (SDL_GetTicks() / 1000));
			break;
		case SDLK_ESCAPE:
			quit = true;
			break;
		default:
			printf("Other Key pressed.");
			break;
		}
	}
}