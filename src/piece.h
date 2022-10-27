#pragma once
// CLASS DECLARATION

class Piece
{
	//----Piece attributes
	// Array that will contain the blocks
	Block blocks[4] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };

	// Integer representing the type of the piece
	int mType = 0;

	// Short representing the movement in x axis
	short dx = 0;

	// Short representing the movement in y axis
	short dy = 0;

	// Short representing the orientation of the piece
	short mDir = 0;

public:

	//----Piece methods
	// Spawn piece based on type
	void spawn(int x, int y);

	// Rotate piece blocks clockwise
	void rotate();

	// Update piece position on the field
	Field movePiece(Field fld, int dir);
};


// METHOD DEFINITION

// Spawn piece based on type
void Piece::spawn(int x, int y)
{
	switch (rand() % 2 + 1)
	{
	case 1:
		mType = 1;
		blocks[0] = { x, y };
		blocks[1] = { x + 1, y };
		blocks[2] = { x, y + 1 };
		blocks[3] = { x + 1, y + 1 };
		break;
	case 2:
		mType = 2;
		blocks[0] = { x, y };
		blocks[1] = { x + 1, y };
		blocks[2] = { x + 2, y };
		blocks[3] = { x + 1, y + 1 };
		break;
	default:
		printf("Piece type not found.");
		break;
	}
}

// Rotate piece blocks clockwise
void Piece::rotate()
{
	printf("rotating...\n");
}

// Update piece position on the field
Field Piece::movePiece(Field fld, int dir)
{
	// Reset direction of movement
	dx = 0, dy = 0;

	// Before moving, clear previous piece
	for (int i = 0; i < 4; i++)
	{
		fld.cell[blocks[i].x][blocks[i].y] = GRID_BLOCK;
	}

	// Go through every block in the piece
	for (int i = 0; i < 4; i++)
	{
		// if block collides with floor or a grey block below it
		if (blocks[i].y + 1 > 19 || fld.cell[blocks[i].x][blocks[i].y + 1] == GREY_BLOCK)
		{
			// Set previous position to grey blocks
			for (int i = 0; i < 4; i++)
			{
				fld.cell[blocks[i].x][blocks[i].y] = GREY_BLOCK;
			}
			// Spawn a new piece
			spawn(SPAWN_X, SPAWN_Y);
			break;
		}
	}

	// Set the new step based on key input
	switch (dir)
	{
	case 0:
		for (int i = 0; i < 4; i++)
		{
			if (blocks[i].x + 1 > 9 || fld.cell[blocks[i].x + 1][blocks[i].y] == GREY_BLOCK)
			{
				dx = 0;
				break;
			}
			else
			{
				dx = 1;
			}
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			if (blocks[i].x - 1 < 0 || fld.cell[blocks[i].x - 1][blocks[i].y] == GREY_BLOCK)
			{
				dx = 0;
				break;
			}
			else
			{
				dx = -1;
			}
		}
		break;
	default:
		dy = 1;
		break;
	}

	// Update piece position by dx and dy
	for (int i = 0; i < 4; i++)
	{
		blocks[i].x += dx;
		blocks[i].y += dy;
	}

	// Place the piece on its next position on the field
	for (int i = 0; i < 4; i++)
	{
		fld.cell[blocks[i].x][blocks[i].y] = mType;
	}

	return fld;
}