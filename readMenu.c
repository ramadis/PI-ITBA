#define RESTRICTION_MENU choice!=1 && choice!=2 && choice!=3
unsigned char readMenu(void){
	int choice;

	printf("\n\tBienvenido al juego 2048\n\n");

	do{
    printf("\n1. Juego nuevo\n2. Cargar un juego guardado\n3. Salir");
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &choice))
			choice = 0;

		CLEAN_BUFFER

    if(RESTRICTION_MENU)
				printf("\n*ERROR: Ingrese un valor válido como opción*\n");
		}while(RESTRICTION_MENU);

	return choice;
}
