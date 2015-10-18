#define CLEAN_BUFFER while(getchar != '\n');

void wrapSave(typePlay * game){
	char filename[15] = {0};
	char parameters;

	do {
		printf("Ingrese el nombre del archivo a guardar [MAX 14 CARACTERES]: ");
		parameters = scanf("%15s", filename);
		
		CLEAN_BUFFER

		if (parameters && saveGame(game, filename)){
			printf("\nPartida guarda con exito!");
		} else {
			printf ("\nSe produjo un error en el guardado.");
			printf ("\nVuelva a intentarlo...");
		}
	}while(!parameters);
}