#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Backend.h"

#define CLEAN_BUFFER while(getchar() != '\n');

enum options {PLAY=1, LOAD, EXIT};

unsigned char readMenu(void);
unsigned char wrapLoad(typePlay * game);
void wrapSave(typePlay * game);
int readCmd(void);
unsigned char readDifficulty(void);
void quitGame(typePlay * game);
void printPlay(const typePlay * game);
unsigned char play(typePlay * previousPlay, typePlay * currentPlay);
signed char executeCmd(int commandNum, typePlay * currentPlay, typePlay * previousPlay);

int main(){
	typePlay currentPlay, previousPlay;
	unsigned short int auxUndos;
	unsigned char option;

	srand(time(NULL));

	do {
		auxUndos = 0;
		option = readMenu();
		int size, filRand, colRand, i;

		switch(option){
			case PLAY:
				currentPlay.difficulty = readDifficulty();
				size = getFromDifficulty(currentPlay.difficulty, &auxUndos, NULL);
				currentPlay = makePlay(currentPlay.difficulty, 0, auxUndos);
				previousPlay = makePlay(currentPlay.difficulty, 0, auxUndos-1);

				if(currentPlay.board == NULL || previousPlay.board == NULL){
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
				if(wrapLoad(&currentPlay))
					printf("\nError al cargar el juego.");	 	//Desde aca adentro se llama a makePlay, getFromDifficulty, etc..
				option = play(&previousPlay, &currentPlay)? option: EXIT;
				break;
			case EXIT:
				printf("\nVolve cuando quieras!\n");
				break;
			default:
				printf("\nSeleccione una opcion correcta");
				break;
		}
	}while(option != EXIT);

	return 0;
}

#define RESTRICTION_MENU choice!=1 && choice!=2 && choice!=3

unsigned char readMenu(void){
	int choice;

	printf("\n\tBienvenido al juego 2048\n");

	do{
    	printf("\n\n1. Juego nuevo\n2. Cargar un juego guardado\n3. Salir\n");
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &choice))
			choice = 0;

		CLEAN_BUFFER

    	if(RESTRICTION_MENU)
			printf("\n*ERROR: Ingrese un valor válido como opción*");
		}while(RESTRICTION_MENU);

	return choice;
}

unsigned char wrapLoad(typePlay * game){
  
  char loadName[36];
  int status;
  printf("\nIngrese el nombre del archivo que desea cargar: ");
  scanf("%35s\n", loadName);
  
  return loadGame(game, loadName);
}

void wrapSave(typePlay * game){
	char filename[36] = {0};
	char parameters;

	do {
		printf("\nIngrese el nombre del archivo a guardar [MAX 35 CARACTERES]: ");
		parameters = scanf("%35s", filename);
		
		CLEAN_BUFFER

		if (parameters && saveGame(game, filename)){
			printf("\nPartida guardada con exito!");
		} else {
			printf ("\nSe produjo un error en el guardado.");
			printf ("\nVuelva a intentarlo...");
		}
	}while(!parameters);
}

int readCmd(void){
  int commandnum,i=0;
  char vec[5];
  char c;
  unsigned char cont = 0;
  printf("\nIngrese el comando que desea realizar: ");
  while(i < 5 && (c=getchar()) != '\n')
    vec[i++]= tolower(c);
  vec[i]='\0';

  if(!strcmp(vec,"undo"))
    commandnum = 1;
  else if(!strcmp(vec,"save"))
    commandnum = 2;
  else if(!strcmp(vec,"quit"))
    commandnum = 3;
  else if(!strcmp(vec,"a"))
    commandnum = 4;
  else if(!strcmp(vec,"d"))
    commandnum = 5;
  else if(!strcmp(vec,"w"))
    commandnum = 6;
  else if(!strcmp(vec,"s"))
    commandnum = 7;
  else
    commandnum = 8;

  if(i != 1 && i != 4 && commandnum != 2) CLEAN_BUFFER
  return commandnum;
}

#define RESTRICTION_DIFFICULTY difficulty!=1 && difficulty!=2 && difficulty!=3

