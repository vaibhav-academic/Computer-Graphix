//graphics
//A 3D View of a Plane diminishing in the Horizan
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
void main()
{int gd=DETECT,gm;
 char key;
 int viewheight=100,viewdistance=20;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 do{
 cleardevice();
 if(key==UP) viewheight+=10;
 if(key==DOWN) viewheight-=10;
 if(key==LEFT) viewdistance+=1;
 if(key==RIGHT) viewdistance-=1;

 int y;
 for(int i=0;i<100;i+=5)
 {y=1.0*viewheight*i/(i+viewdistance);
  y=getmaxy()/1.2-y;
  line(0,y,getmaxx(),y);
 }
 for(i=-1600;i<1600;i+=100)
 {int x1=getmaxx()/2+i;
  int x2=getmaxx()/2+i*viewdistance/(100+viewdistance);
  line(x1,getmaxy()/1.2,x2,y);
 }

 key=getch();
 }while(key!=27);
}
