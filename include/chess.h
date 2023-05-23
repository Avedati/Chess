#ifndef __CHESS_H_
#define __CHESS_H_ 0

int inGrid(int, int);
void findKing(int, int*, int*);
int checkmate(char);
int kingIsInRange(char);
int validBlackMove(int, int);
int validWhiteMove(int, int);
int validRookMove(int, int, int, int, int);
int validKnightMove(int, int, int, int);
int validBishopMove(int, int, int, int, int);
int validQueenMove(int, int, int, int);
int validKingMove(int, int, int, int);
int validPawnMove(int, int, int, int);
int validMove(int, int, int, int);

#endif // __CHESS_H_
