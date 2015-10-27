char saveGame(typePlay * game, char * filename){
	FILE * file;
	file = fopen(filename, "wt");
	
	if(file == NULL)
		return 0;
	
	fwrite(game, sizeof(typePlay), 1, file);
	fclose(file);

	return 1;
}