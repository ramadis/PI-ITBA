int getFromDifficulty(unsigned short int difficulty, unsigned short int * undos, unsigned int * scoreToWin){
  int size;
  unsigned short int undo;
  unsigned int win;

  switch(difficulty){
    case 1:
      win = 1024;
      undo = 8;
      size = 8;
      break;
    case 2:
      win = 2048;
      undo = 4;
      size = 6;
      break;
    case 3:
      win = 2048;
      undo = 2;
      size = 4;
      break;
    default:
      size = 0;
      break;
  }

  if (undos != NULL) *undos = undo;
  if (scoreToWin != NULL) *scoreToWin = win;
  return size;
}

