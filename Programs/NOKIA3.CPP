//project
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#define RAND 10
#define DELAY 21
int main(void)
{ int gdriver = DETECT, gmode, errorcode;
  initgraph(&gdriver, &gmode, "");
  int maxx=getmaxx(),maxy=getmaxy(),r=3, extra;
  int x1=0,y1=0,incerx1=1,incery1=1,xs1=0,ys1=0,col1=15,r1=10,coco1=0;
  int x2=0,y2=0,incerx2=1,incery2=1,xs2=0,ys2=0,col2=15,r2=10;
   cleardevice();
   setlinestyle(0,2,1)  ;
   setfillstyle(1,15);
   settextstyle(0,0,1);
   /*x1=maxx/2;
   y1=maxy/2;*/
   while(1)
   {  coco1=rand()%500;
      /*if (coco1==131)
      cleardevice();*/
      if(coco1%200==0)
      { //randomize();
      	cleardevice();
        col1=rand()%10;
         if(col1==0)
         col1=15;}

      if(xs1==0)
      {x1=x1+incerx1;}
      if(ys1==0)
      {y1=y1+incery1;}
      if(xs1==1)
      {x1=x1-incerx1;}
      if(ys1==1)
      {y1=y1-incery1;}

      if(xs2==0)
      {x2=x2+incerx2;}
      if(ys2==0)
      {y2=y2+incery2;}
      if(xs2==1)
      {x2=x2-incerx2;}
      if(ys2==1)
      {y2=y2-incery2;}
      setcolor(col1);
      line(x1, y1, x2, y2);
      /*setfillstyle(1,col1);
      fillellipse(x1,y1,r,r);
      setfillstyle(1,col1);
      fillellipse(x2,y2,r,r);*/
      delay(DELAY);
      if(x1<r1)
      {incerx1=random(RAND);
       xs1=0;}
      if(x1>maxx-r1)
      {incerx1=random(RAND);
       xs1=1;}
      if(y1<r1)
      {ys1=0;
       incery1=random(RAND);}
      if(y1>maxy-r1)
      {ys1=1;
       incery1=random(RAND);
        if(col1==0)
        col1=15;
      }
     if(x2<r2)
     {incerx2=random(RAND);
       xs2=0;}
      if(x2>maxx-r2)
      {incerx2=random(RAND);
       xs2=1;}
      if(y2<r2)
      {ys2=0;
      incery2=random(RAND);}
      if(y2>maxy-r2)
     {ys2=1;
      incery2=random(RAND);
       if(col2==0)
       col2=15;
     }

     if(kbhit())
     { if(getch()=='p')
       getch()     ;
       else
       { closegraph();
      restorecrtmode();
      exit(1);
      }
    }

     }
}