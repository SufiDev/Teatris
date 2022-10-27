#pragma once
// CONSTANTS

// Screen dimension constants
const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 480;

// Size of every square in the grid
const int MINO_SIZE = 25;

// Spawing position of blocks on the grid
const int SPAWN_X = 3;
const int SPAWN_Y = 2;

// Types of block to be drawn on grid
const int GRID_BLOCK = 0;
const int GREY_BLOCK = 1;
const int PURPLE_BLOCK = 2;

// Game field constants
const int FIELD_ROWS = 20;
const int FIELD_COLS = 10;

// Offset or the game screen
const int GAME_OFF_X = (SCREEN_WIDTH - (FIELD_COLS * MINO_SIZE)) / 2;
const int GAME_OFF_Y = (SCREEN_HEIGHT - (FIELD_ROWS * MINO_SIZE)) / 2;