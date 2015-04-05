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
{if(a<=0||b<=0) return;
 int a2=a*a;
 int b2=b*b;
 if(a>b)
 for(int x=0;x<=a;x++)
 {int y=(int)sqrt(1.0*(a2-x*x)/a2*b2);
  putpixel(cx+x,cy+y,WHITE);
  putpixel(cx+x,cy-y,WHITE);
  putpixel(cx-x,cy+y,WHITE);
  putpixel(cx-x,cy-y,WHITE);
 }
 else
 for(int y=0;y<=b;y++)
 {int x=(int)sqrt(1.0*(b2-y*y)/b2*a2);
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