//graphics
//A text Based Paint Brush Program
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2

char far *screen=(char*)MK_FP(0xb800,0);

typedef struct {int x,y;}Point;
typedef  unsigned Buttons;
void setMousePtr(unsigned andmask,unsigned xormask)
{REGS regi;
regi.x.ax=0xa;
regi.x.bx=0;
regi.x.cx=andmask;
regi.x.dx=xormask;
int86(0x33,&regi,&regi);
}
int InitMouse()
{REGS regi;
regi.x.ax=0;
int86(0x33,&regi,&regi);
return !!regi.x.ax;
}

Point * getMousePos(Point *p)
{REGS regi,rego;
regi.x.ax=0x3;
int86(0x33,&regi,&regi);
p->x=regi.x.cx;
p->y=regi.x.dx;
return p;
}
Buttons * getButtonStatus(Buttons *b)
{REGS regi;
regi.x.ax=0x5;
int86(0x33,&regi,&regi);
*b=regi.x.ax;
return b;
}
void ShowMouse()
{REGS regi;
regi.x.ax=0x1;
int86(0x33,&regi,&regi);
}
void HideMouse()
{REGS regi;
regi.x.ax=0x2;
int86(0x33,&regi,&regi);
}
int main()
{int color=1;
clrscr();
InitMouse();
//setMousePtr(0xf0ff,color<<8);
*(screen)='*';*(screen+1)=color;
ShowMouse();
Point p;
Buttons b;
while(!kbhit())
 { delay(10);
   getMousePos(&p);
   getButtonStatus(&b);
   if(b&LEFT_BUTTON && b&RIGHT_BUTTON)
    {clrscr();
    *(screen)='*';*(screen+1)=color;
    continue;
    }

   if(b&LEFT_BUTTON)
   {HideMouse();
    p.y<<=2,p.x>>=2,*(screen+p.x+p.y*5)=(char)'*';
   *(screen+p.x+p.y*5+1)=color;
   ShowMouse();
   }
   if(b&RIGHT_BUTTON) {color=(color+1)%16;*(screen+1)=color;}

 }
HideMouse();
return 0;
}