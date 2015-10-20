#include "backEnd.h"

int main(){
	typePlay currentPlay, previousPlay;
	unsigned short int auxUndos;

	do {
		auxUndos = 0;
		option = readMenu();

		switch(option){
			case 1:
				currentPlay.difficulty = readDifficulty();
				getFromDifficulty(currentPlay.difficulty, &auxUndos, NULL);
				currentPlay = makePlay(currentPlay.difficulty, auxUndos, 0);
				previousPlay = makePlay(currentPlay.difficulty, auxUndos-1, 0);
				//Faltaria validar que se haya creado con exito el tablero.
				//Game.board == NULL
				option = play(&previousPlay, &currentPlay)? option: 3;
				break;
			case 2:
				wrapLoad(&actual); //Desde aca adentro se llama a makePlay, getFromDifficulty, etc..
				option = play(&previousPlay, &currentPlay)? option: 3;
				break;
			case 3:
				printf("\nVolve cuando quieras!");
				break;
			default:
				printf('\nSeleccione una opcion correcta');
				break;
		}
	}while(option != 3);

	return 0;
}