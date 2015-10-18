signed char executeCmd(int commandNum, typePlay * currentPlay, typePlay * previousPlay){

	switch(commandNum){
		case 1:
			if (!undo(currentPlay, previousPlay))
				printf("\n*** No se puede realizar UNDO en esta instancia ***");
      break;
    case 2:
      wrapSave(currentPlay);
      break;
    case 3:
      quitGame(currentPlay);
      return 0;
      break;
    case 8:
      printf ("\n*** Comando no reconocido! ***");
      break;
    default:
      move(commandNum, currentPlay, previousPlay);
      break;
	}

  return 1;
}