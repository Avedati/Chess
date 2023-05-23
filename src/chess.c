#include "../include/chess.h"
#include "../include/gamestate.h"
#include "../include/util.h"

int inGrid(int x, int y) {
	return 0 <= x && x < 8 && 0 <= y && y < 8;
}

void findKing(int color, int* kingX, int* kingY) {
	char king = (color == 'b') ? BLACK_KING : WHITE_KING;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (grid[y][x] == king) {
				*kingX = x;
				*kingY = y;
				y = 8;
				break;
			}
		}
	}
}

int kingIsInRange(char kingColor) {
	int kingX = -1, kingY = -1;
	int otherKingX = -1, otherKingY = -1;
	int valid;
	findKing(kingColor, &kingX, &kingY);
	findKing(kingColor == 'w' ? 'b' : 'w', &otherKingX, &otherKingY);
	if (kingX == -1) {
		return 0;
	}
	grid[kingY][kingX] = ' ';
	if (otherKingX != -1) {
		grid[otherKingY][otherKingX] = ' ';
	}
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((kingColor == 'b' && IS_WHITE_PIECE(grid[y][x])) ||
			    (kingColor == 'w' && IS_BLACK_PIECE(grid[y][x]))) {
				valid = validMove(x, y, kingX, kingY);
				if (kingColor == 'b' && grid[y][x] == WHITE_PAWN) {
					if (y == kingY + 1 && ABS(x - kingX) == 1) {
						valid = 1;
					}
				}
				if (kingColor == 'w' && grid[y][x] == BLACK_PAWN) {
					if (y == kingY - 1 && ABS(x - kingX) == 1) {
						valid = 1;
					}
				}
				if (valid) {
					grid[kingY][kingX] = (kingColor == 'b') ? BLACK_KING : WHITE_KING;
					grid[otherKingY][otherKingX] = (kingColor == 'b') ? WHITE_KING : BLACK_KING;
					return 1;
				}
			}
		}
	}
	grid[kingY][kingX] = (kingColor == 'b') ? BLACK_KING : WHITE_KING;
	grid[otherKingY][otherKingX] = (kingColor == 'b') ? WHITE_KING : BLACK_KING;
	return 0;
}

// TODO: improve this method
int checkmate(char kingColor) {
	int kingX, kingY;
	findKing(kingColor, &kingX, &kingY);
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) {
				continue;
			}
			if (validMove(kingX, kingY, kingX + x, kingY + y)) {
				return 0;
			}
		}
	}
	return 1;
}

int validBlackMove(int x, int y) {
	return grid[y][x] == ' ' || IS_WHITE_PEON(grid[y][x]);
}

int validWhiteMove(int x, int y) {
	return grid[y][x] == ' ' || IS_BLACK_PEON(grid[y][x]);
}

int validRookMove(int x1, int y1, int x2, int y2, int isQueen) {
	if (!inGrid(x1, y1) || !inGrid(x2, y2)) {
		return 0;
	}
	char color;
	if (isQueen) {
		if (grid[y1][x1] != BLACK_QUEEN && grid[y1][x1] != WHITE_QUEEN) {
			return 0;
		}
		color = (grid[y1][x1] == BLACK_QUEEN) ? 'b' : 'w';
	}
	else {
		if (grid[y1][x1] != BLACK_ROOK && grid[y1][x1] != WHITE_ROOK) {
			return 0;
		}
		color = (grid[y1][x1] == BLACK_ROOK) ? 'b' : 'w';
	}
	if (x1 != x2 && y1 != y2) {
		return 0;
	}
	if (x1 == x2 && y1 == y2) {
		return 0;
	}
	if (color == 'b' && !validBlackMove(x2, y2)) {
		return 0;
	}
	else if (color == 'w' && !validWhiteMove(x2, y2)) {
		return 0;
	}
	if (x1 != x2) {
		for (int i = MIN(x1, x2) + 1; i < MAX(x1, x2); i++) {
			if (grid[y1][i] != ' ') {
				return 0;
			}
		}
	}
	else if (y1 != y2) {
		for (int i = MIN(y1, y2) + 1; i < MAX(y1, y2); i++) {
			if (grid[i][x1] != ' ') {
				return 0;
			}
		}
	}
	return 1;
}

int validKnightMove(int x1, int y1, int x2, int y2) {
	if (!inGrid(x1, y1) || !inGrid(x2, y2)) {
		return 0;
	}
	if (grid[y1][x1] != BLACK_KNIGHT && grid[y1][x1] != WHITE_KNIGHT) {
		return 0;
	}
	if (SQUARE(ABS(x1 - x2)) + SQUARE(ABS(y1 - y2)) != 5) {
		return 0;
	}
	char color = (grid[y1][x1] == BLACK_KNIGHT) ? 'b' : 'w';
	if (color == 'b' && !validBlackMove(x2, y2)) {
		return 0;
	}
	else if (color == 'w' && !validWhiteMove(x2, y2)) {
		return 0;
	}
	return 1;
}

