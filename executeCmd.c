signed char executeCmd(int commandNum, typePlay * nowPlay, typePlay * previousPlay){

	switch(commandNum){
		case 1:
			if (!undo(nowPlay, previousPlay))
				printf("\n*** No se puede realizar UNDO en esta instancia ***");
      break;
    case 2:
      wrapSave(nowPlay);
      break;
    case 3:
      quitGame(nowPlay);
      return 0;
      break;
    case 4:
      move(4, nowPlay, previousPlay);
      break;
    default:
      printf ("\n*** Comando no reconocido! ***");
      break;
	}

  return 1;
}