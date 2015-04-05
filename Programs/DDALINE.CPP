//graphics
//line plotting using DDA
#include <graphics.h>
#include <conio.h>
#define abs(x) (x<0?-x:x)
void drawline(int x1,int y1,int x2,int y2)
{int dx=x2-x1;
 int dy=y2-y1;
 int step=abs(dy);
 if(abs(dx)>abs(dy))
 step=abs(dx);
 float xincr=1.0*dx/step;
 float yincr=1.0*dy/step;
 for(float x=x1,y=y1;step--;)
 {putpixel(x,y,WHITE);
 x+=xincr;
 y+=yincr;
 }
return;
}
void main()
{char key='a';
int gdriver=DETECT,gmode=0;
initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
int x=100,y=20;
while(key!=27)
{drawline(0,0,x,y);
switch(key)
{case 75:x--;break;
 case 77:x++;break;
 case 72:y--;break;
 case 80:y++;break;
 case 13:case ' ':key=27;continue;
}
key=getch();
cleardevice();
}
return;
}
