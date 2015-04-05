//project
//vjbox.h Copyright 2002 Vaibhav Jain..All Rigths Reserved
#include <graphics.h>
#define UP_ARROW 72
#define DN_ARROW 80
#define LF_ARROW 75
#define RT_ARROW 77
#define SPACE_BAR 32
#define ESCAPE_KEY 27
int gdriver = DETECT, gmode,maxx,maxy;
typedef struct {int x,y;} point;
typedef struct {int left,top,right,bottom;} rect;
void init()
{int errorcode;
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
if (errorcode != grOk)  /* an error occurred */
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);             /* return with error code */
}
maxx=getmaxx();maxy=getmaxy();
}