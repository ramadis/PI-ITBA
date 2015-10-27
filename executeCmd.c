#define CLEAN_BUFFER while(getchar() != '\n');

signed char executeCmd(int commandNum, typePlay * currentPlay, typePlay * previousPlay){
  typePlay auxPlay;
  char filename[35];
  auxPlay = makePlay(currentPlay->difficulty, currentPlay->score, currentPlay->undos);
  int score = 0;

	switch(commandNum){
		case 1:
			if (!undo(currentPlay, previousPlay))
				printf("\n*** No se puede realizar UNDO en esta instancia ***");
      break;
    case 2:
      if (scanf("%34s", filename) && !save(currentPlay, filename))
        printf("\n**** No se pudo guardar con exito ***")
      CLEAN_BUFFER
      break;
    case 3:
      quitGame(currentPlay);
      return 0;
      break;
    case 8:
      printf ("\n*** Comando no reconocido! ***");
      break;
    default:
      score = 0;
      copyPlay(&auxPlay, currentPlay);
      if ((score = move(commandNum, currentPlay->board)) != -1){
        currentPlay->score += score;
        copyPlay(previousPlay, &auxPlay);
      }
      break;
	}

  return commandNum;
}