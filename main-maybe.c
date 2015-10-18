typedef struct {
	unsigned short int difficulty;
	unsigned int score;
	unsigned short int undos;
	unsigned short int  ** board;
} typePlay;

int main(){
	typePlay nowPlay, previousPlay;
	unsigned int auxScore;
	unsigned short int auxUndos;

	do {
		option = readMenu();

		switch(option){
			case 1:
				nowPlay.difficulty = readDifficulty();
				getFromDifficulty(nowPlay.difficulty, &auxUndos, &auxScore);
				nowPlay = makePlay(nowPlay.difficulty, auxUndos, auxScore);
				previousPlay.undos = 0;
				play(&previousPlay, &nowPlay);
				break;
			case 2:
				wrapLoad(&actual); //Desde aca adentro se llama a makePlay, getFromDifficulty, etc..
				previousPlay.undos = 0;
				play(&previousPlay, &nowPlay);
				break;
			case 3:
				printf("\nVolve cuando quieras!\n");
				break;
			default:
				printf('\nSeleccione una opcion correcta');
				break;
		}
	}while(option != 3 && checkStatus(&actual));

	return 0;
}