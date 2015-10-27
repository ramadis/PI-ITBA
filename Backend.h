#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define CLEAN_BUFFER while(getchar() != '\n');
#define BLOCK 10

typedef struct {
	unsigned short int difficulty;
	unsigned int score;
	unsigned short int undos;
	unsigned short int ** board;
} typePlay;

enum states {LOSE=1, WIN, CAN_MOVE, NO_MEMORY};
enum movements {LEFT=4, RIGHT, UP, DOWN};

signed char checkAround(typePlay * game, int row, int column);
int checkStatus(typePlay * previousPlay, typePlay * currentPlay);
void copyPlay(typePlay * destination, typePlay * origin);
int getFromDifficulty(unsigned short int difficulty, unsigned short int * undos, unsigned int * scoreToWin);
unsigned char loadGame(typePlay * game, char * loadName);
typePlay makePlay(unsigned short int difficulty, unsigned int score, unsigned short int undos);
int move(typePlay * game, int movement);
double randNormalize(void);
int randInt(int izq, int der);
char saveGame(typePlay * game, char * filename);
signed char undo(typePlay * currentPlay, typePlay * previousPlay);