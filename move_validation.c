#include "move_validation.h"
#include "board.h"
#include "check_validation.h"

bool isEmpty(Piece piece) {
	return piece.name == ' ';
}

bool canCapture(Piece piece, Piece dest) {
	return piece.color != dest.color || isEmpty(dest);
}

bool validateWhitePawn(Piece piece, Piece dest, bool capture) {
	// en passant
	Piece* right = getPieceAsPointer((vector2){piece.position.x + 1, piece.position.y});
	if (right != NULL && right->lastMove == 2 && piece.position.x + 1 == dest.position.x && piece.position.y - 1 == dest.position.y) {
		right->isValidMove = true;
		dest.isValidMove = true;
		if (canCapture(piece, dest) && isEmpty(dest) == true) {
			if (capture) capturePiece(*right);
			return true;
		}
		else return false;
	}
	Piece* left = getPieceAsPointer((vector2){piece.position.x - 1, piece.position.y});
	if (left != NULL && left->lastMove == 2 && piece.position.x - 1 == dest.position.x && piece.position.y - 1 == dest.position.y) {
		left->isValidMove = true;
		dest.isValidMove = true;
		if (canCapture(piece, dest) && isEmpty(dest) == true) {
			if (capture) capturePiece(*left);
			return true;
		}
		else return false;
	}
    if (piece.position.x - 1 == dest.position.x && piece.position.y - 1 == dest.position.y) {
		Piece pos = getPiece((vector2) {piece.position.x-1, piece.position.y-1});
		pos.isValidMove = true;
		dest.isValidMove = true;
		return canCapture(piece, dest) && !isEmpty(dest);
	}
    if (piece.position.x + 1 == dest.position.x && piece.position.y - 1 == dest.position.y) {
		Piece pos = getPiece((vector2) {piece.position.x+1, piece.position.y-1});
		pos.isValidMove = true;
		dest.isValidMove = true;
		return canCapture(piece, dest) && !isEmpty(dest);
	}
    if (piece.position.x == dest.position.x && piece.position.y - 1 == dest.position.y && isEmpty(dest)) {
		dest.isValidMove = true;
		return true;
	}
    if (piece.position.x == dest.position.x && piece.position.y - 2 == dest.position.y && piece.totalMoves == 0 && isEmpty(dest)) {
		Piece prev = getPiece((vector2) {dest.position.x, dest.position.y + 1});
		prev.isValidMove = true;
		dest.isValidMove = true;
		return true;
	}
    return false;
}

bool validateBlackPawn(Piece piece, Piece dest, bool capture) {
	// en passant
	Piece* right = getPieceAsPointer((vector2){piece.position.x + 1, piece.position.y});
	if (right != NULL && right->lastMove == 2 && piece.position.x + 1 == dest.position.x && piece.position.y + 1 == dest.position.y) {
		right->isValidMove = true;
		dest.isValidMove = true;
		if (canCapture(piece, dest) && isEmpty(dest) == true) {
			if (capture) capturePiece(*right);
			return true;
		}
		else return false;
	}
	Piece* left = getPieceAsPointer((vector2){piece.position.x - 1, piece.position.y});
	if (left != NULL && left->lastMove == 2 && piece.position.x - 1 == dest.position.x && piece.position.y + 1 == dest.position.y) {
		left->isValidMove = true;
		dest.isValidMove = true;
		if (canCapture(piece, dest) && isEmpty(dest) == true) {
			if (capture) capturePiece(*left);
			return true;
		}
		else return false;
	}
    if (piece.position.x - 1 == dest.position.x && piece.position.y + 1 == dest.position.y) {
		Piece pos = getPiece((vector2) {piece.position.x-1, piece.position.y+1});
		pos.isValidMove = true;
		dest.isValidMove = true;
		return canCapture(piece, dest) && !isEmpty(dest);
	}
    if (piece.position.x + 1 == dest.position.x && piece.position.y - 1 == dest.position.y) {
		Piece pos = getPiece((vector2) {piece.position.x+1, piece.position.y+1});
		pos.isValidMove = true;
		dest.isValidMove = true;
		return canCapture(piece, dest) && !isEmpty(dest);
	}
    if (piece.position.x == dest.position.x && piece.position.y + 1 == dest.position.y && isEmpty(dest)) {
		dest.isValidMove = true;
		return true;
	}
    if (piece.position.x == dest.position.x && piece.position.y + 2 == dest.position.y && piece.totalMoves == 0 && isEmpty(dest)) {
		Piece prev = getPiece((vector2) {dest.position.x, dest.position.y - 1});
		prev.isValidMove = true;
		dest.isValidMove = true;
		return true;
	}
    return false;
}

