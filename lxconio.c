#include "lxconio.h"

//~ static int getch_echo(int echo);
static int wherexy(int *x, int *y);
static int lxgetch();


static int bgc;
static struct termios orig_termios;


void set_conio_terminal_mode()
{
	bgc = 40;
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

int _kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int _getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

int getch(){
	int c;
	
	set_conio_terminal_mode();
	c = _getch();
	reset_terminal_mode();
	
	return c;
}

int kbhit(){
	int c;
	
	set_conio_terminal_mode();
	c = _kbhit();
	reset_terminal_mode();
	
	return c;
}

int _getche()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
		putchar(c);
        return c;
    }
}


void InitLxConio(){
	bgc=40;
}
      
void CloseLxConio(){
	printf("\033[m");
}
      
void clreol(){
	printf("\033[K");
}
      
void insline(){
	printf( "\x1b[1L");
}
  
void delline(){
	printf( "\033[1M");
}

void gotoxy(int x,int y){
	printf("\033[%d;%df",y,x);
	//~ printf("\033[%d;%dH",y+1,x+1);
}
  
//~ void clrscr(){
	//~ printf( "\033[%dm\033[2J\033[1;1f",bgc);
	//~ gotoxy(1,1);
//~ }
  
void textbackground(int color){
	switch(color%16){
	case BLACK:          
		bgc=40;
		break;
	case BLUE:
	    bgc=44;
	    break;
	case GREEN:          
		bgc=42;
		break;
	case CYAN:           
		bgc=46;
		break;
	case RED:            
		bgc=41;
		break;
	case MAGENTA:        
		bgc=45;
		break;
	case BROWN:          
		bgc=43;
		break;
	case LIGHTGRAY:      
		bgc=47;
		break;
	case DARKGRAY:       
		bgc=40;
		break;
	case LIGHTBLUE:      
		bgc=44;
		break;
	case LIGHTGREEN:     
		bgc=42;
		break;
	case LIGHTCYAN:      
		bgc=46;
		break;
	case LIGHTRED:       
		bgc=41;
		break;
	case LIGHTMAGENTA:   
		bgc=45;
		break;
	case YELLOW:         
		bgc=43;
		break;
	case WHITE:          
		bgc=47;
		break;
	}
}

void textcolor(short color){  
	switch(color%16){
	case BLACK:          
		printf("\033[0;%d;%dm",30,bgc);
		break;
	case BLUE:           
		printf("\033[0;%d;%dm",34,bgc);
		break;
	case GREEN:          
		printf("\033[0;%d;%dm",32,bgc);
		break;
	case CYAN:           
		printf("\033[0;%d;%dm",36,bgc);
		break;
	case RED:            
		printf("\033[0;%d;%dm",31,bgc);
		break;
	case MAGENTA:        
		printf("\033[0;%d;%dm",35,bgc);
		break;
	case BROWN:          
		printf("\033[0;%d;%dm",33,bgc);
		break;
	case LIGHTGRAY:      
		printf("\033[0;%d;%dm",37,bgc);
		break;
	case DARKGRAY:       
		printf("\033[1;%d;%dm",30,bgc);
		break;
	case LIGHTBLUE:      
		printf("\033[1;%d;%dm",34,bgc);
		break;
	case LIGHTGREEN:     
		printf("\033[1;%d;%dm",32,bgc);
		break;
	case LIGHTCYAN:      
		printf("\033[1;%d;%dm",36,bgc);
		break;
	case LIGHTRED:       
		printf("\033[1;%d;%dm",31,bgc);
		break;
	case LIGHTMAGENTA:   
		printf("\033[1;%d;%dm",35,bgc);
		break;
	case YELLOW:         
		printf("\033[1;%d;%dm",33,bgc);
		break;
	case WHITE:          
		printf("\033[1;%d;%dm",37,bgc);
		break;
	}
}

int ungetch(int ch){
	return ungetc(ch, stdin);
}

static int getch_echo(int echo){
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~ICANON;
	if(echo)
		newt.c_lflag &=  ECHO;
	else
		newt.c_lflag &= ~ECHO;
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
 }
  
int lxgetch(){
	return getch_echo(0);
}
//~ int getch(){
	//~ return getch_echo(0);
//~ }
  
//~ int getche(){
	//~ return getch_echo(1);
//~ }
  
static int wherexy(int *x, int *y){
	printf("\033[6n");
	//~ scanf("\033[%d;%dR", x, y);
	if(lxgetch() != '\x1B') 
		return 0;
	if(lxgetch() != '\x5B') 
		return 0;
	int in;
	int ly = 0;
	while((in = lxgetch()) != ';')
		ly = ly * 10 + in - '0';	
	int lx = 0;
	while((in = lxgetch()) != 'R')
		lx = lx * 10 + in - '0';
	*x = lx;
	*y = ly;
	
	return 1;
}

int wherex(){
	int x=0, y=0;
	wherexy(&x, &y);
	return x;
}
  
int wherey(){
	int x=0, y=0;
	wherexy(&x, &y);
	return y;
} 

//~ int kbhit(){
	//~ struct termios oldt, newt;
	//~ int ch;
	//~ int oldf;    
	//~ tcgetattr(STDIN_FILENO, &oldt);
	//~ newt = oldt;
	//~ newt.c_lflag &= ~(ICANON | ECHO);
	//~ tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	//~ oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	//~ fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);    
	//~ ch = getchar();    
	//~ tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	//~ fcntl(STDIN_FILENO, F_SETFL, oldf);    
	//~ if(ch != EOF){
		//~ ungetc(ch, stdin);
		//~ return 1;
	//~ }    
	//~ return 0;
 //~ }

void cursorOff(){
	printf("\e[?25l");
	//~ system("tput cinvis");
}

void cursorOn(){
	printf("\e[?25h");
	//~ system("tput cnorm");
}

int putch(const char c){
	printf("%c",c);
	return (int)c;
}
  
int cputs(const char*str){
	printf("%s", str);
	return 0;
}

