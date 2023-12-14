#include<iostream>
#include<graphics.h>
using namespace std;

static int LEFT=1,RIGHT=2,BOTTOM=4,TOP=8,xl,yl,xh,yh;

int getcode(int x,int y)
{
 int code = 0;												//Perform Bitwise OR to get outcode
	if(y > yh) code |=TOP;
	if(y < yl) code |=BOTTOM;
	if(x < xl) code |=LEFT;
	if(x > xh) code |=RIGHT;
 return code;
}

int main()
{
 int gd= DETECT,gm;
 int x1,y1,x2,y2;

 initgraph(&gd,&gm,NULL);
 setcolor(GREEN);

 cout<<"\n\n\t\t Enter co-ordinates of window/Rectangle: \n\n\n";
 cin>>xl>>yl>>xh>>yh;

 rectangle(xl,yl,xh,yh);


 cout<<"\n\t\t Enter the endpoints of the line: \n\n";
 cin>>x1>>y1>>x2>>y2;
 
 line(x1,y1,x2,y2);

 int outcode1=getcode(x1,y1), outcode2=getcode(x2,y2);

 int accept = 0; 											//decides if line is to be drawn
 while(1)
 {
	float m =(float)(y2-y1)/(x2-x1);						//Both points inside. Accept line
	if(outcode1==0 && outcode2==0)
	{
		accept = 1;
		break;
	}														
	else if((outcode1 & outcode2)!=0)						//AND of both codes != 0.Line is outside. Reject line		
	{
		break;
	}
	else
	{
		int x,y;
		int temp;
		if(outcode1==0)										//Decide if point1 is inside, if not, calculate intersection
			temp = outcode2;
		else
			temp = outcode1;

		if(temp & TOP)										//Line clips top edge
		{
			x = x1+ (yh-y1)/m;
			y = yh;
		}
		else if(temp & BOTTOM)								//Line clips bottom edge
		{
			x = x1+ (yl-y1)/m;
			y = yl;
		}
		else if(temp & LEFT) 								//Line clips left edge
		{
			x = xl;
			y = y1+ m*(xl-x1);
		}
		else if(temp & RIGHT)								//Line clips right edge
		{
			x = xh;
			y = y1+ m*(xh-x1);
		}

		if(temp == outcode1)								//Check which point we had selected earlier as temp, and replace its co-ordinates
		{
			x1 = x;
			y1 = y;
			outcode1 = getcode(x1,y1);
		}
		else
		{
			x2 = x;
			y2 = y;
			outcode2 = getcode(x2,y2);
		}
	}
 }
setcolor(WHITE);
delay(2000);
if(accept)
line(x1,y1,x2,y2);
cout<<"After clipping:";
getch();
return 0;
closegraph();
}
