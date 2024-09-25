#include <stdio.h>
#include <ctype.h>

#include "board.h"

// Function to create a new board
void createBoard() {
	// Create the white pieces
	board[7][0] = createPiece('r', 'w', 7, 0);
	board[7][1] = createPiece('n', 'w', 7, 1);
	board[7][2] = createPiece('b', 'w', 7, 2);
	board[7][3] = createPiece('q', 'w', 7, 3);
	board[7][4] = createPiece('k', 'w', 7, 4);
	board[7][5] = createPiece('b', 'w', 7, 5);
	board[7][6] = createPiece('n', 'w', 7, 6);
	board[7][7] = createPiece('r', 'w', 7, 7);
	for (int i = 0; i < SIZE; i++) {
		board[6][i] = createPiece('p', 'w', 6, i);
	}

	board[0][0] = createPiece('r', 'b', 0, 0);
	board[0][1] = createPiece('n', 'b', 0, 1);
	board[0][2] = createPiece('b', 'b', 0, 2);
	board[0][3] = createPiece('q', 'b', 0, 3);
	board[0][4] = createPiece('k', 'b', 0, 4);
	board[0][5] = createPiece('b', 'b', 0, 5);
	board[0][6] = createPiece('n', 'b', 0, 6);
	board[0][7] = createPiece('r', 'b', 0, 7);
	for (int i = 0; i < SIZE; i++) {
		board[1][i] = createPiece('p', 'b', 1, i);
	}
}

void displayBoard() {
    // Print the column labels (letters a-h)
    printf("\n  a b c d e f g h\n");
    
    for (int i = 0; i < SIZE; i++) {
        // Print the row label (numbers 1-8)
        printf("%d ", SIZE - i); // Print numbers 1-8

        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].isAlive && board[i][j].color == 'w') {
                printf("%c ", board[i][j].name); // Print white pieces
            } else if (board[i][j].isAlive && board[i][j].color == 'b') {
                printf("%c ", toupper(board[i][j].name)); // Print black pieces
            } else {
                printf(" "); // Use '.' to represent empty squares
            }
        }
        printf("\n");
    }
	printf("\n");
}

Piece getPiece(vector2 pos) {
	return board[pos.x][pos.y];
}

void init() {
	createBoard();
	displayBoard();
}
