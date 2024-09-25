#include <stdio.h>

#include "board.h"

void gameLoop() {
    char move[3];
    while (1) {
        printf("Enter your move (e.g., E2, d5): ");
        scanf("%s", move);
        
        if (tolower(move[0]) < 'a' || tolower(move[0]) > 'h' || tolower(move[1]) < '1' || tolower(move[1]) > '8') {
            printf("Invalid move. Please use the format: <letter><number> (e.g., e2, d5).\n");
            continue;
        }

        int x = SIZE - (tolower(move[1]) - '0');
        int y = tolower(move[0]) - 'a';

        vector2 pos = new_vector2(x, y);

        printf("You entered: %s\n", move);
        printf("Vector2 position: (%d, %d)\n", pos.x, pos.y);

		Piece piece = getPiece(pos);

        if (piece.isAlive) { 
            printf("Piece at position: %c\n", piece.name);
        } else {
            printf("No piece at the specified position.\n");
        }
    }
}

int main() {
	init();
	gameLoop();
	return 0;
}
