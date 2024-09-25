#include <stdio.h>

#include "piece.h"

Piece createPiece(char name, char color, int x, int y) {
	Piece piece;
	piece.name = name;
	piece.color = color;
	piece.x = x;
	piece.y = y;
	piece.isAlive = true;
	piece.lastMove = 0;
	piece.totalMoves = 0;
	return piece;
} 
