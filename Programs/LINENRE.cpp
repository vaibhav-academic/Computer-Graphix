//Graphics
//Line drawing Algo using Bresenham`s Method
//(c) Vaibhav Jain
//date:14/4/04
#include <graphics.h>
#include <conio.h>
#define SIGN(a) (a<0?-1:1)
void swap(int *a,int *b)
{int c=*a;
 *a=*b,*b=c;
}
void drawgrid()
{int maxx=getmaxx(),maxy=getmaxy();
 int i;
 setcolor(DARKGRAY);
 for(i=0;i<maxx;i+=10) line(i,0,i,maxy);
 for(i=0;i<maxy;i+=10) line(0,i,maxx,i);
}
void drawline(int x1,int y1,int x2,int y2)
{ int xx=0,yy=0,mx=1,my=1;
  int *x=&xx,*y=&yy;
  int dx=x2-x1,dy=y2-y1,p;
  x2=dx;y2=dy;
  if(dx<0)mx*=-1,dx*=-1,x2*=-1;
  if(dy<0)my*=-1,dy*=-1,y2*=-1;
  if(dx<dy)
	{int temp=dx;
	 dx=dy,dy=temp,x2=y2,x=&yy,y=&xx;
	}
  for(p=0;x2>=0;(*x)++,x2--)
  { putpixel(x1+mx*xx,y1+my*yy,WHITE);
    if(p>0)
	{p=p+2*dy-2*dx;
	 (*y)++;
	}else
	 p=p+2*dy;
  }
return;
}

void main()
{ int gd=DETECT,gm;
 char keycode='a';
 int x1=50,y1=50,x2=70,y2=20;
  initgraph(&gd,&gm,"d:\\tc\\bgi");
  cleardevice();
  drawgrid();

 while(keycode!=27)
 {
 setfillstyle(SOLID_FILL,BLUE);
 fillellipse(x1,y1,2,2);
 setfillstyle(SOLID_FILL,RED);
 fillellipse(x2,y2,2,2);
 //line(x1,y1,x2,y2);
 drawline(x1,y1,x2,y2);
 keycode=getch();
 switch(keycode)
	{case 75:x2-=10;break;
	 case 77:x2+=10;break;
	 case 72:y2-=10;break;
	 case 80:y2+=10;break;
	 case 115:x1-=10;break;
	 case 116:x1+=10;break;
	 case -115:y1-=10;break;
	 case -111:y1+=10;break;
	 case 13:
	 case ' ':cleardevice();
		   drawgrid();
		   break;
	}
 }
}
