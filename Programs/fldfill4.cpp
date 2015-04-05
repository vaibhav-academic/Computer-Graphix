//graphics
//4-point flood fill algorithm
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
void myfloodfill(int x,int y,int backcolor,int color)
{if(kbhit()) exit(0);
if(getpixel(x,y)!=backcolor) return;
delay(10);
putpixel(x,y,color);
myfloodfill(x,y-1,BLACK,color);
myfloodfill(x,y+1,BLACK,color);
myfloodfill(x-1,y,BLACK,color);
myfloodfill(x+1,y,BLACK,color);
}

void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 int points[10]={getmaxx()/2+30,getmaxy()/2+30,
		getmaxx()/2+30,getmaxy()/2-30,
		getmaxx()/2-30,getmaxy()/2-30,
		getmaxx()/2-30,getmaxy()/2+30
		};

 points[8]=points[0];
 points[9]=points[1];
 randomize();
 drawpoly(5,points);
 getch();
 myfloodfill(getmaxx()/2,getmaxy()/2,BLACK,random(15));
 printf("done");
 getch();
}