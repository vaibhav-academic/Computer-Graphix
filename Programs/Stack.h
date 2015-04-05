#ifndef STACK.CPP_DEFINED_1123_234
#define STACK.CPP_DEFINED_1123_234
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

template<class T> class Stack
{int top;
 T * data;
 int size;
public:
	Stack(int size=10)
		{data=new T[size];
		top=0;this->size=size;
		}

	Stack & push(T i)
	{if(top>=size)
		{fprintf(stderr,"Stack Overflow");exit(1);}
	 data[top]=i;
	 top++;
	 return *this;
	}

	T pop()
	{if(!top) {fprintf(stderr,"Stack Underflow");exit(1);}
	 top--;
	 return data[top];
	}

	~Stack(void) {delete [] data;}

	int isempty(){return top;}

	int isfull() {return top==size;}
};/**/
#endif