int validBishopMove(int x1, int y1, int x2, int y2, int isQueen) {
	if (!inGrid(x1, y1) || !inGrid(x2, y2)) {
		return 0;
	}
	char color;
	if (isQueen) {
		if (grid[y1][x1] != BLACK_QUEEN && grid[y1][x1] != WHITE_QUEEN) {
			return 0;
		}
		color = (grid[y1][x1] == BLACK_QUEEN) ? 'b' : 'w';
	}
	else {
		if (grid[y1][x1] != BLACK_BISHOP && grid[y1][x1] != WHITE_BISHOP) {
			return 0;
		}
		color = (grid[y1][x1] == BLACK_BISHOP) ? 'b' : 'w';
	}
	if (ABS(x1 - x2) != ABS(y1 - y2)) {
		return 0;
	}
	if (x1 == x2 && y1 == y2) {
		return 0;
	}
	if (color == 'b' && !validBlackMove(x2, y2)) {
		return 0;
	}
	else if (color == 'w' && !validWhiteMove(x2, y2)) {
		return 0;
	}
	for (int i = 1; i < ABS(x1 - x2); i++) {
		if (grid[y1 + SIGN(y2 - y1) * i][x1 + SIGN(x2 - x1) * i] != ' ') {
			return 0;
		}
	}
	return 1;
}

int validQueenMove(int x1, int y1, int x2, int y2) {
	return validRookMove(x1, y1, x2, y2, 1) || validBishopMove(x1, y1, x2, y2, 1);
}

int validKingMove(int x1, int y1, int x2, int y2) {
	if (!inGrid(x1, y1) || !inGrid(x2, y2)) {
		return 0;
	}
	if (grid[y1][x1] != BLACK_KING && grid[y1][x1] != WHITE_KING) {
		return 0;
	}
	if (SQUARE(ABS(x1 - x2)) + SQUARE(ABS(y1 - y2)) != 1 && 
	    SQUARE(ABS(x1 - x2)) + SQUARE(ABS(y1 - y2)) != 2) {
		return 0;
	}
	char color = (grid[y1][x1] == BLACK_KING) ? 'b' : 'w';
	if (color == 'b' && !validBlackMove(x2, y2)) {
		return 0;
	}
	else if (color == 'w' && !validWhiteMove(x2, y2)) {
		return 0;
	}
	char old = grid[y2][x2];
	grid[y2][x2] = grid[y1][x1];
	grid[y1][x1] = ' ';
	int result = kingIsInRange(color);
	grid[y1][x1] = grid[y2][x2];
	grid[y2][x2] = old;
	return !result;
} 

int validPawnMove(int x1, int y1, int x2, int y2) {
	if (!inGrid(x1, y1) || !inGrid(x2, y2)) {
		return 0;
	}
	if (grid[y1][x1] != BLACK_PAWN && grid[y1][x1] != WHITE_PAWN) {
		return 0;
	}
	char color = (grid[y1][x1] == BLACK_PAWN) ? 'b' : 'w';
	if (color == 'b') {
		if (!validBlackMove(x2, y2)) {
			return 0;
		}
		if (y1 == 1 && (y2 == 2 || y2 == 3) && x1 == x2 && grid[y2][x2] == ' ') {
			return 1;
		}
		if (y2 == y1 + 1) {
			if (ABS(x1 - x2) == 1) {
				if (grid[y2][x2] != ' ') {
					return 1;
				}
				else if (enPassantAllowed) {
					if (inGrid(x2, y1) && IS_WHITE_PEON(grid[y1][x2])) {
						enPassantX = x2;
						enPassantY = y1;
						return 1;
					}
					return 0;
				}
			}
			if (x1 == x2 && grid[y2][x2] == ' ') {
				return 1;
			}
		}
	}
	else if (color == 'w') {
		if (!validWhiteMove(x2, y2)) {
			return 0;
		}
		if (y1 == 6 && (y2 == 5 || y2 == 4) && x1 == x2 && grid[y2][x2] == ' ') {
			return 1;
		}
		if (y2 == y1 - 1) {
			if (ABS(x1 - x2) == 1) {
				if (grid[y2][x2] != ' ') {
					return 1;
				}
				else if (enPassantAllowed) {
					if (inGrid(x2, y1) && IS_BLACK_PEON(grid[y1][x2])) {
						enPassantX = x2;
						enPassantY = y1;
						return 1;
					}
					return 0;
				}
			}
			if (x1 == x2 && grid[y2][x2] == ' ') {
				return 1;
			}
		}
	}
	return 0;
} 

int validMove(int x1, int y1, int x2, int y2) {
	if (!inGrid(x1, y1) || !inGrid(x2, y2)) {
		return 0;
	}
	char me = IS_BLACK_PIECE(grid[y1][x1]) ? 'b' : 'w';
	int valid = validRookMove(x1, y1, x2, y2, 0) ||
	       validKnightMove(x1, y1, x2, y2) ||
	       validBishopMove(x1, y1, x2, y2, 0) ||
	       validQueenMove(x1, y1, x2, y2) ||
	       validKingMove(x1, y1, x2, y2) ||
	       validPawnMove(x1, y1, x2, y2);
	if (valid) {
		char temp = grid[y2][x2];
		grid[y2][x2] = grid[y1][x1];
		grid[y1][x1] = ' ';
		int result = kingIsInRange(me);
		grid[y1][x1] = grid[y2][x2];
		grid[y2][x2] = temp;
		return !result;
	}
	return 0;
}
