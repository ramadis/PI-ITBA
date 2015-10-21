#define ind1  i*orientation + j*!orientation
#define ind2  i*!orientation + j*orientation
#define aux1 aux * !orientation + orientation * (ind1)
#define aux2 aux * orientation + !orientation * (ind2)
#define k1 k * !orientation + orientation * (ind1)
#define k2 k * orientation + !orientation * (ind2)

void move(typeMatrix * t,int incr,int startj,int startk,int endj,int orientation){

  int dim=4;
  int i,j,k,aux,formar;

  for(i=0;i<4;i++){
  formar=startk;
  for(j=startj,k=startk; j != endj ; j+=incr,k+=incr)
    if(t[ind1][ind2] != 0){
      if(t[k1][k2] == t[ind1][ind2]){
        t[k1][k2]*= 2;
        t[ind1][ind2] = 0;
        formar = j;}
      else if(t[k1][k2]==0) {
        aux=k;
        while(t[aux1][aux2] == 0 && aux != formar && aux != startk){
          aux+=incr*(-1);
        }
        if(t[aux1][aux2] == t[ind1][ind2]){
          t[aux1][aux2]*= 2;
          t[ind1][ind2]= 0;
          formar=k;}
        else if(t[aux1][aux2] == 0){
          t[aux1][aux2]= t[ind1][ind2];
          t[ind1][ind2]= 0;}
        else{
          t[aux1+!orientation*incr][aux2+orientation*incr]= t[ind1][ind2];
          t[ind1][ind2]= 0;}
      }
    }
  }
}
