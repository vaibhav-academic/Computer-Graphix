//graphics
//boundry fill using auxillary stack optimization
//(c) Vaibhav Jain
#include <dos.h>
#include <graphics.h>
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

void boundryfill(int seedx,int seedy,int boundry,int color)
{Point p(seedx,seedy);
 s.push(p);
 do
 {p=s.pop();
  if(getpixel(p.x,p.y)==boundry) continue;
  while(getpixel(p.x,p.y)!=boundry)p.x--;
  p.x++;
  int flagup=false,flagdown=false;
  int cup,cdwn;
  while(getpixel(p.x,p.y)!=boundry)
  {cup=getpixel(p.x,p.y-1);
   cdwn=getpixel(p.x,p.y+1);
   if(cup==boundry||cup==color) flagup=false;
   else if(!flagup)
   {flagup=true;
    s.push(Point(p.x,p.y-1));
    }
  if(cdwn==boundry||cdwn==color) flagdown=false;
   else if(!flagdown)
   {flagdown=true;
    s.push(Point(p.x,p.y+1));
    }
  putpixel(p.x,p.y,color);
  p.x++;
  }
 }while(!s.isempty());
 s.reset();
}

void boundryfill(Point seed,int boundry,int color)
{boundryfill(seed.x,seed.y,boundry,color);}

void main()
{init();
 //rectangle(getmaxx()/2-50,getmaxy()/2-150,
  //	   getmaxx()/2+150,getmaxy()/2+150);

 setfillstyle(SOLID_FILL,RED);
 fillellipse(getmaxx()/2,getmaxy()/2,80,80);


 setfillstyle(SOLID_FILL,GREEN);
 fillellipse(getmaxx()/2,getmaxy()/2,50,50);

  setfillstyle(SOLID_FILL,BLUE);
 fillellipse(getmaxx()/2,getmaxy()/2,30,30);

 getch();
 boundryfill(getmaxx()/2,getmaxy()/2,BLACK,LIGHTCYAN);
 getch();
}