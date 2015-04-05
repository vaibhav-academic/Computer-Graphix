//graphics
//done
//line plotting using its cartesian equation
//draws 20 random lines with random colors
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#define abs(x) (x<0?-x:x)
#define SIGN(x) (x<0?-1:1)
#define NUM 20
void drawline(int x1,int y1,int x2,int y2)
{if(x2==x1) return;
 if(x2-x1==0)return;
 float slope=1.0*(y2-y1)/(x2-x1);
 int color=getcolor();
 int incx=SIGN(x2-x1);
 for(int x=x1;x!=x2;x+=incx)
 {float y=slope*(x-x1)+y1;
  putpixel(x,y,color);
 }
return;
}
void main()
{
int gdriver=DETECT,gmode=0;
initgraph(&gdriver,&gmode,"d:\\tc\\bgi");
int x1,y1,x2,y2;
randomize();
cleardevice();

for(int i=0;i<NUM;i++)
{x1=random(640);
 x2=random(640);
 y1=random(480);
 y2=random(480);
 drawline(x1,y1,x2,y2);
 setcolor(random(16));
}
//closegraph();/**/
return;
}
