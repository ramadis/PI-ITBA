void copyPlay(typePlay * destination, typePlay * origin){
	int i, j, size;

	size = getFromDifficulty(origin->difficulty, NULL, NULL);

	destination->score = origin->score;
	destination->undos = origin->undos;
	destination->difficulty = origin->difficulty;

	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			destination->board[i][j] = origin->board[i][j];

	return ;
}
