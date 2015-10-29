#include "Backend.h"

signed char checkAround(typePlay * game, int row, int column){
	unsigned short int current;
	current = game->board[row][column];
	char canMove = 0;

	if( row >= 1 )
		canMove = game->board[row-1][column] == current || game->board[row+1][column] == 0 ;

	else if( !canMove && row+1 < game->size)
		canMove = game->board[row+1][column] == current || game->board[row+1][column] == 0 ;

	else if( !canMove && column >= 1 )
		canMove = game->board[row][column-1] == current || game->board[row+1][column] == 0 ;

	else if( !canMove && column+1 < game->size)
		canMove = game->board[row][column+1] == current || game->board[row+1][column] == 0 ;

	return canMove;
}

int checkStatus(typePlay * previousPlay, typePlay * currentPlay){
	unsigned short int * zeros = NULL, * vectorAux;
	unsigned int winNumber;
	int indexZeros=0, i, j, zeroRand, numRand;
	signed char canMove = 0;

	getFromDifficulty(currentPlay->difficulty, NULL, &winNumber);

	for(i = 0; i < currentPlay->size; i++){
		for(j = 0; j < currentPlay->size; j++){

			if (currentPlay->board[i][j] == 0){

				if(indexZeros%BLOCK == 0){

					vectorAux = realloc(zeros,(BLOCK + indexZeros)*sizeof(*zeros));
					if(vectorAux == NULL){

						free(zeros);
						return NO_MEMORY;
					}
					else{
						zeros = vectorAux;
					}
				}

				zeros[indexZeros++] = i*10+j;
				canMove = 1;
			}
			else if (currentPlay->board[i][j] == winNumber) {
				free(zeros);
				return WIN;
			}
			else if (!canMove && checkAround(currentPlay,i ,j))
				canMove = 1;
		}

		zeros=realloc(zeros,indexZeros*sizeof(*zeros));
	}

	if (canMove){
		zeroRand = randInt(0, indexZeros-1);
		numRand = randInt(1, 100);
		currentPlay->board[zeros[zeroRand]/10][zeros[zeroRand]%10] = 2 + 2 * (numRand < 12);
		free(zeros);
		return CAN_MOVE;
	} else if(currentPlay->undos == previousPlay->undos){
		free(zeros);
		return CAN_MOVE;
	}

	free(zeros);
	return LOSE;
}

void copyPlay(typePlay * destination, typePlay * origin){
	int i, j;


	destination->score = origin->score;
	destination->undos = origin->undos;
	destination->difficulty = origin->difficulty;
	destination->size = origin->size;

	for(i = 0; i < origin->size; i++)
		for(j = 0; j < origin->size; j++)
			destination->board[i][j] = origin->board[i][j];

	return ;
}

int getFromDifficulty(unsigned short int difficulty, unsigned short int * undos, unsigned int * scoreToWin){
  int size;
  unsigned short int undo;
  unsigned int win;

  switch(difficulty){
    case 1:
      win = 1024;
      undo = 8;
      size = 8;
      break;
    case 2:
      win = 2048;
      undo = 4;
      size = 6;
      break;
    case 3:
      win = 2048;
      undo = 2;
      size = 4;
      break;
    default:
      size = 0;
      break;
  }

  if (undos != NULL) *undos = undo;
  if (scoreToWin != NULL) *scoreToWin = win;
  return size;
}

unsigned char loadGame(typePlay * game, char * loadName){
	unsigned short int difficulty;
	int i, j;

  FILE * file;
  if((file = fopen(loadName, "rt")) == NULL)
    return 0;

	fread(&difficulty, sizeof(unsigned short int), 1, file);

	*game = makePlay(difficulty, 0 ,0);
	game->size = getFromDifficulty(game->difficulty, NULL, NULL);
	fread(&(game->score), sizeof(unsigned int), 1, file);
	fread(&(game->undos), sizeof(unsigned short int), 1, file);

	for(i=0;i<game->size;i++)
		for(j=0;j<game->size;j++)
			fread(&(game->board[i][j]), sizeof(unsigned short int), 1, file);

  fclose(file);

  return 1;
}

