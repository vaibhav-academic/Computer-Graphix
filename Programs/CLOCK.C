//project
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>
#define RAD M_PI/180
// length of one second
#define DELAY 1500
// Hand Radiis change at will
#define RSEC 100
#define RMIN 70
#define RHRS 50
// numbers to be shown try changing to I,II,III,IV,...
char* nums[]={"1","2","3","4","5","6","7","8","9","10","11","12"};
//char* nums[]={"I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII"};
//char* nums[]={"A","B","C","D","E","F","G","I","J","K","L","M"};
int midx,midy;
void synchronize(int *,int *,int*);
void drawclock(){
int i;float j;
for(i=20;i<=70;i++) circle(midx,midy,RSEC+i);
settextjustify(1, 1);
settextstyle(1,HORIZ_DIR,4);
for(i=1;i<=12;i++)
{j=(i*30-90)*RAD;
outtextxy(midx+RSEC*cos(j),midy+RSEC*sin(j),nums[i-1]);
}
}
void settime2( int hrs,int min, int sec)
{static float h,m,s;
setcolor(0);setlinestyle(1,1,0);
line(midx,midy,midx+RSEC*cos(s),midy+RSEC*sin(s));setlinestyle(0,1,2);
line(midx,midy,midx+RMIN*cos(m),midy+RMIN*sin(m));setlinestyle(0,1,3);
line(midx,midy,midx+RHRS*cos(h),midy+RHRS*sin(h));
h= (float)(hrs+(float)min/60+(float)sec/3600)*30-90;
m= (float)(min+(float)sec/60)*6-90;
s= (float)sec*6-90;
h*=RAD;m*=RAD;s*=RAD;
setcolor(getmaxcolor());setlinestyle(1,1,0);
line(midx,midy,midx+RSEC*cos(s),midy+RSEC*sin(s));setlinestyle(0,1,2);
line(midx,midy,midx+RMIN*cos(m),midy+RMIN*sin(m));setlinestyle(0,1,3);
line(midx,midy,midx+RHRS*cos(h),midy+RHRS*sin(h));
}
void main()
{int gdriver = DETECT, gmode, errorcode,s=0,h=0,m=0;
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
if (errorcode != grOk){printf("Graphics error: %s\n", grapherrormsg(errorcode));   printf("Press any key to halt:");   getch();   exit(1); }
midx=getmaxx()/2;midy=getmaxy()/2;
drawclock();
synchronize(&h,&m,&s);
while(!kbhit())
{
s++;if(s>59) { s=0;m++;}
if(m>59) {m=0;h++;}
if(h>12) h=1;
settime2(h,m,s);
sound(50);
delay(10);
nosound();
delay(DELAY-20);
}
getch();
closegraph();
restorecrtmode();
}
void synchronize(int * h,int *m,int *s)
{struct time t;
gettime(&t);
*s=t.ti_sec;
*h=t.ti_hour;
*m=t.ti_min;
}


