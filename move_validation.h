#import "board.h"

void resetValidity();
bool canCapture(Piece piece, Piece dest);
bool isEmpty(Piece piece);
bool isValidMove(vector2 from, vector2 to, bool capture);
