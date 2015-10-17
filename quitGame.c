#define CLEAN_BUFFER while(getchar != '\n');

void quitGame(typePlay * game) {
	char response;

	printf("Escriba S si desea guardar antes de salir: ");
	scanf("%c", &response);

	CLEAN_BUFFER

	if (response == 's'){
		wrapSave(game);
	} else {
		printf("\nSaliendo del juego... \n");
	}
}