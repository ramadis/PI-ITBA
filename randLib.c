double randNormalize(void){
	return rand()/((double)RAND_MAX + 1) 
}

int randInt(int izq, int der){
	return izq+ randNormalize() * (der-izq+1);
}