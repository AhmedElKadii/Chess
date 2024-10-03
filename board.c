#include "board.h"

void setCustomBoard(char customMap[SIZE][SIZE]) {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            char pieceType = customMap[y][x];
            char color = ' ';

            if (pieceType >= 'A' && pieceType <= 'Z') {
                color = 'b';
            } else if (pieceType >= 'a' && pieceType <= 'z') {
                color = 'w';
            }

            board[x][y] = createPiece(tolower(pieceType), color, x, y);
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
                if (equals((vector2){x, y}, selected_piece) && HIGHLIGHT) {
                    printf("\033[033m%c \033[0m", board[x][y].name);
                } else if (board[x][y].isValidMove && HIGHLIGHT) {
                    printf("\033[032m%c \033[0m", board[x][y].name);
                } else {
                    printf("%c ", board[x][y].name);
                }
            } else if (!isEmpty(board[x][y]) && board[x][y].color == 'b') {
                if (equals((vector2){x, y}, selected_piece) && HIGHLIGHT) {
                    printf("\033[033m%c \033[0m", toupper(board[x][y].name));
                } else if (board[x][y].isValidMove && HIGHLIGHT) {
                    printf("\033[032m%c \033[0m", toupper(board[x][y].name));
                } else {
                    printf("%c ", toupper(board[x][y].name));
                }
            } else if (isEmpty(board[x][y]) && board[x][y].isValidMove && SHOW_MOVES) {
                if (HIGHLIGHT) printf("\033[33m* \033[0m");
                else printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

Piece getPiece(vector2 pos) {
    return board[pos.x][pos.y];
}

Piece* getPieceAsPointer(vector2 pos) {
    return &board[pos.x][pos.y];
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

	if (lastMovedPiece != NULL) { lastMovedPiece->lastMove = 0; }

	lastMovedPiece = getPieceAsPointer(pos);
}

void init() {
	lastMovedPiece = NULL;
	selected_piece = (vector2) {-1,-1};
	is_piece_selected = false;
	init_message_queue(&queue);
    createBoard();
    displayBoard();
	turn = FIRST_TO_PLAY;
}
