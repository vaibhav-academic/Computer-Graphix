//graphics
//Mid Point Algorithm for generation of circle
//date: 14/4/04
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

//draw circle using mid point algorithm
void drawcircle(int cx,int cy,int radius)
{int p=1-radius;
 int x2=0,y2=2*radius;
 for(int x=0,y=radius;x<=y;x++,x2+=2)
 {putpixel(cx+x,cy+y,WHITE);
  putpixel(cx+x,cy-y,WHITE);
  putpixel(cx-x,cy+y,WHITE);
  putpixel(cx-x,cy-y,WHITE);

  putpixel(cx+y,cy+x,WHITE);
  putpixel(cx+y,cy-x,WHITE);
  putpixel(cx-y,cy+x,WHITE);
  putpixel(cx-y,cy-x,WHITE);
   if(p<0)
  p=p+x2+1;

  else
  {p=p+x2+1-y2;
   y--;
   y2-=2;}

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