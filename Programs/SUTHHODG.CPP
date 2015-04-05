//graphics
//sutherland-hodgement polygon clipping algorithm
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#define BETWEEN(x,a,b) ( ((x)>=(a) && (x)<=(b)) || ((x)>=(b) && (x)<=(a)) )
#define MAXSIDES 30
#define SIDES 7

typedef int Chcode;
typedef struct {int x1,y1,x2,y2;}Line,Rect;
struct Point{int x,y;
	     Point(int xx,int yy):x(xx),y(yy){}
	     Point():x(0),y(0){}
	    };
struct Polygon{Point points[MAXSIDES+2];int count;};
struct EdgeList{Line lines[MAXSIDES+1];int count;};

enum Edge{Left,Right,Top,Bottom};
Polygon p;

void drawEdgeList(EdgeList &e)
{for(int i=0;i<e.count;i++)
 line(e.lines[i].x1,e.lines[i].y1,e.lines[i].x2,e.lines[i].y2);
}

Polygon & buildPolygonFromEdgeList(const EdgeList &els,Polygon &np)
{np.count=0;
if(els.count==0) return np;
 Point *arr=(Point*)els.lines;
 np.points[0]=arr[0];
 for(int i=1;i<2*els.count;i++)
 if(arr[i].x!=np.points[np.count].x||
     arr[i].y!=np.points[np.count].y)
	np.count++, np.points[np.count]=arr[i];
np.count++;
return np;
}

void createEdgeList(Polygon &p, EdgeList &edl)
{edl.count=p.count;
#define NEXTP(x) (((x)+1)%p.count)
  for(int i=0;i<p.count;i++)
  {edl.lines[i].x1=p.points[i].x;
   edl.lines[i].y1=p.points[i].y;
   edl.lines[i].x2=p.points[NEXTP(i)].x;
   edl.lines[i].y2=p.points[NEXTP(i)].y;
  }
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
  sprintf(buff,"%d",i);
  setcolor(BLACK);
  fillellipse(p.points[i].x,p.points[i].y,textwidth(buff),textheight(buff));
  setcolor(GREEN);
  outtextxy(p.points[i].x,p.points[i].y,buff);
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

isInsideEdge(Point &pt,Rect & r,Edge e)
{switch(e)
{case Left: return pt.x>r.x1;
 case Right: return pt.x<r.x2;
 case Top: return pt.y<r.y2;
 case Bottom: return pt.y>r.y1;
 default:return 0;
}
}

int clipLineAtEdge(Line &l,Rect r,Edge e)
{int h;
int a=isInsideEdge(Point(l.x1,l.y1),r,e); //is x1,y1 inside the edge
int b=isInsideEdge(Point(l.x2,l.y2),r,e); //is x2,y2 inside the edge

if(e==Left) h=r.x1;
else if(e==Right) h=r.x2;
else if(e==Top)  h=r.y2;
else if(e==Bottom) h=r.y1;
if(e==Left||e==Right)
      {
	if(a^b)	//is the line crossing the edge
       {int y=l.y1+(h-l.x1)*1.0*(l.y2-l.y1)/(l.x2-l.x1); //get y intercept
	 putpixel(h,y,RED);
	 if(a==1) l.x2=h,l.y2=y;
	 else /*b==1*/ l.x1=h,l.y1=y;
       }
	 else if((a&b)==0) return 0;//is the line outside inside
	 //the clipping edge no need to clip this line ignore;
	 //if a&b==1 then both points are inside the edge
	return 1;
      }
else /*if(e==Top||e==Bottom)*/
      {
       if(a^b)	//is the line crossing the edge
       {int x= l.x1+(h-l.y1)*1.0*(l.x2-l.x1)/(l.y2-l.y1);
	 if(a==1) l.x2=x,l.y2=h;
	 else /*b==0*/ l.x1=x,l.y1=h;
	 putpixel(x,h,RED);
       }
	 else if((a&b)==0) return 0;//is the line outside inside
	 //the clipping edge no need to clip this line ignore;
	 //if a&b==1 then both points are inside the edge
	return 1;
      }
}
void correctEdges(EdgeList &els) //corrects broken edges in edge list
{Line *arr=els.lines;
#define PREEDGE(x) ((x+els.count-1)%els.count)
#define NXTEDGE(x) ((x+1)%els.count)
 for(int i=0;i<els.count;i++)
 if(arr[PREEDGE(i)].x2!=arr[i].x1 ||
     arr[PREEDGE(i)].y2!=arr[i].y1)
	{ for(int j=els.count;j>i;j--)
	   arr[j]=arr[j-1];
	   els.count++;
	   arr[i].x1=arr[PREEDGE(i)].x2;
	   arr[i].y1=arr[PREEDGE(i)].y2;
	   arr[i].x2=arr[NXTEDGE(i)].x1;
	   arr[i].y2=arr[NXTEDGE(i)].y1;
	}
}

Polygon &clipPolygon(Polygon & p,Rect r,Polygon &np)
{
EdgeList els;
createEdgeList(p,els);
for(Edge e=Left;e<=Bottom;((int)e)++)
 {int count=0;
  for(int i=0;i<els.count;i++)
  if(clipLineAtEdge(els.lines[i],r,e)) //line cannot be ignored
	 els.lines[count]=els.lines[i],count++;
 els.count=count;
 correctEdges(els);
 cleardevice();
 setcolor(GREEN);
 drawpolygon(p);
 setcolor(GREEN);
 rectangle(r.x1,r.y1,r.x2,r.y2);
 setcolor(WHITE);
 drawEdgeList(els);
 getch();
 }
buildPolygonFromEdgeList(els,np);
return np;
}

void makepolygon(Polygon &p)
{Point p2[]=   {Point(getmaxx()/2-30-40,getmaxy()/2-30+30),
		Point(getmaxx()/2-30-40,getmaxy()/2+30+30),
		Point(getmaxx()/2+30-40,getmaxy()/2+30+30),
		Point(getmaxx()/2+30-40,getmaxy()/2-30+30),
		};
 p.points[0]=p2[0];
 p.points[1]=p2[1];
 p.points[2]=p2[2];
 p.points[3]=p2[3];
 p.count=4;
}

void main()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 Rect r={getmaxx()/2-50,getmaxy()/2-50,getmaxx()/2+50,getmaxy()/2+50};
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 generatepolygon(p,SIDES);
 //makepolygon(p);
 drawpolygon(p);
 rectangle(r.x1,r.y1,r.x2,r.y2);
 getch();

 cleardevice();
 rectangle(r.x1,r.y1,r.x2,r.y2);
 setcolor(GREEN);
 drawpolygon(p);
	 Polygon p2;
	 clipPolygon(p,r,p2);
	 setlinestyle(SOLID_LINE,0,3);
	 setcolor(RED);
	 drawpolygon(p2);
 getch();
}