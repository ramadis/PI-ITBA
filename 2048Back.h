#ifndef _BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define _BACKEND_H
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

/*Recibe una posicion del tablero y verifica el contenido de los casillero aledaños*/
signed char checkAround (const typePlay * game, int row, int column);

/*Llama a funciones que retornan informacion sobre el estado actual del tablero
	(Si hay espacios vacios, esta lleno o ya se llego al numero ganador) 
		y genera el numero random luego de la jugada*/
int checkStatus (const typePlay * previousPlay, typePlay * currentPlay);

/*Copia en una estructura auxiliar la jugada actual, por si luego se ingresa un UNDO*/
void copyPlay (typePlay * destination, const typePlay * origin);

/*Recibe la dificultad deseada y retorna el numero al que se debe llegar para ganar, 
	el tamaño del tablero y los UNDO de acuerdo a la dificultad seleccionada*/
int getFromDifficulty (unsigned short int difficulty, unsigned short int * undos, unsigned int * scoreToWin);

/*Carga un juego guardado*/
unsigned char loadGame (typePlay * game, const char * loadName);

/*Crea la estructura*/
typePlay makePlay (unsigned short int difficulty, unsigned int score, unsigned short int undos);

/*Realiza el movimiento deseado (Mueve todas las fichas, suma las de igual valor)*/
int move (typePlay * game, int movement);

double randNormalize (void);
int randInt (int izq, int der);

/*Guarda el juego en el estado actual con el nombre deseado*/
char saveGame (typePlay * game, const char * filename);

/*Realiza la funcion UNDO*/
signed char undo (typePlay * currentPlay, typePlay * previousPlay);

#endif