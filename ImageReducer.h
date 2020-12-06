#ifndef IMAGEREDUCER_H
#define IMAGEREDUCER_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include "Point.h"
#include <list>
#include <set>

using namespace std;

//static variable for the comparison function
static Point start_point3;

class ImageReducer
{


private:
	string filename = "";		//filename used
	double threshold = 0.0;		//threshold
	string type = "";			//file type
	int height = 0;				//height
	int width = 0;				//width
	list<Point> total_solution; //solution at the end

	int image[100][100] = { 0 };
	Point points[10000];		//points used
	int count = 0;				//amoun of points used

	void grahmsScan_list(list<Point>& s);
	void swap(Point& first, Point& second);
	void printPoints();
	static double polarAngle(Point p1, Point p2);
	int ccw(Point p1, Point p2, Point p3);
	static bool comparePoints(Point p1, Point p2);
	static bool compareNormal(Point p1, Point p2);
	Point next_to_top_list(list<Point>& s);
	Point last(list<Point>& s);
	double polygonArea(list<Point>& p);
	int remove_from_points(Point p, int size);

public:
	ImageReducer(string filename);
	void calculate(double thresh);
	void write(string name);
};


#endif IMAGEREDUCER_H