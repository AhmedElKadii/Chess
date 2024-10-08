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
			if (board[x][y].name != 'k' && board[x][y].color != turn) {
				vector2 piecePos = new_vector2(x, y);
				if (isValidMove(piecePos, kingPos, false)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool exposesKingToCheck(vector2 dest) {
	if (!is_piece_selected && !validating) return false;
	Piece selectedPiece;
	if (is_piece_selected) selectedPiece = getPiece(selected_piece);
	else if (validating) selectedPiece = getPiece(getKingPosition());

    Piece tempDestPiece = getPiece(dest);

    movePiece(selectedPiece, dest, true);

    bool inCheck = isInCheck();

    board[selectedPiece.position.x][selectedPiece.position.y] = selectedPiece;
    board[dest.x][dest.y] = tempDestPiece;

	validating = false;
    return inCheck;
}

char determineMate() {
	vector2 kingPos = getKingPosition();

	validating = true;
	if (getValidMoves(getPiece(kingPos)) <= 1 && isInCheck()) return 'm';
	else if (getValidMoves(getPiece(kingPos)) <= 1 && !isInCheck() && calculateValidMoves()==0) return 's';
	else return 'n';
}
