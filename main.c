#include <stdio.h>

#include "main.h"
#include "board.h"

void gameLoop() {
    char move[3];
    while (1) {
		if (isInMate()) {
			printf("Checkmate! %s wins.\n", turn == 'w' ? "Black" : "White");
			break;
		}
        printf("\nEnter your move, %s (e.g., E2, d5): ", turn == 'w' ? "White" : "Black");
        scanf("%s", move);

		int x = tolower(move[0]) - 'a';
		int y = SIZE - (move[1] - '0');

		if (x < 0 || x >= SIZE) {
			x = -1;
		}

		if (y < 0 || y >= SIZE) {
			y = -1;
		}

        vector2 pos = new_vector2(x, y);
        Piece piece = getPiece(pos);

        if (!isEmpty(piece) && y != -1 && x != -1) {
			if (piece.color == turn) printf("\nPiece at position: %c\n", piece.name);
			else {
				printf("\nInvalid move. It's not your turn.\n");
				continue;
			}
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

		if (x < 0 || x >= SIZE) {
			x = -1;
		}

		if (y < 0 || y >= SIZE) {
			y = -1;
		}

        vector2 newPos = new_vector2(x, y);

        if (isValidMove(pos, newPos, true) && y != -1 && x != -1) {
			if (!equals(getKingPosition(), selected_piece)) {
				if (!isInCheck()) {
					if (exposesKingToCheck(newPos)) {
						printf("Invalid move. Exposes king to check.\n");
					}
					else {
						movePiece(piece, newPos, false);
						turn = turn == 'w' ? 'b' : 'w';
					}
				}
				else printf("Invalid move. You are in check.\n");
			}
			else {
				if (exposesKingToCheck(newPos)) {
					printf("Invalid move. Exposes king to check.\n");
				}
				else {
					movePiece(piece, newPos, false);
					turn = turn == 'w' ? 'b' : 'w';
				}
			}
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
