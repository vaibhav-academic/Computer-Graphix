//graphics
//Flood fill using auxillary stack optimization
//(c) Vaibhav Jain
#include <dos.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <.\vaibhav\stack.h>
#define true 1
#define false 0

struct Point	{int x,y;
		public:	Point(int px,int py):x(px),y(py){}
			Point(){}
		};

Stack<Point>s;
void init()
{int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
}

void floodfill(int seedx,int seedy,int background,int color)
{Point p(seedx,seedy);
 s.push(p);
 do
 {int flagtop=true,flagbottom=true;
  int clrup,clrdwn;

  p=s.pop();
  if(getpixel(p.x,p.y)!=background) continue;
  while(getpixel(p.x,p.y)==background)p.x--;
  p.x++;
	while(getpixel(p.x,p.y)==background)
		  {clrup=getpixel(p.x,p.y-1);
		   clrdwn=getpixel(p.x,p.y+1);
		   if(clrup==background && flagtop==true)
			   {flagtop=false;
			    s.push(Point(p.x,p.y-1));
			    }else
			    if(clrup!=background)
				flagtop=true;
		   if(clrdwn==background && flagbottom==true)
			    {flagbottom=false;
			    s.push(Point(p.x,p.y+1));
			    }else
			    if(clrdwn!=background)
				flagbottom=true;
		  putpixel(p.x,p.y,color);
		  p.x++;
		  //delay(2);
		  }
 }while(!s.isempty());
 s.reset();
}

inline void floodfill(Point seed,int boundry,int color)
{floodfill(seed.x,seed.y,boundry,color);}

void main()
{init();
 rectangle(getmaxx()/2-50,getmaxy()/2-150,
	   getmaxx()/2+150,getmaxy()/2+150);
 circle(getmaxx()/2-20,getmaxy()/2,60);
 circle(getmaxx()/2-10,getmaxy()/2,90);
 floodfill(getmaxx()/2+81,getmaxy()/2,BLACK,BLUE);
 floodfill(getmaxx()/2+71,getmaxy()/2,BLACK,GREEN);
 floodfill(getmaxx()/2-51,getmaxy()/2,BLACK,LIGHTRED);
 getch();
}