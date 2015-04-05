//graphics
//An interactive mouse driven graphics mode
//mouse draw program
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2

typedef struct {int x,y;}Point;
typedef  unsigned Buttons;
unsigned mouseptr[2][16]=
	{{0xffff,0xffff,0xffff,0xffff,
	  0xffff,0xffff,0xffff,0xffff,
	  0xff7f,0xffff,0xffff,0xffff,
	  0xffff,0xffff,0xffff,0xffff},
	 {0x0000,0x0000,0x0000,0x0000,
	  0x0000,0x0000,0x0000,0x0000,
	  0x0080,0x0000,0x0000,0x0000,
	  0x0000,0x0000,0x0000,0x0000}
	  };
unsigned mouseptr2[2][16]=
	{{0xfe8f,0xfe8f,0xfe8f,0xffff,
	  0xffff,0xffff,0xffff,0xffff,
	  0xff7f,0xffff,0xffff,0xffff,
	  0xffff,0xffff,0xffff,0xffff},
	 {0x0180,0x0180,0x0180,0x0180,
	  0x0000,0x0000,0x0000,0x0000,
	  0x0000,0x0000,0x0000,0x0000,
	  0x0000,0x0000,0x0000,0x0000}
	  };
void setMousePtr()
{asm	{
	push es
	mov ax,seg mouseptr2
	mov es,ax
	mov dx,offset mouseptr2
	mov cx,8
	mov bx,8
	mov ax,0x9
	int 0x33
	pop es;
	}

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
void drawbox()
{ int co=getcolor();
setcolor(WHITE);
for(int col=0;col<16;col++)
 {setfillstyle(SOLID_FILL,col);
  bar3d(1,col*10,20,col*10+8,1,1);
 }
setcolor(co);
}
int main()
{int gdriver=DETECT,mode=2,color=WHITE;
Point pre,p;Buttons b;char init=0;
initgraph(&gdriver,&mode,"c:\\tc\\bgi");
InitMouse();
ShowMouse();
setMousePtr();
 drawbox();
 while(!kbhit())
 { getMousePos(&p);
   getButtonStatus(&b);
   if(b&LEFT_BUTTON && b&RIGHT_BUTTON)
	{HideMouse();
	cleardevice();init=0;drawbox();ShowMouse();continue;}
   if(b&RIGHT_BUTTON)
	{
	   setcolor(BLACK);
	   outtextxy(25,color*10,"<");
	   color++;
	   color%=16;
	  setcolor(WHITE);
	   outtextxy(25,color*10,"<");
	   setcolor(color);
	   delay(500);
	}
   if(b&LEFT_BUTTON)
	  {HideMouse();
	   if(!init) pre=p,init++;
	   line(pre.x,pre.y,p.x,p.y);
	   pre=p;
	   ShowMouse();
	   continue;
	   }
   init=0;
 }
HideMouse();
return 0;
}