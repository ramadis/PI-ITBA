#include "2048Back.h"

signed char checkAround (const typePlay * game, int row, int column)
{
	unsigned short int current;
  char canMove = ERROR;
	current = game->board[row][column];

  /*  Comprueba si se puede realizar un movimiento  */
	if ( row >= 1 )
		canMove = game->board[row - 1][column] == current
              || game->board[row - 1][column] == EMPTY;

	if ( !canMove && row + 1 < game->size)
		canMove = game->board[row + 1][column] == current
              || game->board[row + 1][column] == EMPTY;

	if ( !canMove && column >= 1 )
		canMove = game->board[row][column - 1] == current
              || game->board[row][column - 1] == EMPTY;

	if ( !canMove && column + 1 < game->size)
		canMove = game->board[row][column + 1] == current
              || game->board[row][column + 1] == EMPTY;

	return canMove;
}


int checkStatus (const typePlay * previousPlay, typePlay * currentPlay)
{
	unsigned short int * zeros = NULL, * vectorAux;
	unsigned int winNumber;
	int indexZeros = 0, i, j, zeroRand, numRand;
	signed char canMove = ERROR;

	getFromDifficulty(currentPlay->difficulty, NULL, &winNumber);

  /*  Genera un vector con las posiciones del tablero donde hay 0s  */
  /*  Retorna WIN si se encuentra el valor con el que se gana la partida  */
	for (i = 0; i < currentPlay->size; i++)
  {
		for (j = 0; j < currentPlay->size; j++)
    {
			if (currentPlay->board[i][j] == EMPTY)
      {

				if (indexZeros % BLOCK == 0)
        {
					vectorAux = realloc(zeros, (BLOCK + indexZeros) * sizeof( *zeros ));
					if (vectorAux == NULL)
          {
						free(zeros);
						return NO_MEMORY;
					} else {
						zeros = vectorAux;
					}
				}
				zeros[indexZeros++] = i * 10 + j;
			} else if (currentPlay->board[i][j] == winNumber)
      {
				free(zeros);
				return WIN;
			}
		}
	}
  zeros=realloc(zeros, indexZeros * sizeof( *zeros ));

  /*  Genera un nuevo número aleatorio luego de un movimiento no nulo */
  if (indexZeros >= 1)
  {
    zeroRand = randInt(0, indexZeros-1);
    numRand = randInt(1, 100);
    currentPlay->board[zeros[zeroRand]/10][zeros[zeroRand]%10]
		= 2 + 2 * (numRand < 12);
  }

  /*  Comprueba si aún se pueden realizar movimientos */
  /*  Si no es posible, retorna LOSE  */
  if (indexZeros <= 1)
  {
    for (i = 0; i < currentPlay->size; i++)
      for (j= 0; j < currentPlay->size; j++)
        canMove = checkAround(currentPlay, i ,j);

    if (!canMove && (currentPlay->undos == 0
				|| currentPlay->undos != previousPlay->undos))
    {
      free(zeros);
      return LOSE;
    }
  }

  /*   De otra forma, retorna CAN_MOVE   */
	free(zeros);
	return CAN_MOVE;
}


void copyPlay (typePlay * destination, const typePlay * origin)
{
	int i, j;

	destination->score = origin->score;
	destination->undos = origin->undos;
	destination->difficulty = origin->difficulty;
	destination->size = origin->size;

	for (i = 0; i < origin->size; i++)
		for (j = 0; j < origin->size; j++)
			destination->board[i][j] = origin->board[i][j];

	return ;
}

int getFromDifficulty(unsigned short int difficulty, unsigned short int * undos,
											unsigned int * scoreToWin)
{
  int size;
  unsigned short int undo;
  unsigned int win;

  switch (difficulty)
  {
    case EASY:
      win = 1024;
      undo = 8;
      size = 8;
      break;

    case MODERATE:
      win = 2048;
      undo = 4;
      size = 6;
      break;

    case HARD:
      win = 2048;
      undo = 2;
      size = 4;
      break;

    default:
      size = 0;
      break;
  }

  if (undos != NULL)
    *undos = undo;
  if (scoreToWin != NULL)
    *scoreToWin = win;

  return size;
}


unsigned char loadGame (typePlay * game, const char * loadName)
{
	unsigned short int difficulty;
	int i, j;

  FILE * file;

  if ((file = fopen(loadName, "rt")) == NULL)
    return ERROR;

	fread(&difficulty, sizeof(unsigned short int), 1, file);

	*game = makePlay(difficulty, 0 ,0);
	game->size = getFromDifficulty(game->difficulty, NULL, NULL);
	fread(&(game->score), sizeof(unsigned int), 1, file);
	fread(&(game->undos), sizeof(unsigned short int), 1, file);

	for (i = 0; i < game->size; i++)
		for (j = 0; j < game->size; j++)
			fread(&(game->board[i][j]), sizeof(unsigned short int), 1, file);

  fclose(file);

  return SUCCESS;
}

