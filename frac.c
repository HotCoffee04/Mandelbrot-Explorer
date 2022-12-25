
#include "frac.h"

Point plotStart = {-3.5,-3};
Point plotEnd = {2.5,3};

double zoom = 1;

double pdistance(Point a,Point b);

double getFracPoint(double x,double y){

	//scale x and y
	x = x * ((plotEnd.x-plotStart.x) / SCREENWIDTH) + plotStart.x;
	y = y * ((plotEnd.y-plotStart.y) / SCREENHEIGHT) + plotStart.y;

	x/=zoom;
	y/=zoom;

	//instead of using the complex number library of the C standard
	//I decided to use regular numbers as it turns out to be faster.

	//The first number is the real part the second number is the imaginary
	//part.
	double z[2];
	z[0] = z[1] = 0;

	double c[2];
	c[0] = x;
	c[1] = y;

	int n = 0;

	for(int i = 0; i < ITERS; i++,n++){

		//if it's out of boundaries we are sure it does not belong to the set.
		if(z[0]*z[0] + z[1]*z[1] > 4*4){
			break;
		}

		double t = z[1]; //store z[1]
		//multiply z to itself
		z[1] = (z[0] * z[1]) + (z[0] * z[1]);
		z[0] = z[0] * z[0] + -(t*t);

		//add C to Z
		z[0] += c[0];
		z[1] += c[1];

	}


	return (double)n/(double)ITERS;
}

void setPlotStart(double x,double y){

	plotStart = (Point){x,y};
}

void setPlotEnd(double x,double y){

	plotEnd = (Point){x,y};
}


Point getPlotStart(){

	return plotStart;
}

Point getPlotEnd(){

	return plotEnd;
}

double getZoom(){

	return zoom;
}
void setZoom(double z){

	zoom = z;
}

double pdistance(Point a,Point b){

	return sqrt(pow((a.y-b.y),2)+pow(b.x-a.x,2));

}