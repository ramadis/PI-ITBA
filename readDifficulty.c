#define RESTRICTION_DIFFICULTY choice!=1 && choice!=2 && choice!=3
unsigned char readDifficulty(){
	int difficulty;

	printf("\nPara empezar a jugar, elija una dificulad");
	do {
		printf("\n1. Facil\n2. Intermedio\n3. Dificil");
		printf("\nIngrese alguna de las opciones [1, 2 o 3]: ");

		if (!scanf("%d", &difficulty))
			difficulty = 0;

		CLEAN_BUFFER

		if(RESTRICTION_DIFFICULTY)
				printf("\n*ERROR: Ingrese un valor válido como opción*\n");
		}while(RESTRICTION_DIFFICULTY);

		return difficulty;
}