typePlay makePlay (unsigned short int difficulty, unsigned int score,
									 unsigned short int undos)
{
	typePlay game;
	int size, i, j;

	size = getFromDifficulty(difficulty, NULL, NULL);

	game.difficulty = difficulty;
	game.score = score;
	game.undos = undos;
	game.size = size;

	game.board = malloc(size * sizeof(*game.board));

	if (game.board == NULL)
		return game;

  /*   Creo el tablero  */
	for (i = 0; i < size; i++)
  {
		game.board[i] = malloc(size * sizeof (*game.board[i]));

		if (game.board[i] == NULL)
    {
			for (j = 0; j < i; j++)
				free(game.board[j]);
			free(game.board);
			game.board = NULL;
			return game;
		}
	}

  for (i = 0; i < game.size; i++)
    for (j = 0; j < game.size; j++)
      game.board[i][j] = 0;

	return game;
}


/* Invierte el orden de los indices ingresados para realizar los 4 movimientos*/
/* y asi poder recorrer todas las filas y columnas  */

#define ind1  i * orientation + j * !orientation
#define ind2  i * !orientation + j * orientation
#define aux1 aux * !orientation + orientation * (ind1)
#define aux2 aux * orientation + !orientation * (ind2)
#define k1 k * !orientation + orientation * (ind1)
#define k2 k * orientation + !orientation * (ind2)

int move (typePlay * game, int movement)
{

  int dim = game->size;
  int i,j,k,aux,formar;
  int incr,orientation,startk;
  int score = 0;
  char canMove = ERROR;

  switch (movement)
  {
    case LEFT:
      incr = 1;
      startk = 0;
      orientation = 1;
      break;

    case RIGHT:
      incr = -1;
      startk = dim-1;
      orientation = 1;
      break;

    case UP:
      incr = 1;
      startk = 0;
      orientation = 0;
      break;

    case DOWN:
      incr = -1;
      startk = dim - 1;
      orientation = 0;
      break;
  }

  for (i = 0; i < dim; i++)
  {
    formar=startk;
    for (j = startk + incr, k = startk; j >= 0 && j<dim ; j += incr, k+= incr)
    {
      if (game->board[ind1][ind2] != EMPTY)
      {
        if (game->board[k1][k2] == game->board[ind1][ind2])
        {
          canMove = SUCCESS;
          score += game->board[k1][k2] *= 2;
          game->board[ind1][ind2] = EMPTY;
          formar = j;
        } else if (game->board[k1][k2] == EMPTY)
        {
          aux = k;

          /*  El while se realiza para recorrer la matriz en el sentido */
          /*  del movimientos mientras que el contenido sea 0, que encuentre */
          /*  el mismo numero para sumarlos o que el indice sea distinto al */
					/*  indice del recorrido anterior  */

          while (game->board[aux1][aux2] == EMPTY
								 && aux != formar && aux != startk)
          {
            aux += incr * (-1);
          }
          if (game->board[aux1][aux2] == game->board[ind1][ind2])
          {
            score += game->board[aux1][aux2] *= 2;
            game->board[ind1][ind2] = EMPTY;
            formar = aux + incr; 
          } else if (game->board[aux1][aux2] == EMPTY)
          {
            game->board[aux1][aux2] = game->board[ind1][ind2];
            game->board[ind1][ind2] = EMPTY;
          } else
          {
            game->board[aux1 + !orientation * incr][aux2 + orientation * incr]
						= game->board[ind1][ind2];
            game->board[ind1][ind2]= EMPTY;
          }
          canMove = SUCCESS;
        }
      }
    }
  }

  if (!canMove)
    return -1;
  else
    return score;
}


double randNormalize (void)
{
	return rand() / ((double)RAND_MAX + 1);
}


int randInt (int izq, int der)
{
	return izq + randNormalize() * (der - izq + 1);
}


char saveGame (typePlay * game, const char * filename)
{
	FILE * file;
  int i, j;

	file = fopen(filename, "wt");

	if (file == NULL)
		return ERROR;

	game->size = getFromDifficulty(game->difficulty, NULL, NULL);
	fwrite(&(game->difficulty), sizeof(unsigned short int), 1, file);
	fwrite(&(game->score), sizeof(unsigned int), 1, file);
	fwrite(&(game->undos), sizeof(unsigned short int), 1, file);
	for (i = 0; i < game->size; i++)
		for (j = 0; j < game->size; j++)
			fwrite(&(game->board[i][j]), sizeof(unsigned short int), 1, file);

	fclose(file);

	return SUCCESS;
}


signed char undo (typePlay * currentPlay, typePlay * previousPlay)
{
	if (previousPlay->undos != currentPlay->undos || currentPlay->undos == 0)
		return ERROR;

	copyPlay(currentPlay, previousPlay);
	currentPlay->undos--;
	return SUCCESS;
}
