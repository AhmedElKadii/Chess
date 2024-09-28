#include <stdio.h>
#include <ctype.h>

#include "board.h"
#include "move_validation.h"

void createBoard() {
    board[0][7] = createPiece('r', 'w', 0, 7);
    board[1][7] = createPiece('n', 'w', 1, 7);
    board[2][7] = createPiece('b', 'w', 2, 7);
    board[3][7] = createPiece('q', 'w', 3, 7);
    board[4][7] = createPiece('k', 'w', 4, 7);
    board[5][7] = createPiece('b', 'w', 5, 7);
    board[6][7] = createPiece('n', 'w', 6, 7);
    board[7][7] = createPiece('r', 'w', 7, 7);
    for (int i = 0; i < SIZE; i++) {
        board[i][6] = createPiece('p', 'w', i, 6);
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[j][i] = createPiece(' ', ' ', j, i); // use x, y
        }
    }

    board[0][0] = createPiece('r', 'b', 0, 0);
    board[1][0] = createPiece('n', 'b', 1, 0);
    board[2][0] = createPiece('b', 'b', 2, 0);
    board[3][0] = createPiece('q', 'b', 3, 0);
    board[4][0] = createPiece('k', 'b', 4, 0);
    board[5][0] = createPiece('b', 'b', 5, 0);
    board[6][0] = createPiece('n', 'b', 6, 0);
    board[7][0] = createPiece('r', 'b', 7, 0);
    for (int i = 0; i < SIZE; i++) {
        board[i][1] = createPiece('p', 'b', i, 1);
    }
}

void displayBoard() {
    printf("\n  a b c d e f g h\n");
    for (int y = 0; y < SIZE; y++) {
        printf("%d ", SIZE - y); // row label (numbers 1-8)
        for (int x = 0; x < SIZE; x++) {
            if (!isEmpty(board[x][y]) && board[x][y].color == 'w') {
                printf("%c ", board[x][y].name); // white pieces
            } else if (!isEmpty(board[x][y]) && board[x][y].color == 'b') {
                printf("%c ", toupper(board[x][y].name)); // black pieces
			} else if (isEmpty(board[x][y]) && board[x][y].isValidMove) {
				printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

Piece getPiece(vector2 pos) {
    return board[pos.x][pos.y]; // x first, then y
}

void movePiece(Piece piece, vector2 pos) {
    board[piece.position.x][piece.position.y] = createPiece(' ', ' ', piece.position.x, piece.position.y);

    int xDiff = pos.x - piece.position.x;
    int yDiff = pos.y - piece.position.y;

    piece.position.x = pos.x;
    piece.position.y = pos.y;

	int Diff = xDiff == yDiff ? xDiff : xDiff != 0 ? xDiff : yDiff;

    piece.totalMoves += abs(Diff);
    piece.lastMove = abs(Diff);

    board[pos.x][pos.y] = piece;
}

void init() {
    createBoard();
    displayBoard();
}
