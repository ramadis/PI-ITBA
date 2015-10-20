void quitGame(typePlay * game) {
	char response = 0;

	do {
		printf("\nQuiere guardar antes de salir? [s/n]: ");
		response = tolower(getchar());

		CLEAN_BUFFER

		if (response != 's' && response != 'n'){
			printf("\nComando invalido");
			response = 0;
		}
	}while(!response);

	if (response == 's'){
		wrapSave(game);
	} else {
		printf("\nSaliendo del juego... ");
	}

	return ;
}