//project
#include <dos.h>
#include <graphics.h>
#include <conio.h>
#define DELAY 10
#define XRADIUS 10
#define YRADIUS 10
typedef struct { int x,y;} point;
void tuk(void)
{ int i; for(i=1000;i<=2000;i++,sound(i));
nosound();
}
int maxx,maxy;
int main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   point ball={20,20};
   int dx=5,dy=5;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();

   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
  maxx=getmaxx();  maxy=getmaxy();
  setcolor(0);
  while(!kbhit())
  { setfillstyle(1,0);
    fillellipse(ball.x,ball.y,XRADIUS,YRADIUS);
    if((ball.x>=maxx-XRADIUS)||(ball.x<=XRADIUS)) {dx*=-1;tuk();}
    if((ball.y>=maxy-YRADIUS)||(ball.y<=YRADIUS)) {dy*=-1;tuk();}
    ball.x+=dx;ball.y+=dy;
    setfillstyle(1,15);
    fillellipse(ball.x,ball.y,XRADIUS,YRADIUS);
    delay(DELAY);
  }
return 0;
}