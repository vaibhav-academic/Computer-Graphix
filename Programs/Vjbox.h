//project
//vjbox.h Copyright 2002 Vaibhav Jain..All Rigths Reserved
#include <conio.h>
#include <stdio.h>
#define UP_ARROW 72
#define DN_ARROW 80
#define LF_ARROW 75
#define RT_ARROW 77
#define SPACE_BAR 32
#define ESCAPE_KEY 27
typedef struct {int x,y;} point;
int box(unsigned x1,unsigned y1,unsigned x2,unsigned y2)
{int i;
gotoxy(x1,y1);for(i=x1;i<=x2;i++)putch(205);
gotoxy(x1,y2);for(i=x1;i<=x2;i++)putch(205);
for(i=y1;i<y2;i++){gotoxy(x1,i);putch(186);}
for(i=y1;i<y2;i++){gotoxy(x2,i);putch(186);}
gotoxy(x1,y1);putch(201);gotoxy(x1,y2);putch(200);
gotoxy(x2,y1);putch(187);gotoxy(x2,y2);putch(188);
return 1;
}
void fill(int x1,int y1,int x2,int y2,char ch)
{int i,j;
for(i=y1;(i<=y2)&&(i<=25);i++)
 if (i<1) continue;
 else
 for(j=x1;(j<=x2)&&(j<=79);j++)
    { if (j<1) continue;
     gotoxy(j,i);
     putch(ch);
    }
}

void msgbox(char mesag[])
{int nlines=0,size=0,i=0,j=0,temp[4];
int maxlen=0;
struct text_info ti;gettextinfo(&ti);
temp[0]=ti.curx;temp[1]=ti.cury;size=strlen(mesag);
temp[2]=ti.screenwidth/2;temp[3]=ti.screenheight/2;
for(i=0;i<=size;i++,j++)
if (mesag[i]=='\n'){nlines++;if(j>maxlen) maxlen=j;j=0;}
if(j>maxlen) maxlen=j;
fill(temp[2]-maxlen/2-2,temp[3]-nlines/2-1,temp[2]+maxlen/2+2,temp[3]+nlines/2+1,' ');
box(temp[2]-maxlen/2-2,temp[3]-nlines/2-1,temp[2]+maxlen/2+2,temp[3]+nlines/2+1);
window(temp[2]-maxlen/2,temp[3]-nlines/2,temp[2]+maxlen/2,temp[3]+nlines/2);
cprintf("%s",mesag);window(1, 1, 80, 25);
gotoxy(temp[0],temp[1]);
}

point midpoint(void)
{  struct text_info ti;point temp;
   gettextinfo(&ti);
   temp.x=ti.screenwidth/2;
   temp.y=ti.screenheight/2;
   return temp;
}

void wait(void )
{ int i='a';
while(!((i==13)||(i==27)))
if (kbhit()) i=getch();
}
void beep()
{ sound(1000);
delay(100);
nosound();
}
