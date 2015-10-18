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
		auxUndos = 0;
		auxScore = 0;
		option = readMenu();

		switch(option){
			case 1:
				nowPlay.difficulty = readDifficulty();
				getFromDifficulty(nowPlay.difficulty, &auxUndos, &auxScore);
				nowPlay = makePlay(nowPlay.difficulty, auxUndos, auxScore);
				previousPlay = makePlay(nowPlay.difficulty, auxUndos-1, auxScore);
				option = play(&previousPlay, &nowPlay)? option: 3;
				break;
			case 2:
				wrapLoad(&actual); //Desde aca adentro se llama a makePlay, getFromDifficulty, etc..
				option = play(&previousPlay, &nowPlay)? option: 3;
				break;
			case 3:
				printf("\nVolve cuando quieras!\n");
				break;
			default:
				printf('\nSeleccione una opcion correcta');
				break;
		}
	}while(option != 3);

	return 0;
}