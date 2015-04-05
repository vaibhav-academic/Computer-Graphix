//project
#include "vjbox.h"
#include <assert.h>
#define GAMEOVER "\n\r        Game Over!!!!      \n\r"
#define RENDER 1000
int score=0,level=1,counter=RENDER;
void drawcarxy(),fill(),render(),regen();
point car={10,10};
point cars[4];
void main()
{void generate();
int nkey='a';
car.y=midpoint().y*1.5;
car.x=midpoint().x-4;
clrscr();
generate();
while(nkey!=27)
{ if (counter>=RENDER) {render();counter=0;
  if(collided()) {msgbox(GAMEOVER);wait();exit(1);}
  }
  counter++;
  if (kbhit())
  {nkey=getch();
   switch (nkey)
   {case LF_ARROW:if (car.x==midpoint().x-4) break;
    		  textcolor(0);drawcarxy(car.x,car.y);
   		  textcolor(15);car.x=midpoint().x-4;
		  counter=RENDER;break;
    case RT_ARROW:if (car.x==midpoint().x+4) break;
                  textcolor(0);drawcarxy(car.x,car.y);
   		  textcolor(15);car.x=midpoint().x+4;
		  counter=RENDER;break;
    case SPACE_BAR :counter=RENDER;break;
    case ESCAPE_KEY:counter=RENDER;break;
   }
  }
}


}
void generate()
{int i;
for(i=0;i<3;i++)
{regen(&cars[i]);
cars[i].y=i*10;
}
}
void regen(point * car)
{car->y=-9;
 if (rand()%2) car->x=midpoint().x-4;
 else car->x=midpoint().x+4;
}
void drawcarxy(int x,int y)
{fill(x-3,y,x+3,y,'#');
 fill(x,y-1,x,y+3,'#');
 fill(x-3,y+3,x+3,y+3,'#');
}
void render()
{void footpath(void);int i;
for(i=0;i<3;i++)
{textcolor(0);
drawcarxy(cars[i].x,cars[i].y);
cars[i].y++;
if (cars[i].y>midpoint().y*2+2) regen(&cars[i]);
textcolor(15);
drawcarxy(cars[i].x,cars[i].y);
}
 drawcarxy(car.x,car.y);
 footpath();
gotoxy(60,24);printf("Score:%u",score);
}
void footpath(void)
{static int count=0;
 point mid;int i;
 mid=midpoint();
 for(i=mid.y*2;i>1;i--,count++)
 { if (count%3==0)
   {  gotoxy(mid.x-9 ,i);putch(' ');
      gotoxy(mid.x+9,i);putch(' ');
   }
     else
   {  gotoxy(mid.x-9 ,i);putch('*');
      gotoxy(mid.x+9,i);putch('*');
   }
  }
if (count>=9000) count=0;
}
int collided(void)
{ int i;point ca;
for(i=0;i<=3;i++)
{ ca=cars[i];
if ((car.x==ca.x)&&between(car.y-ca.y,-3,+3)) return 1;
if (car.y==ca.y){
		score+=level*10;
		}
}
return 0;
}
int between( int exp,int r1,int r2)
{ if ((exp>=r1)&&(exp<=r2)) return 1; else return 0;
}