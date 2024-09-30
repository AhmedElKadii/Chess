#include <stdio.h>

#include "settings.h"
#include "piece.h"
#include "custom_boards.h"
#include "move_validation.h"

vector2 selected_piece;
Piece board[SIZE][SIZE];
Piece* lastMovedPiece;
char turn;

void createBoard();
void displayBoard();
Piece getPiece(vector2 pos);
Piece* getPieceAsPointer(vector2 pos);
int getValidMoves(Piece piece);
void capturePiece(Piece piece);
void movePiece(Piece piece, vector2 pos, bool isTemp);
void init();
