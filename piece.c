#include "piece.h"

Piece createPiece(char name, char color, int x, int y) {
    Piece piece;
    piece.name = name;
    piece.color = color;
    piece.position = new_vector2(x, y);
    piece.lastMove = 0;
    piece.totalMoves = 0;
	piece.isValidMove = false;
    return piece;
}

void promotePiece(Piece *piece, char name) {
	piece->name = name;
}

bool shouldPromote(Piece piece) {
	if (piece.name == 'p') {
		return (piece.position.y == 0 && piece.color == 'w') || (piece.position.y == SIZE - 1 && piece.color == 'b');
	}
	return false;
}
