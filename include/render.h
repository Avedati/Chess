#ifndef __RENDER_H_
#define __RENDER_H_

#include "gamestate.h"
#include <SDL2/SDL.h>

void fillRect(int, int, int, int, int, int, int, int);
SDL_Texture* renderText(char*, int, int, int);
SDL_Texture* loadImage(const char*);
void drawPiece(char, int, int, int, int, int, int);
void drawPawn(char, int, int);
void drawRook(char, int, int);
void drawKnight(char, int, int);
void drawBishop(char, int, int);
void drawQueen(char, int, int);
void drawKing(char, int, int);
void drawPieces(void);
void drawIndices(void);
void drawGrid(void);
void render(void);

#endif // __RENDER_H_
