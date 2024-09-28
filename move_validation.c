#include "move_validation.h"

bool isEmpty(Piece piece) {
	return piece.name == ' ';
}

bool validateWhitePawn(Piece piece, Piece dest) {
    if (piece.position.x == dest.position.x && piece.position.y - 1 == dest.position.y && isEmpty(dest)) {
		return true;
	}
    if (piece.position.x == dest.position.x && piece.position.y - 2 == dest.position.y && piece.totalMoves == 0 && isEmpty(dest)) {
		Piece prev = getPiece((vector2) {dest.position.x, dest.position.y + 1});
		return true;
	}
    return false;
}

bool validateBlackPawn(Piece piece, Piece dest) {
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
    if (piece.position.x == dest.position.x) {
        if (piece.position.y < dest.position.y) {
            for (int y = piece.position.y + 1; y < dest.position.y; y++) {
                Piece currPiece = getPiece((vector2) {piece.position.x, y});
                if (!isEmpty(currPiece)) return false;
                board[piece.position.x][y].isValidMove = true;
            }
        }
        else if (piece.position.y > dest.position.y) {
            for (int y = piece.position.y - 1; y > dest.position.y; y--) {
                Piece currPiece = getPiece((vector2) {piece.position.x, y});
                if (!isEmpty(currPiece)) return false;
                board[piece.position.x][y].isValidMove = true;
            }
        }
        return dest.color != piece.color;
    } else if (piece.position.y == dest.position.y) {
        if (piece.position.x < dest.position.x) {
            for (int x = piece.position.x + 1; x < dest.position.x; x++) {
                Piece currPiece = getPiece((vector2) {x, piece.position.y});
                if (!isEmpty(currPiece)) return false;
                board[x][piece.position.y].isValidMove = true;
            }
        }
        else if (piece.position.x > dest.position.x) {
            for (int x = piece.position.x - 1; x > dest.position.x; x--) {
                Piece currPiece = getPiece((vector2) {x, piece.position.y});
                if (!isEmpty(currPiece)) return false;
                board[x][piece.position.y].isValidMove = true;
            }
        }
        return dest.color != piece.color;
    }
    return false;
}

bool validateBishop(Piece piece, Piece dest) {
	if (abs(piece.position.x - dest.position.x) == abs(piece.position.y - dest.position.y)) {
		int x = piece.position.x;
		int y = piece.position.y;

		while (x != dest.position.x && y != dest.position.y) {
			if (x < dest.position.x) x++;
			else x--;

			if (y < dest.position.y) y++;
			else y--;

			Piece currPiece = getPiece((vector2) {x, y});
			if (!isEmpty(currPiece)) return false;
		}
		return true;
	}
	return false;
}

bool validateQueen(Piece piece, Piece dest) {
	return validateRook(piece, dest) || validateBishop(piece, dest);
}

bool validateKnight(Piece piece, Piece dest) {
	if (abs(piece.position.x - dest.position.x) == 2 && abs(piece.position.y - dest.position.y) == 1) return true;
	if (abs(piece.position.x - dest.position.x) == 1 && abs(piece.position.y - dest.position.y) == 2) return true;
	return false;
}

bool validateKing(Piece piece, Piece dest) {
	if (abs(piece.position.x - dest.position.x) <= 1 && abs(piece.position.y - dest.position.y) <= 1) return true;
	return false;
}

void resetValidity() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j].isValidMove = false;
		}
	}
}

bool isValidMove(vector2 from, vector2 to) {
    Piece piece = getPiece(from);
    Piece dest = getPiece(to);

    if (piece.color == dest.color) return false;

    switch (piece.name) {
        case 'p':
            if (piece.color == 'w') return validateWhitePawn(piece, dest);
            if (piece.color == 'b') return validateBlackPawn(piece, dest);
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
			return validateKing(piece, dest);
		default:
			break;
    }
    return false;
}
