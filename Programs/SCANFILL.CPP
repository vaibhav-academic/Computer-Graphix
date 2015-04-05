//graphics
//scanfill algorithm implementation without vertext correction
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#define SIDES 10
#define MAXSIDES 20
#define BETWEEN(x,a,b) ( ((x)>=(a) && (x)<=(b)) || ((x)>=(b) && (x)<=(a)) )
struct Point{int x,y;};
struct Polygon{ Point points[MAXSIDES+1];int count;};
typedef struct {int x1,y1,x2,y2;}Line,Rect;
void bubblesort(int c,int * arr)
{c--;
 for(int i=0;i<c;i++)
  for(int j=0;j<(c-i);j++)
  if(arr[j]>arr[j+1])
	  {int temp=arr[j];
	   arr[j]=arr[j+1];
	   arr[j+1]=temp;}
}

int removeduplicates(int c,int *arr)
{for(int i=0,j=0;i<c;i++)
      if(arr[j]!=arr[i])
       arr[++j]=arr[i];
return j+1;
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
 Point (&pts)[]=p.points;
 int *arr=new int[p.count];
 for(int y=r.y1;y<=r.y2;y++)
 {int index=0;
  for(int i=0;i<p.count;i++)
      if(BETWEEN(y,pts[i].y,pts[NEXTP(i)].y))
      {int x= pts[i].x + (y-pts[i].y)
			 *1.0*(pts[NEXTP(i)].x-pts[i].x)
			 /(pts[NEXTP(i)].y-pts[i].y);
       arr[index++]=x;
      }
      else
      continue;
  bubblesort(index,arr);
  index=removeduplicates(index,arr);
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
 generatePolygon(p,SIDES);
 drawPolygon(p);
 Rect r=getBoundingRect(p);
 //rectangle(r.x1,r.y1,r.x2,r.y2);
 getch();
 scanFill(p,~LIGHTRED);
 getch();
}