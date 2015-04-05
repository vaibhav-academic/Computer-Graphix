//project
#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#define DELAY  0
int main(void)
{ int gdriver = DETECT, gmode, errorcode;
   int x=100,y=70,add=70;
    initgraph(&gdriver, &gmode, "");
    int color=11;   int mx=getmaxy();
 while(1)
 { x=random(500)+30;
   add=70;



  while(add<mx)
  {setfillstyle(1  ,color);


    add=add+20;
    while(y>add)
   {
      y=y-1;
       fillellipse(x,y,10,10);
       delay(DELAY);
       setcolor(0);
       fillellipse(x,y,10,10);
       if(kbhit())
	{ exit(1);
	}
     }



   setfillstyle(1 ,color);
   while(y<=mx)
    {  y=y+1;

      fillellipse(x,y,10,10);
      delay(DELAY);
       setcolor(0);
      fillellipse(x,y,10,10);
      if(kbhit())
      { exit(1);
     }
    }
    cleardevice();

   }

   }



    closegraph();

   restorecrtmode();

   return 0;


}