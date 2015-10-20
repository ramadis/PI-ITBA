signed char undo(typePlay * currentPlay, typePlay * previousPlay){
	if(previousPlay->undos != currentPlay->undos || currentPlay->undos == 0){
		return 0;
	}

	copyPlay(currentPlay, previousPlay);
	currentPlay->undos--;
	return 1;
}