#ifndef __LXCONIO_H
#define __LXCONIO_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>


#define BLACK        0
#define BLUE         1
#define GREEN        2
#define CYAN         3
#define RED          4
#define MAGENTA      5
#define BROWN        6
#define LIGHTGRAY    7
#define DARKGRAY     8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15
#define BLINK        128

//~ void InitLxConio();
//~ void CloseLxConio();
void clreol();
void insline();
void delline();
void gotoxy(int x,int y);
//~ void clrscr();
void textbackground(int color);
void textcolor(short color);
int ungetch(int ch);
int getch();
//~ int getche();
int wherex();
int wherey();
int kbhit();
void cursorOff();
void cursorOn();
int putch(const char c);
int cputs(const char*str);

void set_conio_terminal_mode();
void reset_terminal_mode();
int _kbhit();
int _getch();
int _getche();



        
#endif

#endif

