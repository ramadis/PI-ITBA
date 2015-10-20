#define CLEAN_BUFFER while(getchar() != '\n');

int readCommand(void){
  int commandnum,i=0;
  char vec[5];
  char c;
  unsigned char cont = 0;
  printf("\nIngrese el comando que desea realizar: ");
  while(i < 5 && (c=getchar()) != '\n')
    vec[i++]= tolower(c);
  vec[i]='\0';

  if(!strcmp(vec,"undo"))
    commandnum = 1;
  else if(!strcmp(vec,"save"))
    commandnum = 2;
  else if(!strcmp(vec,"quit"))
    commandnum = 3;
  else if(!strcmp(vec,"a"))
    commandnum = 4;
  else if(!strcmp(vec,"d"))
    commandnum = 5;
  else if(!strcmp(vec,"w"))
    commandnum = 6;
  else if(!strcmp(vec,"s"))
    commandnum = 7;
  else
    commandnum = 8;

  if(i != 1 && i != 4 && commandnum != 2) CLEAN_BUFFER
  return commandnum;
}

