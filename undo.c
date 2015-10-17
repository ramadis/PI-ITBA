signed char undo(typePlay * nowPlay, typePlay * previousPlay){
	if(previousPlay->undos != nowPlay->undos){
		return 0;
	}

	copyPlay(nowPlay, previousPlay);
	nowPlay->undos--;
	return 1;
}