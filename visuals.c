#include "visuals.h"

void displayMoves(Piece piece) {
	resetValidity();
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            vector2 pos = {x, y};

            if (isValidMove(piece.position, pos, false)) {
                board[x][y].isValidMove = true;
            }
        }
    }
}

void hideMoves() {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			board[x][y].isValidMove = false;
		}
	}
}
