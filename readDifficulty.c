#define CLEAN_BUFFER while(getchar() != '\n');

unsigned char readDifficulty(){
	int difficulty, valid = 0;

	printf("\nPara empezar a jugar, elija una dificulad");
	printf("\n1. Facil\n2.Intermedio\n3.Dificil\n");
	
	do {
		printf("Dificultad [1, 2 o 3]: ");

		if (!scanf("%d", &difficulty))
			difficulty = 0;

		CLEAN_BUFFER

		switch (difficulty){
			case 1:
			case 2:
			case 3:
				valid = difficulty;
				break;
			default:
				printf("\nIngrese un valor valido como nivel\n");
				break;
		}
	}while(!valid);

	return valid;

	return 0;
}