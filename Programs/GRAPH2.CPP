//project
#include <complex.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <stdio.h>


float cot(float x)
{float yy;
 yy=1/tan(x);
  return yy;
}
float sec(float x)
{float yy;
 yy=1/cos(x);
  return yy;
}
float cosec(float x)
{float yy;
 yy=1/sin(x);
 return yy;
}
int main(void)
{ int gdriver = DETECT, gmode,fac=2,magi=11,dela=600;
  initgraph(&gdriver, &gmode, "");
  float x1=0,x2=0,prey1=(getmaxy()/4),prey2=getmaxy()-(getmaxy()/4);
  double y1,y2;
  float yy1=0,yy2=0,xx=0;
  while(1)
  {xx=20;
   cleardevice();

   /*line(1,getmaxy()/4,getmaxx(),getmaxy()/4);
   line(1,getmaxy()-(getmaxy()/4),getmaxx(),getmaxy()-(getmaxy()/4));
   line(1,getmaxy(),1,0);*/
   line(20,getmaxy()/2,getmaxx(),getmaxy()/2);
   line(18,getmaxy(),18,0);
     while(xx<=600)
     {
       y1=3*pow(x1,5)-5*pow(x1,3);  //Please Enter First Function Here
       //y2=(pow(x2,2)-1)/x2-1;
       //y2=(pow(x2,2)-1)/(x2-1);//Please Enter Second Function Here
       y1=y1*1;
       y2=y2*1;
       yy1=(getmaxy()/2)-y1;///this 2 was 4 before
       yy2=(getmaxy()/2)-y2;
      /*if(yy1>((getmaxy()/2)-10))
       yy1=((getmaxy()/2)-10);
       yy2=(getmaxy()-(getmaxy()/4))-y2;
       if (yy2<=((getmaxy()/2)+10))
       yy2=getmaxy();*/

     line(xx-fac,prey1,xx,yy1);
     //line(xx-fac,prey2,xx,yy2);
     prey1=yy1*10;
     prey2=yy2*10;
     xx=xx+fac;
     x1=x1+0.1;
     x2=x2+0.1;

   if(kbhit())
       if(getch()=='c')
       {getch();
       }
       else
       exit(1);

      delay(10);



   }

}
}
