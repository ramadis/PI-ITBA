unsigned char wrapLoad(typePlay * game){

  char loadName[36];
  int status;
  printf("\nIngrese el nombre del archivo que desea cargar: ");
  scanf("%35s\n", loadName);
  return loadGame(game, loadName);

}
