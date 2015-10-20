signed char checkAround(typePlay * game, int row, int column){
	int size;
	unsigned short int current;
	current = game->board[row][column];
	char canMove = 0;

	size = getFromDifficulty(game, NULL, NULL);

	if( row >= 1 )
		canMove = game->board[row-1][column] == current || game->board[row+1][column] == 0 ;

	else if( !canMove && row+1 < size)
		canMove = game->board[row+1][column] == current || game->board[row+1][column] == 0 ;

	else if( !canMove && column >= 1 )
		canMove = game->board[row][column-1] == current || game->board[row+1][column] == 0 ;

	else if( !canMove && column+1 < size)
		canMove = game->board[row][column+1] == current || game->board[row+1][column] == 0 ;

	return canMove;
}