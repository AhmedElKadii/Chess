#include "visuals.h"
#include "board.h"

void displayMoves(Piece piece) {
	resetValidity();
	if (piece.name == 'k') {
		for (int y = -1; y <= 1; y++) {
			for (int x = -1; x <= 1; x++) {
				if (x == 0 && y == 0) continue;

				int newX = piece.position.x + x;
				int newY = piece.position.y + y;

				if (board[newX][newY].isValidMove) board[newX][newY].isValidMove = false;
				if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
					Piece dest = getPiece((vector2) {newX, newY});
					if (canCapture(piece, dest)) board[newX][newY].isValidMove = true;
				}
			}
		}
	} else {
		for (int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++) {
				vector2 pos = {x, y};
				board[x][y].isValidMove = isValidMove(piece.position, pos, false);
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
