enum states = {LOSE=1, WIN, CAN_MOVE, NO_MEMORY};

void play(typePlay * previousPlay, typePlay * nowPlay){
	signed char cmd, status = 0;
	unsigned char response = 0;

	do{
		cmd = executeCmd(readMenu(), nowPlay, previousPlay));
	}while(cmd && (status = checkStatus(previousPlay, nowPlay)) == CAN_MOVE);
	
	if (status == LOSE || status == WIN){
		
		do {
			printf("\nQuiere volver a jugar? [s/n]: ");
			response = toLower(getchar());

			if (response != 's' && response != 'n'){
				printf("\nComando invalido");
				response = 0;
			}
		}while(!response);

	} else if(status == NO_MEMORY){
		printf("\nEl programa se ha quedado sin memoria");	
	}

	return response == 's'; //Si quiere volver a jugar devuelve 1, caso contrario 0 
}