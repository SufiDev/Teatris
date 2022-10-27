#pragma once
// STRUCTURES

// Struct representing the field
struct Field
{
	//----Field attributes
	// Array containing all cells in the field
	int cell[FIELD_COLS][FIELD_ROWS];

	//----Field method declaration
	// Create new field
	void create();
	// Draw the field
	void draw();
};

// Struct representing a moving block
struct Block
{
	//----Block attributes
	// Variables for the block's current position
	int x;
	int y;
};


// STRUCTURE METHODS

//----Field methods

// Clear field
void Field::create()
{
	for (size_t j = 0; j < FIELD_ROWS; j++)
	{
		for (size_t i = 0; i < FIELD_COLS; i++)
		{
			cell[i][j] = GRID_BLOCK;
		}
	}
}

// Draw rectangles on each position of the field scaled to the mino rectangle's size
void Field::draw()
{
	// Iterate through field columns
	for (int j = 0; j < FIELD_ROWS; j++)
	{
		// Iterate through field rows
		for (int i = 0; i < FIELD_COLS; i++)
		{
			// Change current block position
			mino.x = i * MINO_SIZE + GAME_OFF_X;
			mino.y = j * MINO_SIZE + GAME_OFF_X;
			if (mino.x + MINO_SIZE == SCREEN_WIDTH)
			{
				mino.x = GAME_OFF_X;
			}
			// Draw block based on type
			switch (cell[i][j])
			{
			case GREY_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				break;
			case PURPLE_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				break;
			default:
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				break;
			}
		}
	}
}