#include "hTest.h"

//CONSTRUCTORS
//an empty constructor
hTest::hTest()
{
	a, b, c, d, e, f, O = -1;
}
//constructor that takes the number of dimensions
hTest::hTest(int dimensions)
{
	M.setDimensions(dimensions);
	a, b, c, d, e, f, O = -1;
}
//constructor that takes an array of dimensions
hTest::hTest(vector<int> dimensions)
{
	M.setDimensions(dimensions);
	a, b, c, d, e, f, O = -1;
}

//SETTERS
//n number of random integers
void hTest::setDimensions(int dimensions)
{
	M.setDimensions(dimensions);
}
//puts the array of elements into the dimensions
void hTest::setDimensions(vector<int> dimensions)
{
	M.setDimensions(dimensions);
}

//asks user for the dimensions that they would like to use and sets them
void hTest::userDimensions()
{
	vector<int> dimensions;
	string response = "";
	int numD = 0;
	int dimension;
	cout << "Exit at any time with E\n" << "\t this will create dimensions\n\n";
	cout << "In other words continue to add numbers that represent the dimensions untill you are done then enter E\n";
	cout << "Dimensions are inserted in the order you enter them\n";
	while (response != "E")
	{
		cout << "Enter Dimension " << numD << ": ";
		cin >> response;
		if (response == "E" && numD >= 3)
		{
			cout << "You have entered " << numD << " dimensions... Resulting in " << numD - 1 << " matrixies";
			M.setDimensions(dimensions);
		}
		else if (dimension = atoi(response.c_str()))
		{
			dimensions.push_back(dimension);
			numD += 1;
		}
		else
		{
			cout << "Please enter an integer or 'E' and make sure that you have entered at least 3 integers\n";
			response = "";
		}
	}

}
//reads the file dimensions from a comma seperated text file
void hTest::userFileDimensions(ifstream &ifile)
{
	//holds output from file
	string dimensionS;
	//actual dimension number
	int dimension;
	//holds all of the dimensions from the file
	vector<int> dimensions;
	while (getline(ifile, dimensionS, ','))
	{
		if (dimension = atoi(dimensionS.c_str()))
		{
			dimensions.push_back(dimension);
		}
		else
			cout << "file error\n" << "Make sure your file is a comma seperated text file\n";
	}
	M.setDimensions(dimensions);
}

//GETTERS
//these return the specific value for each heuristic
//	if the heuristics have not been run they will return -1
long double hTest::geta()
{
	return a;
}
long double hTest::getb()
{
	return b;
}
long double hTest::getc()
{
	return c;
}
long double hTest::getd()
{
	return d;
}
long double* hTest::gete()
{
	long double * E = new long double[3];
	E = e;
	return E;
}
long double hTest::getf()
{
	return f;
}
long double hTest::getO()
{
	return O;
}
//returns the number of dimensions for consideration
int hTest::numOfDimensions()
{
	return M.getNumDimensions();
}
//returns an int array pointer to the dimensions
int hTest::getDimension(int dimension)
{
	return M.getDimension(dimension);
}

//THE REST OF THE FUNCTIONS
//runs the random heruistic and fills out the statistic array
void hTest::runE()
{
	long double tempH;
	//keeps track of number or times loop has run inorder to limit it
	int runtimes = 0;
	//maximum times that the loop will run
	int runCap = 2 * M.getNumDimensions();
	//target min for heuristic
	long double target = 1.1 * O;

	do
	{
		tempH = M.randomExecution();
		//assigns the smallest execution tree size
		if (tempH < e[0] || e[0] == 0)
			e[0] = tempH;
		//assigns the largest execution tree size
		if (tempH > e[2])
			e[2] = tempH;
		//assigns the average case
		//	this gets us out of our initial condition
		if (e[1] == 0)
			e[1] = tempH;
		//	calculates the average
		else
			e[1] = (e[1] + tempH) / 2;
		//allows us to exit the loop when enough tests have been run
		runtimes += 1;
	  //conditions allow this loop to collect enough samples to be somewhat statistically significant
	} while (runtimes < runCap);
}
//runs all heuristics on data
void hTest::runH()
{

	a = M.largestFirst();

	b = M.mostExpensive();

	c = M.smallestFirst();

	d = M.leastExpensive();

	O = M.optimal();

	//uses O so O must be run first
	//	time is kept internally for each execution
	runE();

	f = M.inOrder();

}
//returns a pointer to the heuristic data
//	they are returned in alphabetical order
long double * hTest::H()
{
	long double * data = new long double[8];
	
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	data[4] = e[0];
	data[5] = e[1];
	data[6] = e[2];
	data[7] = f;
	data[8] = O;

	return data;
}
//prints heuristic data
void hTest::printH()
{
	printf("Largest First %lu\nMost Expensive %lu\nSmallest First %lu\nLeast Expensive %lu\nRandom Best Case %lu\nRandom Avg. Case%lu\nRandom Wrost Case%lu\nIn Order %lu\nOptimized %lu\n", a, b, c, d, e[0], e[1], e[2], f, O );
}
//returns a pointer to the heuristic statistics
//	they are returned in alphabetical order
//prints heuristic % difference from the optimal solution
void hTest::printHStat()
{
	printf("Largest First %lu\nMost Expensive %lu\nSmallest First %lu\nLeast Expensive %lu\nRandom Best Case %lu\nRandom Avg. Case%lu\nRandom Wrost Case%lu\nIn Order %lu\nOptimized %lu\n", (a - O / O), (b - O / O), (c - O / O), (d - O / O), (e[0] - O / O), (e[1] - O / O), (e[2] - O / O), (f - O / O), (O - O / O));
}