//graphics
//Drawing and Ellipse with give value of center and A,B
//using its cartesian equation
//(c) Vaibhav Jain
//date: 14/4/04;
#include <graphics.h>
#include <conio.h>
#include <math.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void drawellipse(int cx,int cy,int b,int a)
{ for(float theta=0;theta<=M_PI_2;theta+=0.01)
  {float r=a*b/sqrt((float)b*b*cos(theta)*cos(theta)+
		  a*a*sin(theta)*sin(theta));
  int x=r*cos(theta);
  int y=r*sin(theta);
  putpixel(cx+x,cy+y,WHITE);
  putpixel(cx+x,cy-y,WHITE);
  putpixel(cx-x,cy+y,WHITE);
  putpixel(cx-x,cy-y,WHITE);
  }
}

void main()
{int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc\\bgi");
int a=150,b=50;
char key;
do
{cleardevice();
 drawellipse(getmaxx()/2,getmaxy()/2,a,b);
 key=getch();
 if(key==UP) a+=10;
 if(key==DOWN) a-=10;
 if(key==RIGHT) b+=10;
 if(key==LEFT) b-=10;
}while(key!=27);
}