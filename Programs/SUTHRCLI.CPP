//graphics
//conhen sutherland line clipping algorithm
//draws 100 random lines at clips it against
//a given reactangle
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define LEFT 1
#define RIGHT 2
#define TOP 4
#define BOTTOM 8
#define NUM 30
#define BETWEEN(x,a,b) ( ((x)>=(a) && (x)<=(b)) || ((x)>=(b) && (x)<=(a)) )

struct point{int x,y;};
struct line{int x1,y1,x2,y2,color;};
typedef struct line rect;
typedef int Chcode;

struct line lines[NUM];

void cliplineatrect(struct line &l,rect r,Chcode *a)
{if(*a&LEFT)
	 { int y=l.y1+(r.x1-l.x1)*1.0*(l.y2-l.y1)/(l.x2-l.x1);
	   if(BETWEEN(y,r.y1,r.y2))
	    *a=0,l.x1=r.x1,l.y1=y;
	 }
 if(*a&RIGHT)
	 { int y= l.y1+(r.x2-l.x1)*1.0*(l.y2-l.y1)/(l.x2-l.x1);
	   if(BETWEEN(y,r.y1,r.y2))
	    *a=0,l.x1=r.x2,l.y1=y;
	 }

 if(*a&TOP)
	 { int x= l.x1+(r.y1-l.y1)*1.0*(l.x2-l.x1)/(l.y2-l.y1);
	   if(BETWEEN(x,r.x1,r.x2))
	    *a=0,l.x1=x,l.y1=r.y1;
	 }

 if(*a&BOTTOM)
	 { int x= l.x1+(r.y2-l.y1)*1.0*(l.x2-l.x1)/(l.y2-l.y1);
	   if(BETWEEN(x,r.x1,r.x2))
	    *a=0,l.x1=x,l.y1=r.y2;
	 }
}

void init()
{randomize();
for(int i=0;i<NUM;i++)
 {
   lines[i].x1=random(640);
   lines[i].x2=random(640);
   lines[i].y1=random(480);
   lines[i].y2=random(480);
   lines[i].color=random(15);
 }
}

inline void drawline(struct line l,int /*index*/)
{setcolor(l.color);
 line(l.x1,l.y1,l.x2,l.y2);
 //char buff[6];
 //sprintf(buff,"%d",index);
 //outtextxy(l.x1,l.y1,buff);
 //outtextxy(l.x2,l.y2,buff);
 }

void drawlines()
{for(int i=0;i<NUM;i++)
 drawline(lines[i],i);
}

Chcode getCohenCode(int x,int y,rect r)
{Chcode c=0;
if(x<r.x1) c|=LEFT;
if(x>r.x2) c|=RIGHT;
if(y<r.y1) c|=TOP;
if(y>r.y2) c|=BOTTOM;
return c;
}

void swappoints(struct line &l)
{int temp=l.x1;l.x1=l.x2,l.x2=temp;
 temp=l.y1;l.y1=l.y2,l.y2=temp;
}

void drawclipped(rect r)
{
 for(int i=0;i<NUM;i++)
 {int a=getCohenCode(lines[i].x1,lines[i].y1,r);//code for x1,y1
  int b=getCohenCode(lines[i].x2,lines[i].y2,r);//code for x2,y2
  if((a&b)!=0) continue; //line is rejected
  cliplineatrect(lines[i],r,&a);
  swappoints(lines[i]);
  cliplineatrect(lines[i],r,&b);
  if(!(a|b))/**/
  drawline(lines[i],i);
 }

}
void drawrectangle(rect r)
{rectangle(r.x1,r.y1,r.x2,r.y2);
}
void main()
{int gd=DETECT ,gm;
initgraph(&gd,&gm,"d:\\tc\\bgi");
rect r={50,50,350,350};
init();
drawlines();
setcolor(WHITE);
setlinestyle(SOLID_LINE,0,3);
drawrectangle(r);
getch();
cleardevice();
setlinestyle(SOLID_LINE,0,1);
drawclipped(r);
setcolor(WHITE);
setlinestyle(SOLID_LINE,0,3);
drawrectangle(r);
getch();
return;
}