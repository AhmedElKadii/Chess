#include "board.h"
#include "move_validation.h"

vector2 getKingPosition();
bool isInCheck(vector2 dest);
bool exposesKingToCheck(vector2 dest);
bool isInMate(vector2 dest);
