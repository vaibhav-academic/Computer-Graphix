//graphics
//Inside Outside Test Using Non Zero Side Winding Rule
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#define SIDES 6
#define MAXSIDES 100
#define BETWEEN(x,a,b) ( ((x)>=(a) && (x)<=(b)) || ((x)>=(b) && (x)<=(a)) )
#define SIGN(x) ((x)<0?-1:1)
#define LEFT 75
#define RIGHT 77
#define UP    72
#define DOWN  80
#define CTRLLEFT 115
#define CTRLRIGHT 116
#define CTRLUP    -115
#define CTRLDOWN  -111
struct Point{int x,y;};
struct Polygon{ Point points[MAXSIDES+1];int count;};
typedef struct {int x1,y1,x2,y2;}Line,Rect;
struct EdgeList{Line lines[MAXSIDES+1];int count;};

void drawPolygon(Polygon &p)
{p.points[p.count]=p.points[0];
 drawpoly(p.count+1,(int *) p.points);
 for(int i=0;i<p.count;i++)
 {char buff[4];
  sprintf(buff,"%d",i);
  setcolor(BLACK);
  fillellipse(p.points[i].x,p.points[i].y,textwidth(buff)-4,textheight(buff));
  setcolor(GREEN);
  outtextxy(p.points[i].x,p.points[i].y,buff);
 }
 setcolor(WHITE);
}

void generatePolygon(Polygon &p,int sides)
{randomize();
 if(sides>MAXSIDES) sides=MAXSIDES;
 if(sides<3) sides=3;
 for(int i=0;i<sides;i++)
	{p.points[i].x=random(640);
	 p.points[i].y=random(480);}
 p.count=sides;
}

void buildEdgeList(Polygon &p, EdgeList &edl)
{edl.count=p.count;
 Line (&lns)[]=edl.lines;
 Point (&pts)[]=p.points;
#define NEXTP(x) ((x+1)%p.count)
  for(int i=0;i<p.count;i++)
  { lns[i].x1=pts[i].x;lns[i].y1=pts[i].y;
    lns[i].x2=pts[NEXTP(i)].x;lns[i].y2=pts[NEXTP(i)].y;
    int a=SIGN(pts[i].y-pts[NEXTP(i)].y);
    int b=SIGN(pts[NEXTP(i)].y-pts[NEXTP(NEXTP(i))].y);
    if(a==b) lns[i].y2+=a*1;
  }
}

Rect getBoundingRect(const Polygon &p)
{Rect r={0};
 if(p.count>0){r.x1=p.points[0].x;r.y1=p.points[0].y;
	       r.x2=r.x1;r.y2=r.y1;}
 for(int i=0;i<p.count;i++)
 {if(p.points[i].x<r.x1) r.x1=p.points[i].x;
  if(p.points[i].y<r.y1) r.y1=p.points[i].y;
  if(p.points[i].x>r.x2) r.x2=p.points[i].x;
  if(p.points[i].y>r.y2) r.y2=p.points[i].y;
 }
return r;
}

int isInsidePolygon(Point pt,Polygon &p)
{Rect r=getBoundingRect(p);
 EdgeList e;
 buildEdgeList(p,e);
 Line (&lns)[]=e.lines;
 r.x1--; //set the scanpoint be outside the polygon
 int wind=0;
 int y=pt.y;
 for(int i=0;i<e.count;i++)
      if(BETWEEN(y,lns[i].y1,lns[i].y2)) //does scanline insersects edge
      {int x= lns[i].x1 + (y-lns[i].y1)
			 *1.0*(lns[i].x2-lns[i].x1)
			 /(lns[i].y2-lns[i].y1);
	if(BETWEEN(x,r.x1,pt.x))
		if(lns[i].y2-lns[i].y1==0)
		  wind+=SIGN(lns[i].x2-lns[i].x1);
		    else wind+=SIGN(lns[i].y2-lns[i].y1);

      }
 return wind;
}

void init()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
}

Polygon & addPoint(Polygon &p,int x,int y)
{Point pt={x,y};
 p.points[p.count]=pt;
 p.count++;
 return p;
}

void main()
{
 init();
 Polygon p={0};
 Point pt={60,70};
 generatePolygon(p,SIDES);
 char key;
 setfillstyle(EMPTY_FILL,BLACK);
 do{
 drawPolygon(p);
 putpixel(pt.x,pt.y,YELLOW);
 bar(0,0,50,20);
 if(isInsidePolygon(pt,p))
 outtextxy(0,10,"Inside");
 else outtextxy(0,10,"Out");
 key=getch();
 putpixel(pt.x,pt.y,BLACK);
 if(key==UP) pt.y--;
 if(key==DOWN) pt.y++;
 if(key==LEFT) pt.x--;
 if(key==RIGHT) pt.x++;
 if(key==CTRLUP) pt.y-=10;
 if(key==CTRLDOWN) pt.y+=10;
 if(key==CTRLLEFT) pt.x-=10;
 if(key==CTRLRIGHT) pt.x+=10;
}while(key!=27);
 //cleardevice();
}