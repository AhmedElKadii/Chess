#include "settings.h"

#include "piece.h"

Piece board[SIZE][SIZE];

void createBoard();
void displayBoard();
Piece getPiece(vector2 pos);
void movePiece(Piece piece, vector2 pos);
void init();
