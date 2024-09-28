#ifndef PIECE_H
#define PIECE_H

#include "structs.h"

typedef struct {
	char name;
	char color;
	vector2 position;
	bool isAlive;
	int lastMove;
	int totalMoves;
	bool isValidMove;
} Piece;

Piece createPiece(char name, char color, int x, int y);

#endif
