#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define CLEAN_BUFFER while(getchar() != '\n');
#define BLOCK 10
#define CHANCES_4 11
#define EMPTY 0

enum states {LOSE = 1, WIN, CAN_MOVE, NO_MEMORY};
enum movements {UNDO = 1, SAVE, QUIT, LEFT, RIGHT, UP, DOWN, OTHER_MOVE, EXCEPTION};
enum levels {EASY = 1, MODERATE, HARD};
enum responses {ERROR = 0, SUCCESS};

typedef struct {
	unsigned short int difficulty;
	unsigned int score;
	unsigned short int undos;
	unsigned short int ** board;
	unsigned int size;
} typePlay;

signed char checkAround (const typePlay * game, int row, int column);
int checkStatus (const typePlay * previousPlay, typePlay * currentPlay);
void copyPlay (typePlay * destination, const typePlay * origin);
int getFromDifficulty (unsigned short int difficulty, unsigned short int * undos, unsigned int * scoreToWin);
unsigned char loadGame (typePlay * game, const char * loadName);
typePlay makePlay (unsigned short int difficulty, unsigned int score, unsigned short int undos);
int move (typePlay * game, int movement);
double randNormalize (void);
int randInt (int izq, int der);
char saveGame (typePlay * game, const char * filename);
signed char undo (typePlay * currentPlay, typePlay * previousPlay);
