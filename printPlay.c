
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