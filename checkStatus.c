enum states = {LOSE=1, WIN, CAN_MOVE, NO_MEMORY};

int checkStatus(typePlay * previousPlay, typePlay * nowPlay){
	unsigned short int * zeros, winNumber;
	int indexZeros=0, size, i, j, zeroRand, numRand;
	signed char canMove = 0;

	size = getFromDifficulty(nowPlay->difficulty, NULL, &winNumber);

	zeros = calloc(size*size*sizeof(*zeros));
	if (zeros == NULL) return NO_MEMORY;

	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){

			if (nowPlay->board[i][j] == 0){
				zeros[indexZeros++] = i*10+j;
				canMove = 1;
			}
			else if (nowPlay->board[i][j] == winNumber)
				free(ceros);
				return WIN;
			else if (!canMove && checkAround(t[i][j]))
				canMove = 1;
		}
	}
	
	if (canMove){
		zeroRand = randInt(0, indexZeros-1);
		numRand = randInt(1, 100);
		nowPlay->board[zeros[zeroRand]/10, zeros[zeroRand]%10] = 2 + 2 * (numRand < 12);
		free(ceros);
		return CAN_MOVE;
	} else if(nowPlay->undos == previousPlay->undos){
		free(ceros);
		return CAN_MOVE;
	}

	free(ceros);
	return LOSE;
}