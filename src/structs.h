#pragma once
// STRUCTURES

// Struct representing a moving block
struct Block
{
	//----Block attributes
	int bType;
	bool active;
};

// Moving piece
struct Piece
{
	//----Piece attributes
	int pType;
	bool matrix[4][4];
	int x, y;
	int size;
};

// Randomly generated moving piece
Piece blocks[7]
{
	{ // I Piece
	CYAN_BLOCK,
	{{1, 1, 1, 1}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 4
	},
	{ // J Piece
	ORANGE_BLOCK,
	{{1, 0, 0, 0}
	,{1, 1, 1, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 3
	},
	{ // L Piece
	BLUE_BLOCK,
	{{0, 0, 1, 0}
	,{1, 1, 1, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 3
	},
	{ // O Piece
	YELLOW_BLOCK,
	{{1, 1, 0, 0}
	,{1, 1, 0, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 2
	},
	{ // S Piece
	GREEN_BLOCK,
	{{0, 1, 1, 0}
	,{1, 1, 0, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 3
	},
	{ // T Piece
	PURPLE_BLOCK,
	{{0, 1, 0, 0}
	,{1, 1, 1, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 3
	},
	{ // Z Piece
	RED_BLOCK,
	{{1, 1, 0, 0}
	,{0, 1, 1, 0}
	,{0, 0, 0, 0}
	,{0, 0, 0, 0}},
	SPAWN_X, SPAWN_Y, 3
	}
}, cur;

Piece reverseCols(Piece p)
{
	Piece temp = p;
	for (int i = 0; i < p.size; i++)
	{
		for (int j = 0; j < p.size / 2; j++)
		{
			bool t = p.matrix[i][j];
			temp.matrix[i][j] = p.matrix[i][p.size - j - 1];
			temp.matrix[i][p.size - j - 1] = t;
		}
	}
	return temp;
}

Piece transpose(Piece p)
{
	Piece temp = p;
	for (int i = 0; i < p.size; i++)
	{
		for (int j = 0; j < p.size; j++)
		{
			temp.matrix[i][j] = p.matrix[j][i];
		}
	}
	return temp;
}

void rotate()
{
	cur = reverseCols(transpose(cur));
}


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
	void draw(Piece p);
};

//----Field methods

// Clear field
void Field::create()
{
	for (int i = 0; i < FIELD_COLS; i++)
	{
		for (int j = 0; j < FIELD_ROWS; j++)
		{
			cell[i][j] = GRID_BLOCK;
		}
	}
}

// Rectangle surrounding every mino
void drawRect(SDL_Renderer* rnd, SDL_Rect r)
{
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(rnd, &r);
}

// Draw rectangles on each position of the field scaled to the mino rectangle's size
void Field::draw(Piece p)
{
	// Clear previous field
	for (int i = 0; i < FIELD_COLS; i++)
	{
		// Iterate through field rows
		for (int j = 0; j < FIELD_ROWS; j++)
		{
			if (cell[i][j] != GREY_BLOCK && cell[i][j] != GRID_BLOCK)
			{
				cell[i][j] = GRID_BLOCK;
			}
		}
	}

	// Add piece to field
	for (int i = 0; i < p.size; i++)
	{
		for (int j = 0; j < p.size; j++)
		{
			if (p.matrix[i][j] == 1) {
				cell[p.x + i][p.y + j] = p.pType;
			}
		}
	}

	// Iterate through field columns
	for (int i = 0; i < FIELD_COLS; i++)
	{
		// Iterate through field rows
		for (int j = 0; j < FIELD_ROWS; j++)
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
				drawRect(gRenderer, mino);
				break;
			case CYAN_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			case YELLOW_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			case PURPLE_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			case GREEN_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			case RED_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			case BLUE_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			case ORANGE_BLOCK:
				SDL_SetRenderDrawColor(gRenderer, 255, 127, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				drawRect(gRenderer, mino);
				break;
			default:
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(gRenderer, &mino);
				break;
			}
		}
	}
}