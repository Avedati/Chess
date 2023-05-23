#include "../include/chess.h"
#include "../include/render.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void fillRect(int x, int y, int w, int h, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(ren, r, g, b, a);
	const SDL_Rect rect = { .x = x, .y = y, .w = w, .h = h };
	SDL_RenderFillRect(ren, &rect);
}

// https://www.parallelrealities.co.uk/tutorials/ttf/ttf1.php
// https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
SDL_Texture* renderText(char* text, int r, int g, int b) {
	SDL_Color color = {r, g, b};
	SDL_Surface* surf = TTF_RenderText_Solid(font, text, color);
	if (surf == NULL) {
		printf("renderText: %s\n", TTF_GetError());
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == NULL) {
		printf("renderText: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(surf);
	return texture;
}

// https://github.com/libsdl-org/SDL_image
SDL_Texture* loadImage(const char* path) {
	SDL_Surface* surf = IMG_Load(path);
	if (surf == NULL) {
		printf("loadImage: %s\n", IMG_GetError());
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == NULL) {
		printf("loadImage: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(surf);
	return texture;
}

void drawPiece(char color, int i, int j, int x, int y, int w, int h) {
	SDL_Rect srcrect = { .x = x, .y = y, .w = w, .h = h };
	SDL_Rect dstrect = { .x = PADDING_SIZE + BLOCK_DIM * i, .y = PADDING_SIZE + BLOCK_DIM * j,
	                     .w = BLOCK_DIM, .h = BLOCK_DIM };
	SDL_RenderCopy(ren, color == 'b' ? blackPieces : whitePieces, &srcrect, &dstrect);
}

void drawPawn(char color, int i, int j) { drawPiece(color, i, j, 0, 384, 128, 128); }

void drawRook(char color, int i, int j) { drawPiece(color, i, j, 384, 256, 128, 128); }

void drawKnight(char color, int i, int j) { drawPiece(color, i, j, 384, 128, 128, 128); }

void drawBishop(char color, int i, int j) { drawPiece(color, i, j, 384, 0, 128, 128); }

void drawQueen(char color, int i, int j) { drawPiece(color, i, j, 256, 256, 128, 128); }

void drawKing(char color, int i, int j) { drawPiece(color, i, j, 0, 256, 128, 128); }

void drawPieces(void) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			switch (grid[y][x]) {
				case '1':
					drawPawn('b', x, y);
					break;
				case '2':
					drawRook('b', x, y);
					break;
				case '3':
					drawKnight('b', x, y);
					break;
				case '4':
					drawBishop('b', x, y);
					break;
				case '5':
					drawQueen('b', x, y);
					break;
				case '6':
					drawKing('b', x, y);
					break;
				case '7':
					drawRook('w', x, y);
					break;
				case '8':
					drawKnight('w', x, y);
					break;
				case '9':
					drawBishop('w', x, y);
					break;
				case 'a':
					drawQueen('w', x, y);
					break;
				case 'b':
					drawKing('w', x, y);
					break;
				case 'c':
					drawPawn('w', x, y);
					break;
				default:
					break;
			}
		}
	}
}

void drawIndices(void) {
	SDL_Rect dstrect;
	for (int i = 0; i < 8; i++) {
		dstrect.x = (PADDING_SIZE - NUMBER_WIDTH) / 2;
		dstrect.y = PADDING_SIZE + BLOCK_DIM * i + BLOCK_DIM * 3 / 8;
		dstrect.w = NUMBER_WIDTH;
		dstrect.h = BLOCK_DIM / 4;
		SDL_RenderCopy(ren, numbers[7 - i], NULL, &dstrect);
		dstrect.x = WINDOW_HEIGHT - 14;
		SDL_RenderCopy(ren, numbers[7 - i], NULL, &dstrect);

		dstrect.x = PADDING_SIZE + BLOCK_DIM * i + BLOCK_DIM * 7 / 16;
		dstrect.y = (PADDING_SIZE - LETTER_HEIGHT) / 2;
		dstrect.w = BLOCK_DIM / 8;
		dstrect.h = LETTER_HEIGHT;
		SDL_RenderCopy(ren, letters[i], NULL, &dstrect);
		dstrect.y = WINDOW_HEIGHT - 18;
		SDL_RenderCopy(ren, letters[i], NULL, &dstrect);
	}
}

void drawGrid(void) {
	int index = 0;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (x == selectedX && y == selectedY) {
				fillRect(PADDING_SIZE + x * BLOCK_DIM, PADDING_SIZE + y * BLOCK_DIM,
						 BLOCK_DIM, BLOCK_DIM, 102, 204, 102, 255);
			}
			else if (validMove(selectedX, selectedY, x, y)) {
				fillRect(PADDING_SIZE + x * BLOCK_DIM, PADDING_SIZE + y * BLOCK_DIM,
						 BLOCK_DIM, BLOCK_DIM, 102, 102, 204, 255);
			}
			else {
				if ((index + y) % 2 == 0) {
					fillRect(PADDING_SIZE + x * BLOCK_DIM, PADDING_SIZE + y * BLOCK_DIM,
							 BLOCK_DIM, BLOCK_DIM, 245, 222, 179, 255);
				}
				else {
					fillRect(PADDING_SIZE + x * BLOCK_DIM, PADDING_SIZE + y * BLOCK_DIM,
							 BLOCK_DIM, BLOCK_DIM, 210, 125, 45, 255);
				}
			}
			index++;
		}
	}
}

void render(void) {
	SDL_SetRenderDrawColor(ren, 26, 26, 28, 255);
	SDL_RenderClear(ren);

	drawGrid();
	drawIndices();
	drawPieces();

	SDL_RenderPresent(ren);
}
