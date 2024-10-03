#include "main.h"
#include "board.h"

void gameLoop() {
    char move[3];
    while (1) {
		if (isInMate()) {
			char turn_str[10];
			sprintf(turn_str, "%s", turn == 'w' ? "White" : "Black");
			pim(&queue, strcat("Checkmate! %s wins.", turn_str), false);
			break;
		}

		char turn_str[10];
		char prompt[100];

		sprintf(turn_str, "%s", turn == 'w' ? "White" : "Black");

		sprintf(prompt, "Enter your move, %s (e.g., E2, d5): ", turn_str);

		pim(&queue, prompt, false);
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
			char buffer[100];

			sprintf(buffer, "piece at position: %c", piece.name);

			if (piece.color == turn) pim(&queue, buffer, false);
			else {
				pim(&queue, "Invalid move. It's not your turn.", true);
				selected_piece = (vector2) {-1, -1};
				is_piece_selected = false;
				continue;
			}
        } else {
			resetValidity();
			selected_piece = (vector2) {-1, -1};
			is_piece_selected = false;
			pim(&queue, "No piece at the specified position.\n", true);
			continue;
        }

		selected_piece = pos;
		is_piece_selected = true;

		displayMoves(piece);
		displayBoard();

		pim(&queue, "Enter destination: ", false);
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
						pim(&queue, "Invalid move. Exposes king to check.", true);
					}
					else {
						movePiece(piece, newPos, false);
						turn = turn == 'w' ? 'b' : 'w';
					}
				}
				else pim(&queue, "Invalid move. King is in check.", true);
			}
			else {
				if (exposesKingToCheck(newPos)) {
					pim(&queue, "Invalid move. Exposes king to check.", true);
				}
				else {
					movePiece(piece, newPos, false);
					turn = turn == 'w' ? 'b' : 'w';
				}
			}
        } else {
			pim(&queue, "Invalid move. Try again.", true);
        }

		hideMoves();
        displayBoard();
		resetValidity();
		selected_piece = (vector2) {-1, -1};
		is_piece_selected = false;
    }
}

int main() {
    init();
    gameLoop();
    return 0;
}
