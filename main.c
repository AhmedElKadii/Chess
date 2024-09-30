#include <stdio.h>

#include "main.h"
#include "board.h"

void gameLoop() {
    char move[3];
    while (1) {
        printf("Enter your move (e.g., E2, d5): ");
        scanf("%s", move);

		int x = tolower(move[0]) - 'a';  // Convert 'a' to 0, 'b' to 1, etc.
		int y = SIZE - (move[1] - '0');  // Convert '1' to SIZE-1, '2' to SIZE-2, etc.

		// Check if x is out of bounds (less than 0 or greater than SIZE-1)
		if (x < 0 || x >= SIZE) {
			x = -1;  // Set to -1 if out of bounds
		}

		// Check if y is out of bounds (less than 0 or greater than SIZE-1)
		if (y < 0 || y >= SIZE) {
			y = -1;  // Set to -1 if out of bounds
		}

        vector2 pos = new_vector2(x, y);
        Piece piece = getPiece(pos);

        if (!isEmpty(piece) && y != -1 && x != -1) {
            printf("\nPiece at position: %c\n", piece.name);
        } else {
			resetValidity();
			selected_piece = (vector2) {-1, -1};
            printf("\nNo piece at the specified position.\n");
			continue;
        }

		selected_piece = pos;

		displayMoves(piece);
		displayBoard();

        printf("Enter destination: ");
        scanf("%s", move);

        x = tolower(move[0]) - 'a';
        y = SIZE - (move[1] - '0');

		// Check if x is out of bounds (less than 0 or greater than SIZE-1)
		if (x < 0 || x >= SIZE) {
			x = -1;  // Set to -1 if out of bounds
		}

		// Check if y is out of bounds (less than 0 or greater than SIZE-1)
		if (y < 0 || y >= SIZE) {
			y = -1;  // Set to -1 if out of bounds
		}

        vector2 newPos = new_vector2(x, y);

        if (isValidMove(pos, newPos, true) && y != -1 && x != -1) {
            movePiece(piece, newPos);
        } else {
            printf("Invalid move.\n");
        }

		selected_piece = (vector2) {-1, -1};
		hideMoves();
        displayBoard();
    }
}

int main() {
    init();
    gameLoop();
    return 0;
}
