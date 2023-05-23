#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_ 0

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_TITLE "C Chess - Version 0.0.1"
#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 680
#define BLOCK_DIM 80
#define PADDING_SIZE ( (WINDOW_HEIGHT - BLOCK_DIM * 8) / 2 )
#define FONT_SIZE 48
#define NUMBER_WIDTH 8
#define LETTER_HEIGHT 16

#define BLACK_PAWN '1'
#define BLACK_ROOK '2'
#define BLACK_KNIGHT '3'
#define BLACK_BISHOP '4'
#define BLACK_QUEEN '5'
#define BLACK_KING '6'
#define IS_BLACK_PIECE(x) ( x == BLACK_PAWN || x == BLACK_ROOK || x == BLACK_KNIGHT || x == BLACK_BISHOP || x == BLACK_QUEEN || x == BLACK_KING )
#define IS_BLACK_PEON(x) ( IS_BLACK_PIECE(x) && x != BLACK_KING )

#define WHITE_PAWN 'c'
#define WHITE_ROOK '7'
#define WHITE_KNIGHT '8'
#define WHITE_BISHOP '9'
#define WHITE_QUEEN 'a'
#define WHITE_KING 'b'
#define IS_WHITE_PIECE(x) ( x == WHITE_PAWN || x == WHITE_ROOK || x == WHITE_KNIGHT || x == WHITE_BISHOP || x == WHITE_QUEEN || x == WHITE_KING )
#define IS_WHITE_PEON(x) ( IS_WHITE_PIECE(x) && x != WHITE_KING )

SDL_Window* win;
SDL_Renderer* ren;
TTF_Font* font;
SDL_Texture* numbers[8];
SDL_Texture* letters[8];
SDL_Texture* blackPieces;
SDL_Texture* whitePieces;

int selectedX;
int selectedY;

int enPassantX;
int enPassantY;
int enPassantAllowed;
char turn;
char** grid;

#endif // __GAME_STATE_H_
