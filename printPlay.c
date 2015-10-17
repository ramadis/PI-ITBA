void printPlay(const typePlay * game){
	int i, j, size;
	size = getFromDifficulty(game->difficulty, NULL, NULL);

	printf("\nPuntaje:%6d\n", game->score);
	printf("Undos:\t%6d\n", game->undos);
	
	for(i = 0; i < size; i++){
		for( j = 0; j < size; j++)
			if (game->board[i][j] == 0)
				printf("____ ");
			else
				printf("%4d ", game->board[i][j]);
		printf("\n");
	}

	return ;
}