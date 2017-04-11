#include "matrixHeuristics.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class hTest
{
private:
	//the test variable and tests
	matrixHeuristics M;
	//these are the results from the different heuristics
	//	these names come from the original project document
//TODO fill out these equivelences
	//	a =
	//	b =
	//  c =
	//	d =
	//	e =
	//	f = random
	//	O = optimized
	long double a, b, c, d, f, O;
	//this is so that we can hold the best, average, and worst case
	//	for the random function
	long double e[3];

public:
	//CONSTRUCTORS
	//an empty constructor
	hTest();
	//constructor that takes the number of dimensions
	hTest(int dimensions);
	//constructor that takes an array of dimensions
	hTest(vector<int> dimensions);

	//SETTERS
	//n number of random integers
	void setDimensions(int dimensions);
	//puts the array of elements into the dimensions
	void setDimensions(vector<int> dimensions);
	//asks user for the dimensions that they would like to use and sets them
	void userDimensions();
	//reads the file dimensions from a comma seperated text file
	void userFileDimensions(ifstream &ifile);

	//GETTERS
	//these return the specific value for each heuristic
	//	if the heuristics have not been run they will return -1
	long double geta();
	long double getb();
	long double getc();
	long double getd();
	long double* gete();
	long double getf();
	long double getO();;
	//returns the number of dimensions for consideration
	int numOfDimensions();
	//returns a dimension of the matrix
	int getDimension(int dimension);

	//THE REST OF THE FUNCTIONS
	//runs the random heruistic and fills out the array
	//	this heuristic relies on the fact that the optimized heuristic has been run
	void runE();
	//runs all heuristics on data
	void runH();
	//returns a pointer to the heuristic data
	//	they are returned in alphabetical order
	long double * H();
	//prints heuristic data
	void printH();
	//returns a pointer to the heuristic statistics
	//	they are returned in alphabetical order
	//prints heuristic % difference from the optimal solution
	void printHStat();
};
