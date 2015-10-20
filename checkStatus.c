int checkStatus(typePlay * previousPlay, typePlay * currentPlay){
	unsigned short int * zeros = NULL, * vectorAux, winNumber;
	int indexZeros=0, size, i, j, zeroRand, numRand;
	signed char canMove = 0;

	size = getFromDifficulty(currentPlay->difficulty, NULL, &winNumber);

	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){

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
			else if (currentPlay->board[i][j] == winNumber)
				free(zeros);
				return WIN;
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