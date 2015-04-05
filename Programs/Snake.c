//project
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
typedef struct {int x,y;} point;
void generate(void),swappoints(void),render(void),newfrog(void),msgbox(char mesag[]);
void init(),newlevel();
void fill(unsigned x1,unsigned y1,unsigned x2,unsigned y2,char ch);
void wait(void),makebox(void);
int collided(void),pause(void);
unsigned int  score=0,lives=3;
int dx,dy,size,sir,level=0;
int delays=3000;
point snake[20],frog,newbone(void);
main(void)
{char nkey='a',temp[2];
int isrender=0;
int options=0;
newl:
newlevel();
while(nkey!=27)
{ isrender++;
  if (options==1)  {newlevel();options=0;}
  if (isrender>=delays)
  {
  temp[0]=snake[size-1].x;temp[1]=snake[size-1].y;
  gotoxy(temp[0],temp[1]);putch(' ');
  swappoints();
  snake[0].x+=dx;snake[0].y+=dy;
  render();
  isrender=0;
  }
  if (options==2)  {size++;options=0;}
  if ((snake[0].x==frog.x)&&(snake[0].y==frog.y))
  	{score+=level*10;
        putch(7);
	newfrog();
        options=2;
        if (size>=20) options=1;else snake[size]=newbone();
        render();
        }

  if(kbhit())
  {nkey=getch();
   switch(nkey)
    {case 75:if (dx==0 ){dy=0;dx=-1;sir='<';isrender=delays;render();}break;
     case 77:if (dx==0){dy=0;dx=+1;sir='>';isrender=delays;render();}break;
     case 72:if (dy==0 ){dy=-1;dx=0;sir='^';isrender=delays;render();}break;
     case 80:if (dy==0){dy=+1;dx=0;sir='v';isrender=delays;render();}break;
     case 27: if (pause()){nkey=3;isrender=delays;
     		clrscr();
                makebox();
    		}break;
     case 32:isrender=delays;
    }
  }

	if (collided())
	{lives--;if (lives<=0)
		 {msgbox("  Game Over  ");wait();exit(1);}
		 else
		 {msgbox(" \n\r Oppss.. You Crashed\n\r");wait();init();}
	}
}
printf("Exiting.....");
return 0;
}
void generate()
{ int i;
for(i=0;i<size;i++)
{ snake[i].x=size-i+1;
  snake[i].y=2;
}
}
void swappoints()
{ int i;
 for(i=size-1;i>0;i--)
 {snake[i].x= snake[i-1].x;
 snake[i].y= snake[i-1].y;
 }
}
collided(void)
{int i;
if (((snake[0].x)>=79)||((snake[0].x)<=1))  return 1;
if (((snake[0].y)>=25)||((snake[0].y)<=1))  return 1;
for(i=1;i<size;i++)
if ((snake[0].x+dx==snake[i].x)&&(snake[0].y+dy==snake[i].y)) return 1;
return 0;
}
void newfrog(void)
{
frog.x=random(75)+2;
frog.y=random(21)+2;
}
point newbone(void)
{point temp;
temp.x=snake[size-1].x+dx;
temp.y=snake[size-1].y+dy;
return temp;
}
void render()
{ static int ja=1,i;
  for(i=0;i<size;i++)
 {gotoxy(snake[i].x,snake[i].y);
  putch((i==0)?sir:219);
}
gotoxy(frog.x,frog.y);
if (ja) putch('O'); else putch('*');
ja=!ja;
gotoxy(40,25);printf("Lives:%2u  Level:%2u  Score:%-5u",lives,level,score);
}
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
void fill(unsigned x1,unsigned y1,unsigned x2,unsigned y2,char ch)
{int i,j;
for(i=x1;i<=x2;i++)
{gotoxy(y1,i);
for(j=y1;j<=y2;j++)
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
box(temp[2]-maxlen/2-2,temp[3]-nlines/2-1,temp[2]+maxlen/2+2,temp[3]+nlines/2+1);
window(temp[2]-maxlen/2,temp[3]-nlines/2,temp[2]+maxlen/2,temp[3]+nlines/2);
cprintf("%s",mesag);window(1, 1, 80, 25);
gotoxy(temp[0],temp[1]);
}

void init()
{srand(dx*dx*10);
clrscr();
dx=1;dy=0;
size=5;sir='>';
generate();
newfrog();
makebox();
render();
}
void newlevel()
{ char buffer[50];
  srand(clock());
  size=5;
  init();
  score+=level*100;
  level++;
  delays-=500;
  if(level>=5) sprintf(buffer,"\n\r         Great!!!!\n\r  You Completed the Show"); else
  if(level>1) sprintf(buffer,"       Congrats!!!!\n\r   Starting Level %d  ",level);
  else sprintf(buffer,"  Starting Level %d  ",level);
  msgbox(buffer);
  wait();
  clrscr();
  if (level>=5) exit(0);
  makebox();
}
int pause(void)
{ char nkey='s';
 msgbox("Paused...\n\rPress Escape To Exit\n\rAny Other Key To Continue");
	      while(!kbhit());
	      nkey=getch();
              if (nkey==27) return 0;
	      else return 1;
}
void wait(void )
{ int i='a';
while(!((i==13)||(i==27)))
if (kbhit()) i=getch();
}
void makebox(void)
{
box(1,1,79,25);
gotoxy(35,1);printf("The Snake");
}
point midpoint(void)
{  struct text_info ti;point temp;
   gettextinfo(&ti);
   temp.x=ti.screenwidth/2;
   temp.y=ti.screenheight/2;
   return temp;
}

