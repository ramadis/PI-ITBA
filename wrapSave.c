#define CLEAN_BUFFER while(getchar != '\n');

void wrapSave(typePlay * game){
	char filename[15] = {0};
	
	do {
		printf("Ingrese el nombre del archivo a guardar [MAX 14 CARACTERES]: ");
		parameters = scanf("%15s", filename);
		
		CLEAN_BUFFER

		if (parameters && saveGame(game, filename)){
			printf("\nPartida guarda con exito!\n");
		} else {
			printf ("\nSe produjo un error en el guardado.\n");
			printf ("Vuelva a intentarlo...\n");
		}
	}while(!parameters);
}