#include "backEnd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum options {PLAY=1, LOAD, EXIT};

int main(){
	typePlay currentPlay, previousPlay;
	unsigned short int auxUndos;
	unsigned char option;

	do {
		auxUndos = 0;
		option = readMenu();
		int size, filRand, colRand, i;

		switch(option){
			case PLAY:
				currentPlay.difficulty = readDifficulty();
				size = getFromDifficulty(currentPlay.difficulty, &auxUndos, NULL);
				currentPlay = makePlay(currentPlay.difficulty, auxUndos, 0);
				previousPlay = makePlay(currentPlay.difficulty, auxUndos-1, 0);

				if(currentPlay == NULL || previousPlay == NULL){
					printf("\nNo se pudo generar el tablero");
					option = EXIT;
				}

				for(i=0;option != EXIT && i<2;i++){
					do{
						filRand = randInt(0, size-1);
						colRand = randInt(0, size-1);
					}while(currentPlay.board[filRand][colRand] != 0);
					currentPlay.board[filRand][colRand] = 2 + 2 * (randInt(1, 100) < 12);
				}

				option = play(&previousPlay, &currentPlay)? option: EXIT;
				break;
			case LOAD:
				wrapLoad(&currentPlay); //Desde aca adentro se llama a makePlay, getFromDifficulty, etc..
				option = play(&previousPlay, &currentPlay)? option: EXIT;
				break;
			case EXIT:
				printf("\nVolve cuando quieras!");
				break;
			default:
				printf("\nSeleccione una opcion correcta");
				break;
		}
	}while(option != EXIT);

	return 0;
}
