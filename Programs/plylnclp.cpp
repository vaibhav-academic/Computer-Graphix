//graphics
//Polygon Clipping using cohen-sutherland
//line clipping algorithm
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#define LEFT 1
#define RIGHT 2
#define TOP 4
#define BOTTOM 8
#define BETWEEN(x,a,b) ( ((x)>=(a) && (x)<=(b)) || ((x)>=(b) && (x)<=(a)) )
#define MAXSIDES 100
#define SIDES 6
typedef int Chcode;
typedef struct {int x1,y1,x2,y2;}Line,Rect;
struct Point{int x,y;};
struct Polygon{Point points[MAXSIDES+1];int count;};
Polygon p;

int isinside(Point p,Rect r)
{if(p.x<r.x1) return 0;
 if(p.x>r.x2) return 0;
 if(p.y<r.y1) return 0;
 if(p.y>r.y2) return 0;
return 1;
}

void addpolypoint(Polygon & p,Point pt)
{ int k=p.count-1;
  if(p.count==0||p.points[k].x!=pt.x||p.points[k].y!=pt.y)
  {p.points[p.count].x=pt.x;
   p.points[p.count].y=pt.y;
   p.count++;
  }
}
void drawpolygon(Polygon &p)
{p.points[p.count]=p.points[0];
 drawpoly(p.count+1,(int *) p.points);
 for(int i=0;i<p.count;i++)
 {char buff[4];
 }
 setcolor(WHITE);
}

void generatepolygon(Polygon &p,int sides)
{randomize();
 if(sides>MAXSIDES) sides=MAXSIDES;
  for(int i=0;i<sides;i++)
  {p.points[i].x=random(640);
   p.points[i].y=random(480);
  }
  p.count=sides;
}

Chcode getCohenCode(Point p,Rect r)
{Chcode c=0;
if(p.x<r.x1) c|=LEFT;
if(p.x>r.x2) c|=RIGHT;
if(p.y<r.y1) c|=TOP;
if(p.y>r.y2) c|=BOTTOM;
return c;
}

void cliplineatrect(Line &l,Rect r,Chcode *a)
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

void swappoints(Line &l)
{int temp=l.x1;l.x1=l.x2,l.x2=temp;
 temp=l.y1;l.y1=l.y2,l.y2=temp;
}

Polygon clippolygon(Polygon & p,Rect r)
{
#define NEXTP(x) (((x)+1)%p.count)
Polygon np={0};
 for(int i=0;i<p.count;i++)
 {int a=getCohenCode(p.points[i],r);
  int b=getCohenCode(p.points[NEXTP(i)],r);
  if(a&b) continue;
  Line l={p.points[i].x,p.points[i].y,p.points[NEXTP(i)].x,
	p.points[NEXTP(i)].y};
  cliplineatrect(l,r,&a);
  putpixel(l.x1,l.y1,RED);
  swappoints(l);
  cliplineatrect(l,r,&b);
  putpixel(l.x1,l.y1,RED);
  swappoints(l);
  if(!(a|b))
  {Point pt={l.x1,l.y1};
   addpolypoint(np,pt);
   pt.x=l.x2;pt.y=l.y2;
   addpolypoint(np,pt);
  }
 }
if(np.points[np.count-1].x==np.points[0].x&&
   np.points[np.count-1].y==np.points[0].y) np.count--;
return np;
}
void makepolygon(Polygon &p)
{Point p2[]=   {{getmaxx()/2-30-40,getmaxy()/2-30+30},
		{getmaxx()/2-30-40,getmaxy()/2+30+30},
		{getmaxx()/2+30-40,getmaxy()/2+30+30},
		{getmaxx()/2+30-40,getmaxy()/2-30+30},
		};
 p.points[0]=p2[0];
 p.points[1]=p2[1];
 p.points[2]=p2[2];
 p.points[3]=p2[3];
 p.count=4;
}
void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"d:\\tc\\bgi");
 Rect r={getmaxx()/2-50,getmaxy()/2-50,getmaxx()/2+50,getmaxy()/2+50};
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 generatepolygon(p,SIDES);
 //makepolygon(p);
 drawpolygon(p);
 rectangle(r.x1,r.y1,r.x2,r.y2);
 getch();
 cleardevice();
 rectangle(r.x1,r.y1,r.x2,r.y2);
 Polygon p2=clippolygon(p,r);
 drawpolygon(p2);/**/
 getch();
}


