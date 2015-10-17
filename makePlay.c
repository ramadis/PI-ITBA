typePlay makePlay(unsigned short int difficulty, unsigned int score, unsigned short int undos){
	typePlay game;
	int size;

	size = getFromDifficulty(difficulty, NULL, NULL);

	game.difficulty = difficulty;
	game.score = score;
	game.undos = undos;

	game.board = malloc(size * size * sizeof(unsigned short int));

	return game;
}