bool validateRook(Piece piece, Piece dest) {
    if (piece.position.x == dest.position.x || piece.position.y == dest.position.y) {
        int xDir = (dest.position.x > piece.position.x) ? 1 : (dest.position.x < piece.position.x) ? -1 : 0;
        int yDir = (dest.position.y > piece.position.y) ? 1 : (dest.position.y < piece.position.y) ? -1 : 0;

        int x = piece.position.x + xDir;
        int y = piece.position.y + yDir;

        while (x != dest.position.x || y != dest.position.y) {
            Piece currPiece = getPiece((vector2) {x, y});
            if (!isEmpty(currPiece)) return false;
            board[x][y].isValidMove = true;

            x += xDir;
            y += yDir;
        }

        return canCapture(piece, dest);
    }
    return false;
}

bool validateBishop(Piece piece, Piece dest) {
    if (abs(piece.position.x - dest.position.x) == abs(piece.position.y - dest.position.y)) {
        int xDir = (dest.position.x > piece.position.x) ? 1 : -1;
        int yDir = (dest.position.y > piece.position.y) ? 1 : -1;

        int x = piece.position.x + xDir;
        int y = piece.position.y + yDir;

        while (x != dest.position.x && y != dest.position.y) {
            Piece currPiece = getPiece((vector2) {x, y});
            if (!isEmpty(currPiece)) return false;
            board[x][y].isValidMove = true;

            x += xDir;
            y += yDir;
        }

        return canCapture(piece, dest);
    }
    return false;
}

bool validateQueen(Piece piece, Piece dest) {
	return validateRook(piece, dest) || validateBishop(piece, dest);
}

bool validateKnight(Piece piece, Piece dest) {
	if (abs(piece.position.x - dest.position.x) == 2 
			&& abs(piece.position.y - dest.position.y) == 1) return canCapture(piece, dest);
	if (abs(piece.position.x - dest.position.x) == 1 
			&& abs(piece.position.y - dest.position.y) == 2) return canCapture(piece, dest);
	return false;
}

bool validateWhiteKing(Piece king, Piece dest) {
	if (dest.isValidMove) return false;
	if (king.totalMoves == 0 && dest.position.x == 6 && dest.position.y == 7) {
		Piece rook = getPiece((vector2) {7, 7});
		if (rook.totalMoves == 0 && equals(rook.position, (vector2) {7, 7})) {
			rook.isValidMove = true;
			dest.isValidMove = true;
			return true;
		}
	}
	if (king.totalMoves == 0 && dest.position.x == 2 && dest.position.y == 7) {
		Piece rook = getPiece((vector2) {0, 7});
		if (rook.totalMoves == 0 && equals(rook.position, (vector2) {0, 7})) {
			rook.isValidMove = true;
			dest.isValidMove = true;
			return true;
		}
	}
    if (abs(king.position.x - dest.position.x) <= 1
			&& abs(king.position.y - dest.position.y) <= 1
			&& !exposesKingToCheck(dest.position)) {
        return canCapture(king, dest);
    }
    return false;
}

bool validateBlackKing(Piece king, Piece dest) {
	if (dest.isValidMove) return false;
	if (king.totalMoves == 0 && dest.position.x == 6 && dest.position.y == 0) {
		Piece rook = getPiece((vector2) {7, 0});
		if (rook.totalMoves == 0 && equals(rook.position, (vector2) {7, 0})) {
			rook.isValidMove = true;
			dest.isValidMove = true;
			return true;
		}
	}
	if (king.totalMoves == 0 && dest.position.x == 2 && dest.position.y == 0) {
		Piece rook = getPiece((vector2) {0, 0});
		if (rook.totalMoves == 0 && equals(rook.position, (vector2) {0, 0})) {
			rook.isValidMove = true;
			dest.isValidMove = true;
			return true;
		}
	}
    if (abs(king.position.x - dest.position.x) <= 1
			&& abs(king.position.y - dest.position.y) <= 1
			&& !exposesKingToCheck(dest.position)) {
        return canCapture(king, dest);
    }
    return false;
}

void resetValidity() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j].isValidMove = false;
		}
	}
}

bool isValidMove(vector2 from, vector2 to, bool capture) {
    Piece piece = getPiece(from);
    Piece dest = getPiece(to);

    if (piece.color == dest.color) return false;

    switch (piece.name) {
        case 'p':
            if (piece.color == 'w') return validateWhitePawn(piece, dest, capture);
            if (piece.color == 'b') return validateBlackPawn(piece, dest, capture);
            break;
        case 'r':
            return validateRook(piece, dest);
		case 'b':
			return validateBishop(piece, dest);
		case 'q':
			return validateQueen(piece, dest);
		case 'n':
			return validateKnight(piece, dest);
		case 'k':
			if (piece.color == 'w') return validateWhiteKing(piece, dest);
			if (piece.color == 'b') return validateBlackKing(piece, dest);
		default:
			break;
    }
    return false;
}
