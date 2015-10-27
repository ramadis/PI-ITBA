#define ind1  i*orientation + j*!orientation
#define ind2  i*!orientation + j*orientation
#define aux1 aux * !orientation + orientation * (ind1)
#define aux2 aux * orientation + !orientation * (ind2)
#define k1 k * !orientation + orientation * (ind1)
#define k2 k * orientation + !orientation * (ind2)

int move(unsigned short int ** t,int incr,int startk,int orientation){

  int dim=4;
  int i,j,k,aux,formar;
  int score = 0;
  char canMove = -1;

  for(i=0;i<dim;i++){
  formar=startk;
  for(j=startk + incr,k=startk; j>=0 && j<dim ; j+=incr,k+=incr)
    if(t[ind1][ind2] != 0){
      if(t[k1][k2] == t[ind1][ind2]){
        score += t[k1][k2]*= 2;
        t[ind1][ind2] = 0;
        formar = j;}
      else if(t[k1][k2]==0) {
        aux=k;
        while(t[aux1][aux2] == 0 && aux != formar && aux != startk){
          aux+=incr*(-1);
        }
        if(t[aux1][aux2] == t[ind1][ind2]){
          score += t[aux1][aux2]*= 2;
          t[ind1][ind2]= 0;
          formar=k;}
        else if(t[aux1][aux2] == 0){
          t[aux1][aux2]= t[ind1][ind2];
          t[ind1][ind2]= 0;}
        else{
          t[aux1 + !orientation*incr][aux2 + orientation*incr]= t[ind1][ind2];
          t[ind1][ind2]= 0;}
      }
    }
  }

  if(canMove == -1)
    return -1;
  else
    return score;


}
