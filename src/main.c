// Assets: https://opengameart.org/content/2d-chess-pack
#include "../include/chess.h"
#include "../include/gamestate.h"
#include "../include/render.h"
#include "../include/setup.h"
#include "../include/util.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void handleMouseButton(int x, int y) {
	if (x >= PADDING_SIZE && x <= WINDOW_HEIGHT - PADDING_SIZE &&
		y >= PADDING_SIZE && y <= WINDOW_HEIGHT - PADDING_SIZE) {
		if ((x - PADDING_SIZE) / BLOCK_DIM == selectedX &&
			(y - PADDING_SIZE) / BLOCK_DIM == selectedY) {
			selectedX = -1;
			selectedY = -1;
		}
		else {
			int nextX = (x - PADDING_SIZE) / BLOCK_DIM;
			int nextY = (y - PADDING_SIZE) / BLOCK_DIM;
			if (selectedX != -1 && selectedY != -1) {
				// TODO: check for a checkmate.
				if (validMove(selectedX, selectedY, nextX, nextY)) {
					enPassantAllowed = 0;
					// Checking for an opening that would allow en passant.
					if (validPawnMove(selectedX, selectedY, nextX, nextY) && ABS(nextY - selectedY) == 2) {
						enPassantAllowed = 1;
					}
					grid[nextY][nextX] = grid[selectedY][selectedX];
					grid[selectedY][selectedX] = ' ';
					// Pawn promotion
					if ((nextY == 0 && grid[nextY][nextX] == WHITE_PAWN) ||
					    (nextY == 7 && grid[nextY][nextX] == BLACK_PAWN)) {
						grid[nextY][nextX] = (grid[nextY][nextX] == BLACK_PAWN ? BLACK_QUEEN : WHITE_QUEEN);
					}
					selectedX = -1;
					selectedY = -1;
					turn = (turn == 'w' ? 'b' : 'w');
					if (enPassantX != -1 && enPassantY != -1) {
						grid[enPassantY][enPassantX] = ' ';
						enPassantX = -1;
						enPassantY = -1;
					}
				}
			}
			else {
				if (turn == 'b') {
					if ('1' <= grid[nextY][nextX] && grid[nextY][nextX] <= '6') {
						selectedX = nextX;
						selectedY = nextY;
					}
				}
				else if (turn == 'w') {
					if (('7' <= grid[nextY][nextX] && grid[nextY][nextX] <= '9') ||
					    ('a' <= grid[nextY][nextX] && grid[nextY][nextX] <= 'c')) {
						selectedX = nextX;
						selectedY = nextY;
					}
				}
			}
		}
	}
	else {
		selectedX = -1;
		selectedY = -1;
	}
}

int update(void) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				return 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleMouseButton(e.button.x, e.button.y);
				break;
			default:
				break;
		}
	}
	render();
	return 1;
}


int main(int argc, char** argv) {
	init();
	while (update());
	quit();
	return 0;
}
