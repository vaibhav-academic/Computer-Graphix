#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2
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
{
InitMouse();
setMousePtr(0x07ff,0x1800);
ShowMouse();
Point p;
Buttons b;
 while(!kbhit())
 { delay(10);
   getMousePos(&p);
  //gotoxy(1,1);
   getButtonStatus(&b);
  // printf("%-.3d\n%-.3d",p.x,p.y);

  if(b&LEFT_BUTTON && b&RIGHT_BUTTON)
  {clrscr();
   continue;}

   if(b&LEFT_BUTTON){
   gotoxy(p.x/8+1,p.y/8+1);
   putch('*');
   ShowMouse();
   }
   if(b&RIGHT_BUTTON){
   gotoxy(p.x/8+1,p.y/8+1);
   putch(' ');
   ShowMouse();
   }
 }
HideMouse();
return 0;
}