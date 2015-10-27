unsigned char play(typePlay * previousPlay, typePlay * currentPlay){
	signed char cmd, status = 0;
	unsigned char response = 0;

	do{
		cmd = executeCmd(readCmd(), currentPlay, previousPlay);

		if(cmd >= 4 && cmd < 7)
			status = checkStatus(previousPlay, currentPlay)
	}while(cmd && status == CAN_MOVE);
	
	if (status == LOSE || status == WIN){
		
		do {
			printf("\nQuiere volver a jugar? [s/n]: ");
			response = tolower(getchar());

			CLEAN_BUFFER

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