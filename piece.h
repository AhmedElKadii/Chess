#ifndef PIECE_H
#define PIECE_H

#include "structs.h"

typedef struct {
	char name;
	char color;
	int x;
	int y;
	bool isAlive;
	int lastMove;
	int totalMoves;
} Piece;

Piece createPiece(char name, char color, int x, int y);

#endif
