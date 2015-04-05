//graphics
//circle drawing using polar equation
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
void drawcircle(int xx,int yy,unsigned radius)
{ float theta=0,inc=1.0/radius;
  for(theta=0;theta<=M_PI_4;theta+=inc)
  {int x=radius*cos(theta);
   int y=radius*sin(theta);
   putpixel(x+xx,y+yy,WHITE);
   putpixel(-x+xx,y+yy,WHITE);
   putpixel(-x+xx,-y+yy,WHITE);
   putpixel(x+xx,-y+yy,WHITE);

   putpixel(y+xx,x+yy,WHITE);
   putpixel(-y+xx,x+yy,WHITE);
   putpixel(-y+xx,-x+yy,WHITE);
   putpixel(y+xx,-x+yy,WHITE);
}


}
void main()
{int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc\\bgi");
randomize();
for(int i=0;i<40;i++)
drawcircle(random(560)+40,random(400)+40,random(40)+1);
getch();
}