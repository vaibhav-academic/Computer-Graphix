//project
#include <vjgraph.h>
#include <alloc.h>
#define DELAY 5
#define XRADIUS 10
#define YRADIUS 10
#define INCER 3

point ball={20,20};
int dx=INCER,dy=INCER;
void main(void)
{ void *buff,tuk();int imgsize;
  char nkey='a';
  init();
  setfillstyle(SOLID_FILL,getmaxcolor());
  fillellipse(ball.x,ball.y,XRADIUS,YRADIUS);
  imgsize=imagesize(ball.x-XRADIUS,ball.y-YRADIUS,
  ball.x+XRADIUS,ball.y+YRADIUS);
  buff=malloc(imgsize);
  if (buff==NULL){closegraph();printf("Error Allocating Memory");exit(1);}
  getimage(ball.x-XRADIUS,ball.y-YRADIUS,ball.x+XRADIUS,
		ball.y+YRADIUS,buff);
  while(nkey!=27)
  { putimage(ball.x-XRADIUS,ball.y-YRADIUS,buff,XOR_PUT);
    if (kbhit())
    { nkey=getch();
      if(nkey==13) {dx*=-1;dy*=-1;}
      if(nkey==UP_ARROW) dy=-INCER;
      if(nkey==DN_ARROW) dy=+INCER;
      if(nkey==RT_ARROW) dx=+INCER;
      if(nkey==LF_ARROW) dx=-INCER;
    }
    if((ball.x>=maxx-XRADIUS)||(ball.x<=XRADIUS))
    {dx*=-1;tuk();}
    if((ball.y>=maxy-YRADIUS)||(ball.y<=YRADIUS))
    {dy*=-1;tuk();}
    ball.x+=dx;ball.y+=dy;
    putimage(ball.x-XRADIUS,ball.y-YRADIUS,buff,XOR_PUT);
    delay(DELAY);
  }
free(buff);
closegraph();
}
void tuk(void)
{ int i; for(i=100;i<=200;i++,sound(i));
nosound();
}
