#define CLEAN_BUFFER while(getchar() != '\n');

signed char executeCmd(int commandNum, typePlay * currentPlay, typePlay * previousPlay){
  typePlay auxPlay;
  auxPlay = makePlay(currentPlay->difficulty, currentPlay->score, currentPlay->undos);

	switch(commandNum){
		case 1:
			if (!undo(currentPlay, previousPlay))
				printf("\n*** No se puede realizar UNDO en esta instancia ***");
      break;
    case 2:
      //scanf filename
      //save(currentPlay);
      //clean buffer
      break;
    case 3:
      quitGame(currentPlay);
      return 0;
      break;
    case 8:
      printf ("\n*** Comando no reconocido! ***");
      break;
    default:
      copyPlay(&auxPlay, currentPlay);
      if (move(commandNum, currentPlay, previousPlay))
        copyPlay(previousPlay, &auxPlay);
      break;
	}

  return 1;
}