unsigned char readDifficulty(void){
	int difficulty;

	printf("\nPara empezar a jugar, elija una dificulad");
	do {
		printf("\n1. Facil\n2. Intermedio\n3. Dificil");
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &difficulty))
			difficulty = 0;

		CLEAN_BUFFER

		if(RESTRICTION_DIFFICULTY)
				printf("\n*ERROR: Ingrese un valor válido como opción*\n");
		}while(RESTRICTION_DIFFICULTY);

		return difficulty;
}

void quitGame(typePlay * game) {
	char response = 0;

	do {
		printf("\nQuiere guardar antes de salir? [s/n]: ");
		response = tolower(getchar());

		CLEAN_BUFFER

		if (response != 's' && response != 'n'){
			printf("\nComando invalido");
			response = 0;
		}
	}while(!response);

	if (response == 's'){
		wrapSave(game);
	} else {
		printf("\nSaliendo del juego... \n");
	}

	return ;
}


#define TOTAL_WIDTH 5 * size

void printPlay(const typePlay * game){
	int i, j, size;
	size = getFromDifficulty(game->difficulty, NULL, NULL);

	printf("\nPuntaje:%6d", game->score);
	printf("\nUndos:\t%6d\n", game->undos);
	
	/*PRINT SUPERIOR BAR*/
	printf("╔");
	for(i = 1; i < TOTAL_WIDTH ; i++)
		printf("%s", (i % 5)? "═" : "╦");
	printf("╗\n");


	for(i = 0; i < size; i++){

		/*PRINT NUMBERS OR SPACES*/
		for( j = 0; j < size; j++){
			if (game->board[i][j] == 0)
				printf("║    ");
			else
				printf("║%4d", game->board[i][j]);				
		}
		
		/*PRINT SEPARATOR AND LOWER BAR*/
		printf("║\n%s", (i != size - 1)? "╠" : "╚");
		for(j = 1; j < TOTAL_WIDTH ; j++)
			if (i != size - 1) 
				printf("%s", (j % 5)? "═" : "╬");
			else
				printf("%s", (j % 5)? "═" : "╩");
		printf("%s\n", (i != size - 1)? "╣" : "╝");
	}

	return ;
}

unsigned char play(typePlay * previousPlay, typePlay * currentPlay){
	signed char cmd, status = CAN_MOVE;
	unsigned char response = 0;

	do{
		printPlay(currentPlay);
		cmd = executeCmd(readCmd(), currentPlay, previousPlay);

		if(cmd >= 4 && cmd < 8)
			status = checkStatus(previousPlay, currentPlay);
	}while(cmd && status == CAN_MOVE);
	
	if (status == LOSE || status == WIN){
		
		do {
			printf("\nQuiere volver a jugar? [s/n]: ");
			response = tolower(getchar());

			CLEAN_BUFFER

			if (response != 's' && response != 'n'){
				printf("\nComando invalido");
				response = 0;
			}
		}while(!response);

	} else if(status == NO_MEMORY){
		printf("\nEl programa se ha quedado sin memoria");	
	}

	return response == 's'; //Si quiere volver a jugar devuelve 1, caso contrario 0 
}

signed char executeCmd(int commandNum, typePlay * currentPlay, typePlay * previousPlay){
  typePlay auxPlay;
  char filename[35];
  auxPlay = makePlay(currentPlay->difficulty, currentPlay->score, currentPlay->undos);
  int score = 0;

	switch(commandNum){
		case 1:
			if (!undo(currentPlay, previousPlay))
				printf("\n*** No se puede realizar UNDO en esta instancia ***");
      break;
    case 2:
      if (scanf("%34s", filename) && !saveGame(currentPlay, filename))
        printf("\n**** No se pudo guardar con exito ***");
      CLEAN_BUFFER
      break;
    case 3:
      quitGame(currentPlay);
      return 0;
      break;
    case 8:
      printf ("\n*** Comando no reconocido! ***");
      break;
    default:
      score = 0;
      copyPlay(&auxPlay, currentPlay);
      if ((score = move(currentPlay, commandNum)) != -1){
        currentPlay->score += score;
        copyPlay(previousPlay, &auxPlay);
      } else {
      	commandNum = 9;
      }
      
      break;
	}

  return commandNum;
}