#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Backend.h"

#define CLEAN_BUFFER while(getchar() != '\n');

enum options {PLAY = 1, LOAD, EXIT};

unsigned char readMenu (void);
unsigned char wrapLoad (typePlay * game);
void wrapSave (typePlay * game);
int readCmd (void);
unsigned char readDifficulty (void);
void quitGame (typePlay * game);
void printPlay (const typePlay * game);
unsigned char play (typePlay * previousPlay, typePlay * currentPlay);
signed char executeCmd (int commandNum, typePlay * currentPlay, typePlay * previousPlay);


int main (void)
{
	typePlay currentPlay, previousPlay;
	unsigned short int auxUndos;
	unsigned char option;

	srand(time(NULL));

	do
	{
		int filRand, colRand, i;
	
		auxUndos = 0;
		option = readMenu();
	
		switch(option)
		{
			case PLAY:
				currentPlay.difficulty = readDifficulty();
				getFromDifficulty(currentPlay.difficulty, &auxUndos, NULL);
				currentPlay = makePlay(currentPlay.difficulty, 0, auxUndos);
				previousPlay = makePlay(currentPlay.difficulty, 0, 0);

				if (currentPlay.board == NULL || previousPlay.board == NULL)
				{
					printf("\nNo se pudo generar el tablero\n");
					option = EXIT;
				}

				for (i = 0; option != EXIT && i < 2; i++)
				{
					do
					{
						filRand = randInt(0, currentPlay.size - 1);
						colRand = randInt(0, currentPlay.size - 1);
					}while (currentPlay.board[filRand][colRand] != 0);
					currentPlay.board[filRand][colRand] = 2 + 2 * (randInt(1, 100) <= CHANCES_4);
				}

				option = play(&previousPlay, &currentPlay)? option: EXIT;
				break;

			case LOAD:
				if (wrapLoad(&currentPlay) == ERROR)
				{
					printf("\nError al cargar el juego.");
				}	
				else
				{
					previousPlay = makePlay(currentPlay.difficulty, 0, 0);
					option = play(&previousPlay, &currentPlay)? option: EXIT;
				}
				break;

			case EXIT:
				printf("\nVolve cuando quieras!\n");
				break;

			default:
				printf("\nSeleccione una opcion correcta");
				break;
		}
	}while (option != EXIT);

	return 0;
}


#define RESTRICTION_MENU choice != PLAY && choice != LOAD && choice != EXIT

unsigned char readMenu (void)
{
	int choice;

	printf("\n\tBienvenido al juego 2048\n");

	do
	{
    printf("\n\n1. Juego nuevo\n2. Cargar un juego guardado\n3. Salir\n");
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &choice))
			choice = ERROR;

		CLEAN_BUFFER

  	if (RESTRICTION_MENU)
			printf("\n*ERROR: Ingrese un valor válido como opción*");
	
	}while (RESTRICTION_MENU);

	return choice;
}


unsigned char wrapLoad (typePlay * game)
{
  char loadName[36] = {0};
  printf("\nIngrese el nombre del archivo que desea cargar: ");
	scanf("%35s", loadName);
	CLEAN_BUFFER

	return loadGame(game, loadName);
}


void wrapSave (typePlay * game)
{
	char filename[36] = {0};
	char parameters;

	do
  {
		printf("\nIngrese el nombre del archivo a guardar [MAX 35 CARACTERES]: ");
		parameters = scanf("%35s", filename);

		CLEAN_BUFFER

		if (parameters && saveGame(game, filename))
		{
			printf("\nPartida guardada con exito!\n");
		} else {
			printf ("\nSe produjo un error en el guardado.");
			printf ("\nVuelva a intentarlo...");
		}
	} while(!parameters);
}


int readCmd(void)
{
  int commandnum, i = 0;
  char vec[5];
  char c;

  printf("\nIngrese el comando que desea realizar: ");

  while (i < 5 && (c = getchar()) != '\n')
    vec[i++]= tolower(c);
  vec[i]='\0';

  if (!strcmp(vec,"undo"))
    commandnum = UNDO;
  else if (!strcmp(vec,"save "))
    commandnum = SAVE;
  else if (!strcmp(vec,"quit"))
    commandnum = QUIT;
  else if (!strcmp(vec,"a"))
    commandnum = LEFT;
  else if (!strcmp(vec,"d"))
    commandnum = RIGHT;
  else if (!strcmp(vec,"w"))
    commandnum = UP;
  else if (!strcmp(vec,"s"))
    commandnum = DOWN;
  else
    commandnum = OTHER_MOVE;

  if (i <= UNDO && i >= LEFT && commandnum != SAVE)
  	CLEAN_BUFFER

  return commandnum;
}


