#define CLEAN_BUFFER while(getchar() != '\n');
#define BLOCK 10

enum states = {LOSE=1, WIN, CAN_MOVE, NO_MEMORY};

typedef struct {
	unsigned short int difficulty;
	unsigned int score;
	unsigned short int undos;
	unsigned short int  ** board;
} typePlay;


unsigned char readMenu(void);
signed char checkAround(typePlay * game, int row, int column);
int checkStatus(typePlay * previousPlay, typePlay * currentPlay);
void copyPlay(typePlay * destination, typePlay * origin);
signed char executeCmd(int commandNum, typePlay * currentPlay, typePlay * previousPlay);
int getFromDifficulty(unsigned short int difficulty, unsigned short int * undos, unsigned int * scoreToWin);
typePlay makePlay(unsigned short int difficulty, unsigned int score, unsigned short int undos);
void play(typePlay * previousPlay, typePlay * currentPlay);
void printPlay(const typePlay * game);
void quitGame(typePlay * game);
unsigned char readDifficulty();
unsigned char readMenu(void);
signed char undo(typePlay * nowPlay, typePlay * previousPlay);
void wrapSave(typePlay * game);