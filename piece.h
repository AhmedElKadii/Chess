#include "structs.h"

typedef struct {
	char name;
	char color;
	vector2 position;
	int lastMove;
	int totalMoves;
	bool isValidMove;
} Piece;

Piece createPiece(char name, char color, int x, int y);
void promotePiece(Piece *piece, char name);
bool shouldPromote(Piece piece);
