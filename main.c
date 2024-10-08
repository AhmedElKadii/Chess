#include "main.h"
#include "board.h"

void gameLoop() {
    char move[3];
    while (1) {
		printf("lastCapture: %d\n", lastCapture);
		if (determineMate() == 'm') {
			char turn_str[10];
			char message[100];
			sprintf(turn_str, "%s", turn == 'b' ? "White" : "Black");
			sprintf(message, "Checkmate! %s wins.", turn_str);
			pim(&queue, message, 'n');
			break;
		} else if (determineMate() == 's' || lastCapture == 50) {
			char turn_str[10];
			printf("lastCapture: %d\n", lastCapture);
			pim(&queue, "Stalemate! the match is a draw...", 'n');
			break;
		}

		char turn_str[10];
		char prompt[100];

		sprintf(turn_str, "%s", turn == 'w' ? "White" : "Black");

		sprintf(prompt, "Enter your move, %s (e.g., E2, d5): ", turn_str);

		pim(&queue, prompt, 'n');
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
			if (piece.color != turn) {
				pim(&queue, "Invalid move. It's not your turn.", 'e');
				selected_piece = (vector2) {-1, -1};
				is_piece_selected = false;
				continue;
			}
        } else {
			selected_piece = (vector2) {-1, -1};
			is_piece_selected = false;
			pim(&queue, "No piece at the specified position.", 'e');
			continue;
        }

		selected_piece = pos;
		is_piece_selected = true;

		displayMoves(piece);
		displayBoard();

		pim(&queue, "Enter destination: ", 'n');
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
						pim(&queue, "Invalid move. Exposes king to check.", 'e');
					}
					else {
						if (piece.name != 'p' && isEmpty(getPiece(newPos))) lastCapture++;
						else lastCapture = 0;

						movePiece(piece, newPos, false);
						turn = turn == 'w' ? 'b' : 'w';
					}
				}
				else pim(&queue, "Invalid move. King is in check.\n", 'e');
			}
			else {
				if (exposesKingToCheck(newPos)) {
					pim(&queue, "Invalid move. Exposes king to check.", 'e');
				}
				else {
					if (piece.name != 'p' && isEmpty(getPiece(newPos))) lastCapture++;
					else lastCapture = 0;

					movePiece(piece, newPos, false);
					turn = turn == 'w' ? 'b' : 'w';
				}
			}
        } else {
			pim(&queue, "Invalid move. Try again.", 'e');
        }

		selected_piece = (vector2) {-1, -1};
		is_piece_selected = false;
		hideMoves();
        displayBoard();
		resetValidity();

		Piece* piece_ptr = getPieceAsPointer(newPos);

		if (shouldPromote(*piece_ptr)) {
			char promotion;
			bool valid = false;
			while (!valid) {
				pim(&queue, "Promote pawn to (Q)ueen, (R)ook, (B)ishop, k(N)ight: ", 'n');
				scanf(" %c", &promotion);
				promotion = tolower(promotion);
				switch (promotion) {
					case 'q':
					case 'r':
					case 'b':
					case 'n':
						valid = true;
						promotePiece(piece_ptr, promotion);
						break;
					default:
						promotion = 'c';
						pim(&queue, "Invalid Selection, Must Promote!.", 'e');
						break;
				}
				if (promotion == 'q' || promotion == 'r' || promotion == 'b' || promotion == 'n') {
					pim(&queue, "Pawn promoted.", 'w');
				}
			}
			selected_piece = (vector2) {-1, -1};
			is_piece_selected = false;
			displayBoard();
		}
    }
}

int main() {
    init();
    gameLoop();
    return 0;
}
