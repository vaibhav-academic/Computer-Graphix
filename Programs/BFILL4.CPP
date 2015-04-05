//graphics
//4-connected boundry fill algorithm
//draws 30 random circles of random radius and fills with
// random color using 4 point connected boundry filling
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#define NUM 50
struct Circle{int cx,cy,radius;}circles[NUM];

void generateCircles()
{for(int i=0;i<NUM;i++)
 {circles[i].cx=random(590)+20;
  circles[i].cy=random(430)+20;
  circles[i].radius=random(40);
 }
}

void drawCircles()
{for(int i=0;i<NUM;i++)
 circle(circles[i].cx,circles[i].cy,circles[i].radius);
}
void BoundryFill(int x,int y,int boundry,int newColor)
{if(x<0 || x>640) return;
 if(y<0 || y>480) return;
 int curcol=getpixel(x,y);
 if(curcol==boundry
 ||curcol==newColor) return;
 putpixel(x,y,newColor);
 //delay(5);
 //if(kbhit()) exit(0);
 //fill the four connected points
  BoundryFill(x,y+1,boundry,newColor);
  BoundryFill(x,y-1,boundry,newColor);
  BoundryFill(x+1,y,boundry,newColor);
  BoundryFill(x-1,y,boundry,newColor);

}

void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 generateCircles();
 drawCircles();
 getch();
 for(int i=0;i<NUM;i++)
 BoundryFill(circles[i].cx,circles[i].cy,WHITE,random(15)+1);
 getch();
}