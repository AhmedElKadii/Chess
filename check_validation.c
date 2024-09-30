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

bool isInCheck(vector2 dest) {
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
    Piece selectedPiece = getPiece(selected_piece);  // Get the selected piece

    // Temporarily store the destination piece (in case it's non-empty)
    Piece tempDestPiece = getPiece(dest);

    // Simulate the move
    movePiece(selectedPiece, dest, true);  // False to avoid printing or extra logic

    // Recheck if the king is now in check after the simulated move
    bool inCheck = isInCheck(getKingPosition());

    // Revert the move (restore the original board state)
    board[selectedPiece.position.x][selectedPiece.position.y] = selectedPiece;  // Restore the moved piece
    board[dest.x][dest.y] = tempDestPiece;  // Restore the destination piece (whatever was there before)

    return inCheck;  // Return true if the move exposes the king to check
}

bool isInMate(vector2 dest) {
	vector2 kingPos;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y].name == 'k' && board[x][y].color == turn) {
				kingPos = new_vector2(x, y);
				break;
			}
		}
	}

	return getValidMoves(getPiece(kingPos)) == 0 && isInCheck(dest);
}