#define RESTRICTION_DIFFICULTY difficulty != EASY && difficulty != MODERATE && difficulty != HARD

unsigned char readDifficulty (void)
{
	int difficulty;

	printf("\nPara empezar a jugar, elija una dificulad");

	do
	{
		printf("\n1. Facil\n2. Intermedio\n3. Dificil");
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &difficulty))
			difficulty = 0;

		CLEAN_BUFFER

		if (RESTRICTION_DIFFICULTY)
			printf("\n*ERROR: Ingrese un valor válido como opción*\n");
	
	}while (RESTRICTION_DIFFICULTY);

	return difficulty;
}


void quitGame (typePlay * game)
{
	char response = ERROR;

	do
	{
		printf("\nQuiere guardar antes de salir? [s/n]: ");
		response = tolower(getchar());

		CLEAN_BUFFER

		if (response != 's' && response != 'n')
		{
			printf("\nComando invalido");
			response = ERROR;
		}

	}while (!response);

	if (response == 's')
	{
		wrapSave(game);
	} else {
		printf("\nSaliendo del juego... \n");
	}

	return ;
}


#define TOTAL_WIDTH NUM_LENGTH * game->size
#define NUM_LENGTH 5

void printPlay (const typePlay * game)
{
	int i, j;

	printf("\nPuntaje:%6d", game->score);
	printf("\nUndos:\t%6d\n", game->undos);

	/*PRINT SUPERIOR BAR*/
	printf("╔");
	for (i = 1; i < TOTAL_WIDTH ; i++)
		printf("%s", (i % NUM_LENGTH)? "═" : "╦");
	printf("╗\n");

	for (i = 0; i < game->size; i++)
	{

		/*PRINT NUMBERS OR SPACES*/
		for ( j = 0; j < game->size; j++)
		{
			if (game->board[i][j] == EMPTY)
				printf("║    ");
			else
				printf("║%4d", game->board[i][j]);
		}

		/*PRINT SEPARATOR AND LOWER BAR*/
		printf("║\n%s", (i != game->size - 1)? "╠" : "╚");
		for (j = 1; j < TOTAL_WIDTH ; j++)
			if (i != game->size - 1)
				printf("%s", (j % NUM_LENGTH)? "═" : "╬");
			else
				printf("%s", (j % NUM_LENGTH)? "═" : "╩");
		printf("%s\n", (i != game->size - 1)? "╣" : "╝");
	}

	return ;
}


unsigned char play (typePlay * previousPlay, typePlay * currentPlay)
{
	signed char cmd, status = CAN_MOVE;
	unsigned char response = ERROR;

	do
	{
		printPlay(currentPlay);
		cmd = executeCmd(readCmd(), currentPlay, previousPlay);

		if (cmd >= LEFT && cmd <= DOWN)
			status = checkStatus(previousPlay, currentPlay);
	}while (cmd && status == CAN_MOVE);

	if (status == LOSE || status == WIN)
	{

		printPlay(currentPlay);

		if (status == LOSE)
		{
			printf("\nPerdiste!");
		} else if (status == WIN) {
			printf("\nGanaste!");
		}

		do
		{
			printf("\nQuiere volver a jugar? [s/n]: ");
			response = tolower(getchar());

			CLEAN_BUFFER

			if (response != 's' && response != 'n')
			{
				printf("\nComando invalido");
				response = ERROR;
			}
		}while (!response);

	} else if (status == NO_MEMORY) {
		printf("\nEl programa se ha quedado sin memoria");
	}

	return response == 's';
}


signed char executeCmd (int commandNum, typePlay * currentPlay, typePlay * previousPlay)
{
  typePlay auxPlay;
  char filename[35];
  int score = 0;

  auxPlay = makePlay(currentPlay->difficulty, currentPlay->score, currentPlay->undos);
  
	switch (commandNum)
	{
		case UNDO:
			if (!undo(currentPlay, previousPlay))
				printf("\n*** No se puede realizar UNDO en esta instancia ***");
      	break;

    case SAVE:
      if (! (fgets(filename, 35, stdin) != NULL 
            && filename[0] != '\n' 
            && (filename[strlen(filename)-1] = 0) == 0 
            && saveGame(currentPlay, filename) == SUCCESS))
        printf("\n**** No se pudo guardar con exito ***");
      break;

    case QUIT:
      quitGame(currentPlay);
      return ERROR;
      break;

    case OTHER_MOVE:
      printf ("\n*** Comando no reconocido! ***");
      break;

    default:
      score = 0;
      copyPlay(&auxPlay, currentPlay);
      if ((score = move(currentPlay, commandNum)) != -1){
        currentPlay->score += score;
        copyPlay(previousPlay, &auxPlay);
      } else {
      	commandNum = EXCEPTION;
      }
      break;
	}

  return commandNum;
}
