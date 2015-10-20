unsigned char readMenu(void){
	int choice, valid = 0;

	printf("\n\tBienvenido al juego 2048\n\n");
	printf("\n1. Juego nuevo\n2. Cargar un juego guardado\n3. Salir");
	
	do {
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &choice))
			choice = 0;

		CLEAN_BUFFER

		switch (choice){
			case 1:
			case 2:
			case 3:
				valid = choice;
				break;
			default:
				printf("\nIngrese un valor valido como opcion");
				break;
		}
	}while(!valid);

	return valid;

	return 0;
}