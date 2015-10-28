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