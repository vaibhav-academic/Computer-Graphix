//graphics
//Rotation of a square
#include <math.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
class Square
{struct Point{float x,y;} points[4];
int degr;
public:
Square(int left,int top,int right,int bottom)
{points[0].x=left;points[0].y=top;
 points[1].x=right;points[1].y=top;
 points[2].x=right;points[2].y=bottom;
 points[3].x=left;points[3].y=bottom;
degr=0;
}
Square & draw()
{for(int i=1;i<4;i++)
 line(points[i-1].x+getmaxx()/2,points[i-1].y+getmaxy()/2,
	points[i].x+getmaxx()/2,points[i].y+getmaxy()/2);
 line(points[i-1].x+getmaxx()/2,points[i-1].y+getmaxy()/2,
	points[0].x+getmaxx()/2,points[0].y+getmaxy()/2);
putpixel(getmaxx()/2,getmaxy()/2,WHITE);
return *this;
}

Square & rotate(int deg)
{double rad=-M_PI*deg/180;
for(int i=0;i<4;i++)
{Point p=points[i];
 points[i].x= p.x*cos(rad)-p.y*sin(rad);
 points[i].y= p.y*cos(rad)+p.x*sin(rad);
}
degr+=deg;
return *this;
}
};

void main()
{int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc\\bgi");
Square sq(-50,-50,
	  +50,+50);
Square sqs[]={sq,sq.rotate(6),sq.rotate(6),sq.rotate(6)};
char key;
int del=10;
do
{setcolor(WHITE);
for(int i=0;i<1;i++) sqs[i].rotate(-1).draw();
delay(del);
setcolor(BLACK);
for(i=0;i<1;i++) sqs[i].draw();
if(kbhit())
	switch(key=getch())
	{case 80:del+=2;break;
	 case 72:del-= (del>0?2:0);break;
	 default:break;
	}
//cleardevice();
}while(key!=27);
}
