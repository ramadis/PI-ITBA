void wrapSave(typePlay * game){
	char filename[36] = {0};
	char parameters;

	do {
		printf("\nIngrese el nombre del archivo a guardar [MAX 35 CARACTERES]: ");
		parameters = scanf("%35s", filename);
		
		CLEAN_BUFFER

		if (parameters && saveGame(game, filename)){
			printf("\nPartida guardada con exito!");
		} else {
			printf ("\nSe produjo un error en el guardado.");
			printf ("\nVuelva a intentarlo...");
		}
	}while(!parameters);
}