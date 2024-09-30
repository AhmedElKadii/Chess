#include "settings.h"

#include "piece.h"

vector2 selected_piece;
Piece board[SIZE][SIZE];
Piece* lastMovedPiece;

void createBoard();
void displayBoard();
Piece getPiece(vector2 pos);
Piece* getPieceAsPointer(vector2 pos);
void capturePiece(Piece piece);
void movePiece(Piece piece, vector2 pos);
void init();