typePlay makePlay(unsigned short int difficulty, unsigned int score, unsigned short int undos){
	typePlay game;
	int size, i, j;

	size = getFromDifficulty(difficulty, NULL, NULL);

	game.difficulty = difficulty;
	game.score = score;
	game.undos = undos;
	game.size = size;

	game.board = malloc(size * sizeof(*game.board));

	if(game.board == NULL)
		return game;

	for(i = 0; i < size; i++){
		game.board[i] = malloc(size * sizeof (*game.board[i]));

		if(game.board[i] == NULL){
			for(j = 0; j < i; j++)
				free(game.board[j]);
			free(game.board);
			game.board = NULL;
			return game;
		}
	}

	return game;
}

#define ind1  i*orientation + j*!orientation
#define ind2  i*!orientation + j*orientation
#define aux1 aux * !orientation + orientation * (ind1)
#define aux2 aux * orientation + !orientation * (ind2)
#define k1 k * !orientation + orientation * (ind1)
#define k2 k * orientation + !orientation * (ind2)

int move(typePlay * game, int movement){

  int dim = game->size;
  int i,j,k,aux,formar;
  int incr,orientation,startk;
  int score = 0;
  char canMove = 0;

  switch(movement){
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

  for(i=0;i<dim;i++){
  formar=startk;
  for(j=startk + incr,k=startk; j>=0 && j<dim ; j+=incr,k+=incr)
    if(game->board[ind1][ind2] != 0){
      if(game->board[k1][k2] == game->board[ind1][ind2]){
        canMove = 1;
        score += game->board[k1][k2]*= 2;
        game->board[ind1][ind2] = 0;
        formar = j;}
      else if(game->board[k1][k2]==0) {
        aux=k;
        while(game->board[aux1][aux2] == 0 && aux != formar && aux != startk){
          aux+=incr*(-1);
        }
        if(game->board[aux1][aux2] == game->board[ind1][ind2]){
          score += game->board[aux1][aux2]*= 2;
          game->board[ind1][ind2]= 0;
          formar=k;}
        else if(game->board[aux1][aux2] == 0){
          game->board[aux1][aux2]= game->board[ind1][ind2];
          game->board[ind1][ind2]= 0;}
        else{
          game->board[aux1 + !orientation*incr][aux2 + orientation*incr]= game->board[ind1][ind2];
          game->board[ind1][ind2]= 0;}
        canMove = 1;
      }
    }
  }

  if(!canMove)
    return -1;
  else
    return score;
}

double randNormalize(void){
	return rand()/((double)RAND_MAX + 1);
}

int randInt(int izq, int der){
	return izq+ randNormalize() * (der-izq+1);
}

char saveGame(typePlay * game, char * filename){
	FILE * file;
	file = fopen(filename, "wt");
	int i, j;

	if(file == NULL)
		return 0;

	game->size = getFromDifficulty(game->difficulty, NULL, NULL);
	fwrite(&(game->difficulty), sizeof(unsigned short int), 1, file);
	fwrite(&(game->score), sizeof(unsigned int), 1, file);
	fwrite(&(game->undos), sizeof(unsigned short int), 1, file);
	for(i=0;i<game->size;i++)
		for(j=0;j<game->size;j++)
			fwrite(&(game->board[i][j]), sizeof(unsigned short int), 1, file);

	fclose(file);

	return 1;
}

signed char undo(typePlay * currentPlay, typePlay * previousPlay){
	if(previousPlay->undos != currentPlay->undos || currentPlay->undos == 0){
		return 0;
	}

	copyPlay(currentPlay, previousPlay);
	currentPlay->undos--;
	return 1;
}
