#define ind1  i*orientation + j*!orientation
#define ind2  i*!orientation + j*orientation
#define aux1 aux * !orientation + orientation * (ind1)
#define aux2 aux * orientation + !orientation * (ind2)
#define k1 k * !orientation + orientation * (ind1)
#define k2 k * orientation + !orientation * (ind2)

enum movements {LEFT=4, RIGHT, UP, DOWN};

int move(typePlay * game, int movement){

  int dim = getFromDifficulty(game, NULL, NULL);
  int i,j,k,aux,formar;
  int score = 0;
  char canMove = 0;

  switch(movement){
    case LEFT:
      incr = 1;
      startk = 0;
      orientation = 0;
      break;
    case RIGHT:
      incr = -1;
      startk = dim-1;
      orientation = 0;
      break;
    case UP:
      incr = 1;
      startk = 0;
      orientation = 1;
      break;
    case DOWN:
      incr = -1;
      startk = dim - 1;
      orientation = 1;
      break;
  }

  for(i=0;i<dim;i++){
  formar=startk;
  for(j=startk + incr,k=startk; j>=0 && j<dim ; j+=incr,k+=incr)
    if(game->board[ind1][ind2] != 0){
      if(game->board[k1][k2] == game->board[ind1][ind2]){
        canMove = 1;
        score += game->board[k1][k2]*= 2;
        game->board[ind1][ind2] = 0;
        formar = j;}
      else if(game->board[k1][k2]==0) {
        aux=k;
        while(game->board[aux1][aux2] == 0 && aux != formar && aux != startk){
          aux+=incr*(-1);
        }
        if(game->board[aux1][aux2] == game->board[ind1][ind2]){
          score += game->board[aux1][aux2]*= 2;
          game->board[ind1][ind2]= 0;
          formar=k;}
        else if(game->board[aux1][aux2] == 0){
          game->board[aux1][aux2]= game->board[ind1][ind2];
          game->board[ind1][ind2]= 0;}
        else{
          game->board[aux1 + !orientation*incr][aux2 + orientation*incr]= game->board[ind1][ind2];
          game->board[ind1][ind2]= 0;}
        canMove = 1;
      }
    }
  }

  if(!canMove)
    return -1;
  else
    return score;
}