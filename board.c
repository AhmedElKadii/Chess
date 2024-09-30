#include "board.h"

void setCustomBoard(char customMap[SIZE][SIZE]) {
    for (int y = 0; y < SIZE; y++) {  // Use y before x for consistency
        for (int x = 0; x < SIZE; x++) {
            char pieceType = customMap[y][x];  // Use customMap[y][x] for correct order
            char color = ' ';

            // Set color based on the piece type ('w' for white, 'b' for black)
            if (pieceType >= 'A' && pieceType <= 'Z') {
                color = 'b';  // Capital letters represent black pieces
            } else if (pieceType >= 'a' && pieceType <= 'z') {
                color = 'w';  // Lowercase letters represent white pieces
            }

            // Create a piece for each position on the board
            board[x][y] = createPiece(tolower(pieceType), color, x, y);  // Ensure coordinates are x, y
        }
    }
}

void createBoard() {
    char defaultBoard[SIZE][SIZE] = SELECTED_BOARD;
    setCustomBoard(defaultBoard);
}

void displayBoard() {
    printf("\n  a b c d e f g h\n");
    for (int y = 0; y < SIZE; y++) {
        printf("%d ", SIZE - y);
        for (int x = 0; x < SIZE; x++) {
            if (!isEmpty(board[x][y]) && board[x][y].color == 'w') {
                // Highlight or print white pieces
                if (equals((vector2){x, y}, selected_piece) && HIGHLIGHT) {
                    printf("\033[033m%c \033[0m", board[x][y].name);  // Highlight white piece
                } else if (board[x][y].isValidMove && HIGHLIGHT) {
                    printf("\033[032m%c \033[0m", board[x][y].name);  // Valid move highlighting
                } else {
                    printf("%c ", board[x][y].name);  // Regular white piece display
                }
            } else if (!isEmpty(board[x][y]) && board[x][y].color == 'b') {
                // Highlight or print black pieces
                if (equals((vector2){x, y}, selected_piece) && HIGHLIGHT) {
                    printf("\033[033m%c \033[0m", toupper(board[x][y].name));  // Highlight black piece
                } else if (board[x][y].isValidMove && HIGHLIGHT) {
                    printf("\033[032m%c \033[0m", toupper(board[x][y].name));  // Valid move highlighting
                } else {
                    printf("%c ", toupper(board[x][y].name));  // Regular black piece display
                }
            } else if (isEmpty(board[x][y]) && board[x][y].isValidMove && SHOW_MOVES) {
                if (HIGHLIGHT) printf("\033[33m* \033[0m");  // Highlight empty square
                else printf("* ");
            } else {
                printf("  ");  // Print empty square
            }
        }
        printf("\n");
    }
    printf("\n");
}

Piece getPiece(vector2 pos) {
    return board[pos.x][pos.y]; // x first, then y
}

Piece* getPieceAsPointer(vector2 pos) {
    return &board[pos.x][pos.y]; // x first, then y
}

int getValidMoves(Piece piece) {
	int count = 0;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			vector2 pos = {x, y};

			if (isValidMove(piece.position, pos, false)) {
				count++;
			}
		}
	}
	return count;
}

void capturePiece(Piece piece) {
    board[piece.position.x][piece.position.y] = createPiece(' ', ' ', piece.position.x, piece.position.y);
}

void movePiece(Piece piece, vector2 pos, bool isTemp) {
	capturePiece(piece);

    int xDiff = pos.x - piece.position.x;
    int yDiff = pos.y - piece.position.y;

    piece.position.x = pos.x;
    piece.position.y = pos.y;

	int Diff = xDiff == yDiff ? xDiff : xDiff != 0 ? xDiff : yDiff;

	if (!isTemp) {
		piece.totalMoves += abs(Diff);
		piece.lastMove = abs(Diff);
	}

    board[pos.x][pos.y] = piece;

	if (isTemp) return;

	if (lastMovedPiece != NULL) {
		printf("Last move: %d\n", lastMovedPiece->lastMove);
		printf("Last moved piece: %c\n", lastMovedPiece->name);
		lastMovedPiece->lastMove = 0;
	}

	lastMovedPiece = getPieceAsPointer(pos);
}

void init() {
	selected_piece = (vector2) {-1,-1};
    createBoard();
    displayBoard();
	turn = FIRST_TO_PLAY;
}
