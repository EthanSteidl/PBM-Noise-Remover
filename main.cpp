#include <iostream>
#include <string>
#include "ImageReducer.h"

using namespace std;

void getInput(string& filename, double& threshold);
void test1();
void test0();
void test3();
void test4();
void test_corner0();
void test_corner25();
void test_corner50();
void test_corner75();
void test_corner100();
void test_cornerB0();

void testO05();
void testJ05();
void testI05();
void testO0();
void testJ0();
void testI0();
void runTests();

int main()
{
	//runs test cases
	//runTests();
	
	string filename;
	double threshold;
	getInput(filename, threshold);
	ImageReducer Ir = ImageReducer(filename);

	//solves problem
	Ir.calculate(threshold);

	//wires out image solution to file
	Ir.write("solution_" + filename);

	return 0;
}

void runTests()
{
	cout << "test0-----" << endl;
	test0();
	cout << "test1-----" << endl;
	test1();
	cout << "test2-----" << endl;
	test3();
	cout << "test3-----" << endl;
	test4();
	cout << "corner 0 threshold-----" << endl;
	test_corner0();
	cout << "corner 25 threshold-----" << endl;
	test_corner25();
	cout << "corner 50 threshold-----" << endl;
	test_corner50();
	cout << "B with 0 threshold-----" << endl;
	test_cornerB0();
	cout << "I with 50 threshold-----" << endl;
	testI05();
	cout << "J with 50 threshold-----" << endl;
	testJ05();
	cout << "O with 50 threshold-----" << endl;
	testO05();
	cout << "I with 0 threshold-----" << endl;
	testI0();
	cout << "J with 0 threshold-----" << endl;
	testJ0();
	cout << "O with 0 threshold-----" << endl;
	testO0();
	cout << "COMPLETE" << endl;
}

void getInput(string& filename, double& threshold)
{
	cin >> filename;
	cin >> threshold;
	return;
}


void testI0()
{
	string filename1 = "test-I.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(0.0);
	y.write("solution0.0_" + filename1);
}
void testJ0()
{
	string filename1 = "test-J.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(0.0);
	y.write("solution0.0_" + filename1);
}
void testO0()
{
	string filename1 = "test-O.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(0.0);
	y.write("solution0.0_" + filename1);
}

void testI05()
{
	string filename1 = "test-I.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(5.0);
	y.write("solution5.0_" + filename1);
}
void testJ05()
{
	string filename1 = "test-J.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(5.0);
	y.write("solution5.0_" + filename1);
}
void testO05()
{
	string filename1 = "test-O.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(5.0);
	y.write("solution5.0_" + filename1);
}


void test1()
{
	string filename1 = "test-B.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(5.0);
	y.write("solution5.0_" + filename1);
}
void test0()
{
	string filename1 = "test-A.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(5.0);
	y.write("solution5.0_" + filename1);
}
void test3()
{
	string filename1 = "test-A.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(100.0);
	y.write("solution100_" + filename1);
}
void test4()
{
	string filename1 = "test-A.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(80.0);
	y.write("solution80_" + filename1);
}
void test_corner0()
{
	string filename1 = "test-corners.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(0.0);
	y.write("solution00_" + filename1);
}
void test_corner25()
{
	string filename1 = "test-corners.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(25.0);
	y.write("solution25_" + filename1);
}

void test_corner50()
{
	string filename1 = "test-corners.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(50.0);
	y.write("solution50_" + filename1);
}
void test_corner75()
{
	string filename1 = "test-corners.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(75.0);
	y.write("solution75_" + filename1);
}
void test_corner100()
{
	string filename1 = "test-corners.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(100.0);
	y.write("solution100_"+filename1);
}
void test_cornerB0()
{
	string filename1 = "test-B.pbm";
	ImageReducer y = ImageReducer(filename1);
	//y.printPoints();
	y.calculate(0.0);
	y.write("solutionB0_" + filename1);
}