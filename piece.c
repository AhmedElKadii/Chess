#include "piece.h"

Piece createPiece(char name, char color, int x, int y) {
    Piece piece;
    piece.name = name;
    piece.color = color;
    piece.position = new_vector2(x, y); // Store x and y properly
    piece.lastMove = 0;
    piece.totalMoves = 0;
	piece.isValidMove = false;
    return piece;
}
