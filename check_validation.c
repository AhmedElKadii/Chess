#include "check_validation.h"
#include "board.h"

vector2 getKingPosition() {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y].name == 'k' && board[x][y].color == turn) {
				return new_vector2(x, y);
			}
		}
	}
	return new_vector2(-1, -1);
}

bool isInCheck() {
	resetValidity();
	vector2 kingPos = getKingPosition();

	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y].color != turn && getValidMoves(board[x][y]) > 0) {
				vector2 piecePos = new_vector2(x, y);
				if (isValidMove(piecePos, kingPos, false)) {
					printf("King is in check\n");
					return true;
				}
			}
		}
	}

	return false;
}

bool exposesKingToCheck(vector2 dest) {
    Piece selectedPiece = getPiece(selected_piece);
    Piece tempDestPiece = getPiece(dest);

    movePiece(selectedPiece, dest, true);

    bool inCheck = isInCheck();

    board[selectedPiece.position.x][selectedPiece.position.y] = selectedPiece;
    board[dest.x][dest.y] = tempDestPiece;

	printf("selected position: %d %d\n", selected_piece.x, selected_piece.y);

    return inCheck;
}

bool isInMate() {
	vector2 kingPos;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y].name == 'k' && board[x][y].color == turn) {
				kingPos = new_vector2(x, y);
				break;
			}
		}
	}

	return getValidMoves(getPiece(kingPos)) == 0 && isInCheck();
}
