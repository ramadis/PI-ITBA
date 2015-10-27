unsigned char loadGame(typePlay * game, char * loadName){

  FILE * myGame;
  if(myGame = fopen("loadName", "r") == NULL)
    return 0;
  fread(game, sizeof(typePlay), 1, myGame);
  fclose(myGame);
  return 1;
}
