enum states = {LOSE=1, WIN, CAN_MOVE};

void play(typePlay * previousPlay, typePlay * nowPlay){
	signed char cmd, status = 0;
	unsigned char response;

	do{
		cmd = executeCmd(readMenu(), nowPlay, previousPlay));
	}while(cmd && (status = checkStatus()) == CAN_MOVE);
	
	if (status == LOSE || status == WIN){
		
		do {
			printf("\nQuiere volver a jugar? [s/n]: ");
			response = toLower(getchar());

			if (response == 's'){
				return 1;
			} else if (response == 'n') {
				return 0;
			} else {
				printf("\nComando invalido");
			}
		}while(1);

	} else {
		return 0;
	}
}