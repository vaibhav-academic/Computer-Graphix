//project
#include <vjgraph.h>
#include <dos.h>
#include <string.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define BUTTON 40
#define HGAP  10
#define VGAP 10
#define FONTSIZE 1
#define SCRFNTSIZE 4
#define STICKY  3000
typedef unsigned char uint;
char *caption="CITIZEN CT-500";
rect calculator,screen,logo;
int screenpoly[8];
extern uint sign,err,mem_err,reset_display;
extern char disptext[];
typedef struct {double value;uint cf;} registers;
extern registers mem;
const char *captions[30]={"AC","MC","MR","M+","M-","C","->","+/-","\xFB"
			,"3\xFB","7","8","9","Sqr","\xF6","4","5","6",
			"%","X","1","2","3","1/n","-","0","00","."
			,"=","+"};
const int keycodes[32]={83,-109,109,-112,-114,99,8,32,64,35,55,56,57,
			115,47,52,53,54,37,42,49,50,51,114,45,48,
			111,46,13,43,27,0};
typedef struct{int x,y;char *caption;}button;
button buttons[31];
void drawcalc()
{int i;
 cleardevice();
 rectangle(calculator.left,calculator.top,calculator.right,calculator.bottom);
 rectangle(screen.left,screen.top,screen.right,screen.bottom);
 rectangle(logo.left,logo.top,logo.right,logo.bottom);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 settextstyle(0,0,FONTSIZE);
 for(i=0;i<30;i++)
 {rectangle(buttons[i].x,buttons[i].y,buttons[i].x+BUTTON,buttons[i].y+BUTTON);
 outtextxy(buttons[i].x+BUTTON/2,buttons[i].y+BUTTON/2,buttons[i].caption);
 }
 settextjustify(RIGHT_TEXT,CENTER_TEXT);
 settextstyle(2,0,0);
 outtextxy(logo.right-HGAP/2,logo.top+BUTTON/4,caption);
 setfillstyle(CLOSE_DOT_FILL,15);
 floodfill(calculator.left+1,calculator.top+1,getmaxcolor());

}
void initallobjects()
{void initbuttons(),capsoff();
 int cheight,cwidth;
 capsoff();
 cheight=7*(BUTTON+VGAP)+2*BUTTON+VGAP;
 cwidth=5*(BUTTON+HGAP)+HGAP;
 calculator.left=(maxx-cwidth)/2;
 calculator.top=(maxy-cheight)/2;
 calculator.right=(maxx+cwidth)/2;
 calculator.bottom=(maxy+cheight)/2;
 screen.left=calculator.left+HGAP;
 screen.top=calculator.top+VGAP;
 screen.right=calculator.right-HGAP;
 screen.bottom=calculator.top+2*BUTTON;
 logo.left=screen.left;
 logo.right=screen.right;
 logo.top=screen.bottom+VGAP;
 logo.bottom=logo.top+BUTTON/2;
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 settextstyle(0,0,FONTSIZE);
 setcolor(getmaxcolor());
 screenpoly[0]=screen.left+1; screenpoly[1]=screen.top+1;
 screenpoly[2]=screen.right-1; screenpoly[3]=screen.top+1;
 screenpoly[4]=screen.right-1; screenpoly[5]=screen.bottom-1;
 screenpoly[6]=screen.left+1; screenpoly[7]=screen.bottom-1;
 initbuttons();
}
void capsoff()
{ unsigned char far *kb;
kb=(char *)0x417;
*kb=32;
}
void initbuttons()
{int i;
   buttons[0].caption=(char *)captions[0];
   buttons[0].y=screen.bottom+VGAP+BUTTON;
   buttons[0].x=calculator.left+HGAP;
   for(i=1;i<30;i++)
    {if (i%5==0)
    {buttons[i].y=buttons[i-1].y+BUTTON+VGAP;
     buttons[i].x=buttons[0].x;
    }
    else
    {buttons[i].x=buttons[i-1].x+BUTTON+HGAP;
     buttons[i].y=buttons[i-1].y;
    }
    buttons[i].caption=(char *)captions[i];
    }
buttons[30].x=-100;
buttons[30].y=-100;
}
void tuk(void)
{ int i; for(i=100;i<=200;i+=i,sound(i));
nosound();
}
void beep(void)
{ sound(2000);
 delay(200);
 nosound();
}
int isoperator(int num)
{switch(num)
{ case 14:
  case 18:
  case 19:
  case 24:
  case 28:
  case 29:return 1;
  default:return 0;
}
}
int display(char * text)
{char texttodisp[20];
 strcpy(texttodisp,text);
 if (strlen(text)>11) strncpy(text,texttodisp,11);
 texttodisp[11]='\0';
 setfillstyle(SOLID_FILL,0);
 fillpoly(4,screenpoly);
 settextstyle(1,0,SCRFNTSIZE);
 settextjustify(RIGHT_TEXT,CENTER_TEXT);
 outtextxy(screen.right,screen.top+BUTTON,texttodisp);
 settextstyle(SMALL_FONT,0,10);
 if (sign) outtextxy(screen.left+textwidth("-")+4,
			screen.top+BUTTON*0.90,"-");
 settextstyle(SMALL_FONT,0,7);
 if (!mem.cf) outtextxy(screen.left+textwidth("M")+4,
		screen.top+BUTTON-textheight("M"),"M");
 if (err) outtextxy(screen.left+textwidth("E")+4,screen.bottom
	  -textheight("E"),"E");
 return 1;
}
int displaynum(double num)
{char buff[22];int i;
if (num<0) sign=TRUE;
if ((num>9999999999)||(num<-9999999999)) err=TRUE;
sprintf(buff,"%10.10f",num);
for(i=0;i<11;i++) disptext[i]=buff[i];
disptext[i]='\0';
display(disptext);
reset_display=TRUE;
return 1;
}
