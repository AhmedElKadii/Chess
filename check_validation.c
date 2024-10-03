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
	vector2 kingPos = getKingPosition();

	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y].name != 'k' && board[x][y].color != turn && getValidMoves(board[x][y]) > 0) {
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
	if (!is_piece_selected) return false;
    Piece selectedPiece = getPiece(selected_piece);
    Piece tempDestPiece = getPiece(dest);

    movePiece(selectedPiece, dest, true);

    bool inCheck = isInCheck();

    board[selectedPiece.position.x][selectedPiece.position.y] = selectedPiece;
    board[dest.x][dest.y] = tempDestPiece;

    return inCheck;
}

bool isInMate() {
	vector2 kingPos = getKingPosition();

	return getValidMoves(getPiece(kingPos)) <= 1 && isInCheck();
}
