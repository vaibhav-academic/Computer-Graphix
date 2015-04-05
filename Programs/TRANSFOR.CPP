//graphics
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <math.h>
#pragma warn -inl
struct Point
{float x,y;
Point(float xx,float yy):x(xx),y(yy){}
Point():x(0),y(0){}
};
struct Line
{int x1,x2,y1,y2;
};
class Transformation;

class Polygon
{ Point pts[30];
int count,fill;
public:
	Polygon()
	{count=fill=0;}

Polygon & addVertex(Point &pt)
	{pts[count++]=pt;return *this;}

Polygon & removeVertex(int index)
	{if(index<count && index>=0)
		 {for(int i=index+1;i<count;i++)
		   pts[i-1]=pts[i];
		   count--;
		 }
	return *this;
	}

Polygon & insertVertex(int index,Point pt)
	{if(index>=count || index<0) return *this;
	 for(int i=count;i>index;i--)
		   pts[i+1]=pts[i];
	 count++;
	 pts[i]=pt;
	 return *this;
	}

Polygon & applyTransformation(Transformation & t)
	{for(int i=0;i<count;i++)
	  pts[i]=t.TransformPt(pts[i]);
	return *this;
	}

Polygon Transform(Transformation & t)
	{Polygon p2(*this);
	p2.applyTransformation(t);
	 return p2;
	}

void setFill(int i)
	{fill=i;}

void Draw()
	{if(count==0) return;
	 int arr[60];
	 for(int i=0;i<count;i++)
		 {arr[2*i]=pts[i].x,arr[2*i+1]=pts[i].y;}
	 if(!fill)
	   {drawpoly(count,arr);
	    line(pts[0].x,pts[0].y,pts[count-1].x,pts[count-1].y);
	   }
	   else
	   fillpoly(count,arr);
	 }

};

class Transformation
{ float matrix[3][3];
  static void matmult(float (*arr)[3],const float (*arr2)[3])
	{ float tarr[3]={0};
	  for(int i=0;i<3;i++)
	  {for(int j=0;j<3;j++)
	     {tarr[j]= arr[i][0]*arr2[0][j];
	      tarr[j]+=arr[i][1]*arr2[1][j];
	      tarr[j]+=arr[i][2]*arr2[2][j];
	     }
	   arr[i][0]=tarr[0];
	   arr[i][1]=tarr[1];
	   arr[i][2]=tarr[2];
	  }
	}
  public:
	Transformation()
	{matrix[0][0]=1;matrix[0][1]=0;matrix[0][2]=0;
	 matrix[1][0]=0;matrix[1][1]=1;matrix[1][2]=0;
	 matrix[2][0]=0;matrix[2][1]=0;matrix[2][2]=1;
	}

	void Reset()
	{matrix[0][0]=1;matrix[0][1]=0;matrix[0][2]=0;
	 matrix[1][0]=0;matrix[1][1]=1;matrix[1][2]=0;
	 matrix[2][0]=0;matrix[2][1]=0;matrix[2][2]=1;
	}

	Point TransformPt(const Point & pt)
	{float arr[3];
	 for(int i=0;i<3;i++)
	      {arr[i]=pt.x*matrix[0][i];
	       arr[i]+=pt.y*matrix[1][i];
	       arr[i]+=1*matrix[2][i];
	      }
	 arr[0]/=arr[2];
	 arr[1]/=arr[2];
	 return Point(arr[0],arr[1]);
	}

       void Translate(int dx,int dy) // sets transformation to translations
	{ Reset();
	  matrix[2][0]=dx;
	  matrix[2][1]=dy;
	}

	void Scale(float sx,float sy)// sets transformation to scaling
	{  Reset();
	   matrix[0][0]=sx;
	   matrix[1][1]=sy;
	}

	void Rotate(float rad)// sets transformation to rotation
	{ Reset();
	 matrix[0][0]=cos(rad);matrix[0][1]=sin(rad);
	 matrix[1][0]=-matrix[0][1];matrix[1][1]=matrix[0][0];
	}

	void addTranslation(int dx,int dy) //add given translation to currunt
	{ Reset();
	  matrix[2][0]+=dx;
	  matrix[2][1]+=dy;
	}

	void addScaling(float sx,float sy)//add given scale factor to currunt
	{  matrix[0][0]*=sx;
	   matrix[1][1]*=sy;
	}

	void addRotation(float rad)//adds given rotation angle to currunt
	{float tarr[3][3]={0};
	 tarr[0][0]=cos(rad);tarr[0][1]=sin(rad);
	 tarr[1][0]=-tarr[0][1];tarr[1][1]=tarr[0][0];
	 tarr[2][2]=1;
	 matmult(matrix,tarr);
	}

	void addReflection(int x,int y)
	{if(x) matrix[1][1]*=-1;
	 if(y) matrix[0][0]*=-1;
	}

	void Reflect(int x,int y)
	{Reset();
	 if(x) matrix[1][1]=-1;
	 if(y) matrix[0][0]=-1;
	}

	Transformation & Compose(Transformation & t)
	{matmult(matrix,t.matrix);
	return *this;
	}
};

void init()
{int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc\\bgi");
}

void main()
{ init();
  Transformation t1,t2,t3,t4,T;
  Polygon py;
  t1.Rotate(M_PI_2);
  t2.Scale(1.5,1.5);
  t3.Reflect(1,0);//reflect with respect to x-axis
  t4.Translate(getmaxx()/2,getmaxy()/1.1);

  T.Compose(t1).Compose(t2).Compose(t3).Compose(t4);

  randomize();
  for(int i=0;i<6;i++)
	 py.addVertex(Point(random(320),random(240)));

  py.Draw();
   getch();
  cleardevice();

   py.applyTransformation(T);
   py.Draw();
   getch();
}