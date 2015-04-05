//project
#include <calcu.h>
#include <ctype.h>
#define FILLCOL 4
char disptext[20]="0.",textpos=0;
registers r1={0,TRUE},r2={0,TRUE},mem={0,TRUE};
uint dec_pressed=FALSE;//is decimal pressed
uint reset_display=FALSE;
uint mem_err=FALSE;
uint err=FALSE;
uint sign=FALSE;
int handlextended();
double getdispnum(void);
void main()
{char keycode='a';int i=0;
 double temp;
 init();initallobjects();drawcalc();
 //sign=TRUE;err=TRUE;
 mem.cf=FALSE;
 displaynum(12.98);
 r1.value=getdispnum();
 //display(disptext);
 while(keycode!=ESCAPE_KEY)
 {


   if(kbhit())
    { keycode=getch();
      for(i=0;i<32;i++) if (keycodes[i]==keycode) break;
      if (i>=32) continue;
      if (isdigit(keycode)||(keycode=='.')) addnumtodisp(keycode);
      switch(keycode)
      {case 0: i=handlextended();break;
       case 8: delnumdisp();break;
       case's':temp=getdispnum();
	       temp*=temp;
	       displaynum(temp);break;
       case 63:drawcalc();continue;
      }
      tuk();
      if (i==-1) continue;
      setfillstyle(SOLID_FILL,FILLCOL);
      floodfill(buttons[i].x+1,buttons[i].y+1,getmaxcolor());
      delay(100);
      setfillstyle(EMPTY_FILL,7);
      floodfill(buttons[i].x+1,buttons[i].y+1,getmaxcolor());
      }


 }
//closegraph();
}
int handlextended()
{int i;
i=getch();
switch(i)
{case 67:sign=!sign;display(disptext);
	 i=7;
	 break;
 default:return -1;
}
return i;
}
int addnumtodisp(char num)
{if (reset_display)
	{textpos=0;
	dec_pressed=FALSE;
	reset_display=FALSE;
	dec_pressed=FALSE;
	strcpy(disptext,"0.");
	//display(disptext);
	//return 1;
	}
if(num=='.') {dec_pressed=TRUE;return 1;}
if (textpos>=10) return 0;
if(dec_pressed) disptext[++textpos]=num;
else  {disptext[textpos]=num;
	disptext[++textpos]='.';
       }
disptext[textpos+1]='\0';
display(disptext);
return 1;
}

double getdispnum(void)
{ double factor,num=0;int len=0;
  while(disptext[++len]!='.');
  factor=pow10(len-1);
  for(len=0;disptext[len]!='\0';len++,factor/=10)
  if (disptext[len]=='.') {factor*=10;continue;}
  else num+=(disptext[len]-48)*factor;
  if(sign) num*=-1;
  return num;
}
int delnumdisp()
{//if (strlen(disptext)<2) return 0;
if (disptext[2]=='\0')
{disptext[0]='0';
 display(disptext);
 textpos=1;
 return 1;
}
if (disptext[textpos]=='.'){
disptext[textpos]='\0';
disptext[textpos-1]='.';}
else disptext[textpos]='\0';
textpos--;
display(disptext);
return 1;
}
