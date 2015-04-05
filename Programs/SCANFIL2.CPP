//graphics
//Scanfilling with vertex intersection solved
//by shorting of segments
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#define SIDES 10
#define MAXSIDES 20
#define BETWEEN(x,a,b) ( ((x)>=(a) && (x)<=(b)) || ((x)>=(b) && (x)<=(a)) )
#define SIGN(x) ((x)<0?-1:1)
struct Point{int x,y;};
struct Polygon{ Point points[MAXSIDES+1];int count;};
typedef struct {int x1,y1,x2,y2;}Line,Rect;
struct EdgeList{Line lines[MAXSIDES+1];int count;};
void bubblesort(int c,int * arr)
{c--;
 for(int i=0;i<c;i++)
  for(int j=0;j<(c-i);j++)
  if(arr[j]>arr[j+1])
	  {int temp=arr[j];
	   arr[j]=arr[j+1];
	   arr[j+1]=temp;}
}

void drawPolygon(Polygon &p)
{p.points[p.count]=p.points[0];
 drawpoly(p.count+1,(int*) p.points);
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
void drawEdgeList(EdgeList &e)
{for(int i=0;i<e.count;i++)
 line(e.lines[i].x1,e.lines[i].y1,e.lines[i].x2,e.lines[i].y2);
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

void scanFill(Polygon &p,int color=RED)
{Rect r=getBoundingRect(p);
#define NEXTP(x) ((x+1)%p.count)
 EdgeList e; buildEdgeList(p,e);
 Line (&lns)[]=e.lines;
 int *arr=new int[e.count];
 for(int y=r.y1;y<=r.y2;y++)
 {int index=0;
  for(int i=0;i<e.count;i++)
      if(BETWEEN(y,lns[i].y1,lns[i].y2))
      {int x= lns[i].x1 + (y-lns[i].y1)
			 *1.0*(lns[i].x2-lns[i].x1)
			 /(lns[i].y2-lns[i].y1);
       arr[index++]=x;
      }
      else
      continue;
  bubblesort(index,arr);
  setcolor(color);
  for(i=0;i<index-1;i++)
   if(i%2==0)
   line(arr[i],y,arr[i+1],y);
 }
 delete []arr;
}
void init()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
}
void main()
{init();
 Polygon p;
 EdgeList e;
 generatePolygon(p,SIDES);
 drawPolygon(p);
 Rect r=getBoundingRect(p);
 //rectangle(r.x1,r.y1,r.x2,r.y2);
 getch();
 cleardevice();
 //buildEdgeList(p,e);
 //drawEdgeList(e);
 //getch();
 scanFill(p,LIGHTGRAY);
 getch();
}