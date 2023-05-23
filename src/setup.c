#include "../include/gamestate.h"
#include "../include/render.h"
#include "../include/setup.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

void initModules(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("initModules: %s\n", SDL_GetError());
	}
	if (TTF_Init() == -1) {
		printf("initModules: %s\n", TTF_GetError());
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("initModules: %s\n", IMG_GetError());
	}
}

void initGlyphs(void) {
	char* numberTexts[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };
	char* letterTexts[8] = { "a", "b", "c", "d", "e", "f", "g", "h" };
	for (int i = 0; i < 8; i++) {
		numbers[i] = renderText(numberTexts[i], 255, 255, 255);
		letters[i] = renderText(letterTexts[i], 255, 255, 255);
	}
}

void initGrid(void) {
	grid = malloc(sizeof(char*) * 8);
	for (int i = 0; i < 8; i++) {
		grid[i] = malloc(sizeof(char) * 9);
	}
	strcpy(grid[0], "23456432");
	strcpy(grid[1], "11111111");
	strcpy(grid[2], "        ");
	strcpy(grid[3], "        ");
	strcpy(grid[4], "        ");
	strcpy(grid[5], "        ");
	strcpy(grid[6], "cccccccc");
	strcpy(grid[7], "789ab987");
}

void initCoords(void) {
	selectedX = -1;
	selectedY = -1;
}

void init(void) {
	initModules();
	initGrid();
	initCoords();
	win = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	font = TTF_OpenFont("res/Anonymous_Pro.ttf", FONT_SIZE);
	enPassantAllowed = 0;
	enPassantX = -1;
	enPassantY = -1;
	turn = 'w';
	initGlyphs();
	blackPieces = loadImage("res/BlackPieces.png");
	whitePieces = loadImage("res/WhitePieces.png");
}

void freeGrid(void) {
	for (int i = 0; i < 8; i++) {
		free(grid[i]);
	}
	free(grid);
}

void quit(void) {
	TTF_CloseFont(font);
	for (int i = 0; i < 8; i++) {
		SDL_DestroyTexture(numbers[i]);
		SDL_DestroyTexture(letters[i]);
	}
	SDL_DestroyTexture(blackPieces);
	SDL_DestroyTexture(whitePieces);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	freeGrid();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
