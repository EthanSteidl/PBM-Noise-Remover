#include "ImageReducer.h"

/*
reads points from file
*/
ImageReducer::ImageReducer(string name)
{
	filename = name;
	ifstream fin;
	fin.open(name);
	fin >> type;
	fin >> width;
	fin >> height;

	int value;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fin >> value;

			if (value == 1)
			{
				//!!! points stored as x, y
				points[count] = Point(j, i);
				count += 1;
			}
			
		}
	}

}

void ImageReducer::write(string filename)
{
	ofstream fout;
	fout.open(filename);
	fout << type << endl;
	fout << width << " " << height << endl;

	for (auto it = total_solution.begin(); it != total_solution.end(); it++)
	{
		image[it->y][it->x] = 1;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fout << image[i][j] << " ";
		}
		fout << endl;
	}

	fout.close();
}

/*
Prints points used
*/
void ImageReducer::printPoints()
{
	for (int i = 0; i < count; i++)
	{
		cout << "(" << points[i].x <<  ", " << points[i].y << ")" << endl;
	}
}



/*
swaps two points
*/
void ImageReducer::swap(Point& first, Point &second)
{
	Point x = first;
	first = second;
	second = x;
}


/*
returns 1 if ccw, 0 if linear and sometimes treats linear as ccw
if the points are given in linear order
*/
int ImageReducer::ccw(Point a, Point b, Point c)
{
	//1 if ccw - if cw 0 if linar
	int sum = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);


	if (sum == 0 && (a.x > b.x && b.x > c.x))
		return -1;
	//colinear down or up
	if (sum == 0 && b.y != c.y && (a.x == b.x) && (a.x == c.x))
		return -1;

	if (sum == 0 && b.x != c.x)
		return 1;
	if (sum == 0 && b.y != c.y)
		return 1;

	return sum;

}



/*
Calculates polar angle
*/
double ImageReducer::polarAngle(Point p1, Point p2)
{
	int tempx = p2.x - p1.x;
	int tempy = p2.y - p1.y;

	double result = atan2(tempy, tempx) * 180 / 3.14159265;

	return result;

}

/*
solves for the lowest angle as comparator
*/
bool ImageReducer::comparePoints(Point p1, Point p2)
{
	double angle1 = polarAngle(start_point3, p1);
	double angle2 = polarAngle(start_point3, p2);

	if (angle2 - angle1 < 0)
		return true;
	return false;
	
}


/*
ensures points are sorted by y coordinate than x
*/
bool ImageReducer::compareNormal(Point p1, Point p2)
{

	int val = 0;
	val = p2.y - p1.y;
	if (val != 0)
	{
		if (val > 0)
			return true;
		return false;
	}
	val = p2.x - p1.x;
	if (val > 0)
		return true;
	return false;
}


/*
returns second to last point in list
*/
Point ImageReducer::next_to_top_list(list<Point>& s)
{
	Point temp = s.back();
	s.pop_back();

	Point retval = s.back();
	s.push_back(temp);
	return retval;
}

/*
returns last point in list
*/
Point ImageReducer::last(list<Point>& s)
{
	Point val = s.back();
	return val;
}

/*
Performs grahms algorithm for a set of points
*/
void ImageReducer::grahmsScan_list(list<Point> &hit_points)
{
	//clears the current list
	hit_points.clear();

	//sort points from top left to bottom right
	std::sort(&points[0], &points[count], compareNormal);

	//set start point to highest left point
	start_point3 = points[0];

	//sort points by polar angle
	std::stable_sort(&points[1], &points[count], comparePoints);


	hit_points.push_back(points[0]);
	hit_points.push_back(points[1]);
	hit_points.push_back(points[2]);

	//perform grahms algorithm
	for (int i = 3; i < count; i++)
	{

		while (ccw(next_to_top_list(hit_points), last(hit_points), points[i]) > 0)
		{
			//remove_next_to_top(hit_points);
			hit_points.pop_back();
		}

		hit_points.push_back(points[i]);
	}

}






/*
Removes a point from array preserving ordering
Point that is removed is placed at the end
*/
int ImageReducer::remove_from_points(Point p, int size)
{
	Point temp;
	bool start = false;
	for (int i = 0; i < size; i++)
	{
		if (start == true)
		{
			points[i - 1] = points[i];
		}
		if (points[i].x == p.x && points[i].y == p.y)
		{
			temp = points[i];
			start = true;
		}
	}
	if(start == false)
		return size - 1;
	points[size - 1] = temp;
	return size - 1;
}

/*
Solves for area of polygon enclosed by points
*/
double ImageReducer::polygonArea(list<Point> &p)
{
	double a = 0.0;

	//solves area for 2 vectors
	auto it_2 = p.begin();
	for (auto it = (++p.begin()); it != p.end(); it++)
	{
		a += ((it_2->x) + (it->x)) * ((it_2->y) - (it -> y));
		it_2 = it;
	}

	//include edge case point that wraps
	a += ((p.rbegin()->x) + (p.begin()->x)) * ((p.rbegin()->y) - (p.begin()->y));
	return abs(a / 2.0);
}


/*
Given a threshold as a percentage, removes points that would remove
at least that percentage from the solution
*/
void ImageReducer::calculate(double thresh)
{
	//handles case of invalid amount of points
	if (count < 4)
	{
		cout << "No pixels deleted." << endl;
		return;
	}

	//perform the scan and place points in list
	list<Point> solution_list;
	grahmsScan_list(solution_list);

	//calculate area and threshold values
	double start_area = polygonArea(solution_list);
	threshold = start_area * (thresh / 100);


	bool first_attempt = true;	//holds if this was the first pass
	bool altered = true;		//holds if there was a removed point

	//while points are removed and there are at least 3 points
	while (altered == true  && solution_list.size() > 3)
	{

		double secondary_area = 0.0;		//temp area of other polygons
		double smallest_area = start_area;	//smallest area found so far
		Point removal_point;				//point to be removed
		bool removal_point_changed = false;	//if the removal point was changed

		//for each point in current list, try removing it and if it meets threshold
		//delete the best point
		for (auto it = solution_list.begin(); it != solution_list.end(); it++)
		{
			//removes current point
			remove_from_points(*it, count);
			count -= 1;	

			//perform scan without the point
			list<Point> secondary_list;
			grahmsScan_list(secondary_list);

			//solve area of new section
			secondary_area = polygonArea(secondary_list);

			//if the area is the smallest thus far keep it and note the point removed
			if (secondary_area < smallest_area)
			{
				smallest_area = secondary_area;
				removal_point = *it;
				removal_point_changed = true;
			}

			count += 1; //put count back
		}

		//finds smallest, so threshold = area removed wich = 1 - small/large
		if (start_area-smallest_area >= threshold && (removal_point_changed == true) )
		{
			//set flags for print
			first_attempt = false;

			//set flag for continuing
			removal_point_changed = false;

			//update starting area
			start_area = smallest_area;
			
			//remove point and print out
			remove_from_points(removal_point, count);
			count -= 1;
			cout << "Delete Pixel at (" << removal_point.y << ", " << removal_point.x << ")"  << endl;

			//update solution
			grahmsScan_list(solution_list);

			altered = true;
		}
		else
		{
			if (first_attempt)
				cout << "No pixels deleted." << endl;
			altered = false;
		}
	}

	total_solution = solution_list;

}
