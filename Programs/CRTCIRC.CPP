//graphics
//generation of circle using its cartesion
//equation

#include <conio.h>
#include <math.h>
#include <graphics.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define CTRLUP -115
#define CTRLDOWN -111
#define CTRLLEFT 115
#define CTRLRIGHT 116

//draw circle using mid point algorithm
void drawcircle(int cx,int cy,int radius)
{if(radius<=0) return;
 for(int x=0;x<radius/2;x++)
 {int y=sqrt((long)radius*radius-x*x);
  putpixel(cx+x,cy+y,WHITE);
  putpixel(cx+x,cy-y,WHITE);
  putpixel(cx-x,cy+y,WHITE);
  putpixel(cx-x,cy-y,WHITE);
  putpixel(cx+y,cy+x,WHITE);
  putpixel(cx+y,cy-x,WHITE);
  putpixel(cx-y,cy+x,WHITE);
  putpixel(cx-y,cy-x,WHITE);
 }
}
void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 int cx=getmaxx()/2,cy=getmaxy()/2,r=50;
 char key;
 do{
 cleardevice();
 setcolor(GREEN);
 circle(cx,cy,r);
 drawcircle(cx,cy,r);
 putpixel(cx,cy,WHITE);
 key=getch();
 switch(key)
 {case UP:
  case RIGHT:r-=10;break;
  case LEFT:
  case DOWN:r+=10;break;
  case CTRLDOWN:cy+=10;break;
  case CTRLUP:cy-=10;break;
  case CTRLLEFT:cx-=10;break;
  case CTRLRIGHT:cx+=10;break;
 }
 }while(key!=27);
closegraph();
}