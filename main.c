#include <stdio.h>

#include "main.h"

void gameLoop() {
    char move[3];
    while (1) {
        printf("Enter your move (e.g., E2, d5): ");
        scanf("%s", move);

        int x = tolower(move[0]) - 'a'; // Convert 'a' to 0, 'b' to 1, etc.
        int y = SIZE - (move[1] - '0'); // Convert '1' to 7, '2' to 6, etc.

        vector2 pos = new_vector2(x, y);
        Piece piece = getPiece(pos);

        if (piece.isAlive) {
            printf("Piece at position: %c\n", piece.name);
        } else {
            printf("No piece at the specified position.\n");
        }

		displayMoves(piece);
		displayBoard();

        printf("Enter destination: ");
        scanf("%s", move);

        x = tolower(move[0]) - 'a';
        y = SIZE - (move[1] - '0');

        vector2 newPos = new_vector2(x, y);

        if (isValidMove(pos, newPos)) {
            movePiece(piece, newPos);
        } else {
            printf("Invalid move.\n");
        }

		hideMoves();
        displayBoard();
    }
}

int main() {
    init();
    gameLoop();
    return 0;
}
