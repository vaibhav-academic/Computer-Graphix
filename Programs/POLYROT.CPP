//graphics
//Poly Rotate Animation
// Rotates various Regular Polygons on an Interactive Display
//(C) Vaibhav Jain
//14/4/04
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define CTRLUP -115
#define CTRLDOWN -111
#define CTRLLEFT 115
#define CTRLRIGHT 116

void mydrawpoly(int sides,int r,int x,int y,int phase=0)
{if(sides<=0) return;
 float theta=2*M_PI/sides;
 float t=M_PI/180*phase;
 int x1=x+r*cos(t),x2;
 int y1=y+r*sin(t),y2;
 while(sides--)
 {t+=theta;
  x2=x+r*cos(t);
  y2=y+r*sin(t);
  line(x1,y1,x2,y2);
  x1=x2,y1=y2;
 }
}

void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 int phase=0;
 int sides=3;
 int radius=60;
 char key=0;
 int x=getmaxx()/2;
 int y=getmaxy()/2;

 do
 {phase++;
 putpixel(x,y,WHITE);
 mydrawpoly(sides,radius,x,y,phase);
 delay(10);
 cleardevice();
 if(kbhit())
	 switch(key=getch())
	 {case UP:sides++;break;
	  case DOWN:sides--;break;
	  case LEFT:radius-=10;break;
	  case RIGHT:radius+=10;break;
	  case CTRLUP:y-=10;break;
	  case CTRLDOWN:y+=10;break;
	  case CTRLLEFT:x-=10;break;
	  case CTRLRIGHT:x+=10;break;
	 }
 }while(key!=27);
closegraph();
}