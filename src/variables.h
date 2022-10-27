#pragma once
// SDL VARIABLES

// Window we'll render to
SDL_Window* gWindow = nullptr;

// Renderer
SDL_Renderer* gRenderer = nullptr;

// Basic mino
SDL_Rect mino = { 100, 100, MINO_SIZE, MINO_SIZE };

// Input booleans
bool left, right, up, down;

// Main loop flag
bool quit = false;

// Variables for limiting framerate
int frameCount, timerFPS, fps;
int lastFrame = 0;