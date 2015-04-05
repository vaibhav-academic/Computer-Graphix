//graphics
//Computer Graphics
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
void main()
{int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc\\bgi");
int cx=getmaxx()/2,cy=getmaxy()/2;
int r=320;
float phase=0.0;
setfillstyle(SOLID_FILL,BLACK);
while(!kbhit())
{

delay(10);
//cleardevice();
bar(cx-2*r,cy-2*r,cx+2*r,cy+2*r);
phase+=0.01;
for(float t=phase;t<(2*M_PI+phase);t+=M_PI/10)
{ int cxx=cx+(r-10)*cos(t);
  int cyy=cy+(r-10)*sin(t);
  circle(cxx,cyy,r);
}

}
getch();
}