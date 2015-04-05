//graphics
//8-connected boundry fill algorithm
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#define NUM 10
struct Rectangle{int x,y,height,width;}rects[NUM];

void generateRects()
{randomize();
for(int i=0;i<NUM;i++)
 {rects[i].x=random(570);
  rects[i].y=random(410);
  rects[i].height=random(70)+10;
  rects[i].width=random(70)+10;
 }
}

void drawRects()
{for(int i=0;i<NUM;i++)
  rectangle(rects[i].x,rects[i].y,
	    rects[i].x+rects[i].width,rects[i].y+rects[i].height);
}

void BoundryFill(int x,int y,int boundry,int newColor)
{if(x<0 || x>640) return;
 if(y<0 || y>480) return;
 int curcol=getpixel(x,y);
 if(curcol==boundry
 ||curcol==newColor) return;
 putpixel(x,y,newColor);
 //fill the four connected points
  BoundryFill(x,y+1,boundry,newColor);
  BoundryFill(x,y-1,boundry,newColor);
  BoundryFill(x+1,y,boundry,newColor);
  BoundryFill(x-1,y,boundry,newColor);
  BoundryFill(x+1,y+1,boundry,newColor);
  BoundryFill(x+1,y-1,boundry,newColor);
  BoundryFill(x-1,y+1,boundry,newColor);
  BoundryFill(x-1,y-1,boundry,newColor);

}

void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 generateRects();
 drawRects();
 getch();
 for(int i=0;i<NUM;i++)
 BoundryFill(rects[i].x+rects[i].width/2,rects[i].y+rects[i].height/2,
		WHITE,random(15)+1);
 getch();
}