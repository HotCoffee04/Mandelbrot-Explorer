#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "common.h"

typedef struct Point{

	double x,y;

}Point;


//plots a point of the set giving a number from 0 to 1 as the output.
double getFracPoint(double x,double y);

//set start coordinates for plotting
void setPlotStart(double x,double y);
//set end coordinates for plotting
void setPlotEnd(double x,double y);

Point getPlotStart();
Point getPlotEnd();

double getZoom();
void setZoom(double z); //set zoom
double pdistance(Point a,Point b); //calculate distance between two points