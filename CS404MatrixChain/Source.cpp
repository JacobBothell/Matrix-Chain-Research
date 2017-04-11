//Jacob Bothell
//
//CS449 algorithms
//efficiency of different matrix chain multiplications

#include <iostream>
#include <fstream>
#include "hTest.h"

using namespace std;

void formatedoutput(ofstream& fout, long double a[3])
{

	fout << "\t\t Best Case:    " << a[0] << "\n";
	fout << "\t\t Average Case: " << a[1] << "\n";
	fout << "\t\t Worst Case:   " << a[2] << "\n";
}

void formatedstats(ofstream& fout, long double a[30])
{
	//calculate the mean and standard deviation for data run
	long double mean = 0;
	long double M2 = 0;
	long double SD = 0;
	int indexes = 30;
	long double smallest = LDBL_MAX;
	long double largest = 0;
	long double avg = 0;

	for (int i = 1; i < indexes; i++)
	{
		
		long double item = a[i-1];
		//finds the min
		if (item < smallest)
			smallest = item;
		//finds the max
		if (item > largest)
			largest = item;

		//calculates the average and SD with Welford's algorithm
		//	algorithm rewriten from online source name not given
		
		avg += item;
		long double delta = item - mean;
		mean += delta / i;
		long double delta2 = item - mean;
		M2 += delta*delta2;
	}
	avg = avg / (indexes);
	SD = sqrt(M2 / (indexes));


	fout << "\t\t Best Case:    " << smallest << "\n";
	fout << "\t\t Mean Case:    " << mean << "\n";
	fout << "\t\t Average Case: " << avg << "\n";
	fout << "\t\t Worst Case:   " << largest << "\n";
	fout << "\t\t\t Standard Deviation: " << SD << "\n";
}

void formatedstatsE(ofstream& fout, long double a[3][30])
{
	//calculate the mean and standard deviation for data run


	for (int outer = 0; outer < 3; outer++)
	{
		long double mean = 0;
		long double SD = 0;
		long double M2 = 0;
		long double avg = 0;
		int indexes = 30;
		long double smallest = LDBL_MAX;
		long double largest = 0;

		for (int i = 1; i < indexes - 1; i++)
		{
			long double item = a[outer][i-1];
			//finds the min
			if (outer == 0 && item < smallest)
				smallest = item;
			//finds the max
			if (outer == 2 && item > largest)
				largest = item;

			//calculates the average and SD with Welford's algorithm
			//	algorithm rewriten from online source name not given

			avg += item;
			long double delta = item - mean;
			mean += delta / i;
			long double delta2 = item - mean;
			M2 += delta*delta2;
		}
		avg = avg / (indexes);
		SD = sqrt(M2 / (indexes));

		if (outer == 0)
			fout << "\t\t Best Case:    " << smallest << "\n";
		if (outer == 1)
			fout << "\t\t Average Case: " << mean << "\n";
		if (outer == 2)
			fout << "\t\t Worst Case:   " << largest << "\n";
		
		fout << "\t\t\tStandard Deviation: " << SD << "\n";
	}
}

//runs the standard test
// uses random numbers and different numbers of dimenions to get stats
void standard()
{
	//number of dimensions
	int numD;
	//number of times test has been run
	int numTest;
	//these are to keep track of the best, avg., and worst case of the heuristics
	//	organization: best[0], avg.[1], worst[2]
	//long double a[3] = { 0, 0, 0 }, b[3] = { 0, 0, 0 }, c[3] = { 0, 0, 0 }, d[3] = { 0, 0, 0 }, e[3] = { 0, 0, 0 }, f[3] = { 0, 0, 0 }, O[3] = { 0, 0, 0 };

	//outputs the test results to a text file
	ofstream testR("TestResults.txt");

	//does testing for 10, 15, 20, 25 dimensions
	for (numD = 10; numD <= 30; numD += 5)
	{
		long double a[30], b[30], c[30], d[30], e[3][30], f[30], O[30];
		for (numTest = 0; numTest < 30; numTest++)
		{

			//container that does heuristics and holds the values
			hTest test(numD);

			//this runs all of the tests
			test.runH();

			//saves test conditions and organizes them
			long double heuristicOValue = test.getO();
			//for a
			a[numTest] = test.geta() / heuristicOValue;
			//for b
			b[numTest] = test.getb() / heuristicOValue;
			//for c
			c[numTest] = test.getc() / heuristicOValue;
			//for d
			d[numTest] = test.getd() / heuristicOValue;
			//for e
			long double *tempe = test.gete();
			e[0][numTest] = *tempe / heuristicOValue;
			e[1][numTest] = *(tempe + 1) / heuristicOValue;
			e[2][numTest] = *(tempe + 2) / heuristicOValue;
			//for f
			f[numTest] = test.getf() / heuristicOValue;
			//for O
			O[numTest] = test.getO();
		}
		testR << "Test Heuristic Results for " << numD << " dimensions\n";
		testR << "\t Largest Dimension First:\n";
		formatedstats(testR, a);
		testR << "\t Most Expensive First:\n";
		formatedstats(testR, b);
		testR << "\t Smallest Dimension First:\n";
		formatedstats(testR, c);
		testR << "\t Least Expensive First:\n";
		formatedstats(testR, d);
		testR << "\t Random Execution:\n";
		formatedstatsE(testR, e);
		testR << "\t InOrder:\n";
		formatedstats(testR, f);
		testR << "\t Optimized Raw Value:\n";
		formatedstats(testR, O);

		
	}
	testR.close();
}

//runs statistics on single matrix set
//	uses the passed in member as the matrix
void singleTest(hTest &test)
{
	//these are to keep track of the best, avg., and worst case of the heuristics
	//	organization: best[0], avg.[1], worst[2]
	long double e[3] = { 0, 0, 0 };

	//outputs the test results to a text file
	ofstream testR("TestResults.txt");


	//this runs all of the tests
	test.runH();
	//now to save test conditions and organizes them
	long double heuristicOValue = test.getO();
	//for e
	long double *tempe = test.gete();
	e[0] = *tempe / heuristicOValue;
	e[1] = *(tempe + 1) / heuristicOValue;
	e[2] = *(tempe + 2) / heuristicOValue;
	

	testR << "Test Heuristic Results\n";
	testR << "\t Largest Dimension First:\n";
	testR << "\t\t" << test.geta() / heuristicOValue << "\n";
	testR << "\t Most Expensive First:\n";
	testR << "\t\t" << test.getb() / heuristicOValue << "\n";
	testR << "\t Smallest Dimension First:\n";
	testR << "\t\t" << test.getc() / heuristicOValue << "\n";
	testR << "\t Least Expensive First:\n";
	testR << "\t\t" << test.getd() / heuristicOValue << "\n";
	testR << "\t Random Execution:\n";
	formatedoutput(testR, e);
	testR << "\t InOrder:\n";
	testR << "\t\t" << test.getf() / heuristicOValue << "\n";
	testR << "\t Optimized Raw Value:\n";
	testR << "\t\t" << heuristicOValue;

	testR.close();
}

//runs heuristics on single matrix set
//	uses the passed matrix member as the matrix
//runs statistics on single matrix set
//	uses the passed in member as the matrix
void singleHTest(hTest &test)
{
	//these are to keep track of the best, avg., and worst case of the heuristics
	//	organization: best[0], avg.[1], worst[2]
	long double e[3] = { 0, 0, 0 };

	//outputs the test results to a text file
	ofstream testR("TestResults.txt");


	//this runs all of the tests
	test.runH();
	//now to save test conditions and organizes them
	//for e
	long double *tempe = test.gete();
	e[0] = *tempe;
	e[1] = *(tempe + 1);
	e[2] = *(tempe + 2);


	testR << "Test Heuristic Results\n";
	testR << "\t Largest Dimension First:\n";
	testR << "\t\t" << test.geta() << "\n";
	testR << "\t Most Expensive First:\n";
	testR << "\t\t" << test.getb() << "\n";
	testR << "\t Smallest Dimension First:\n";
	testR << "\t\t" << test.getc() << "\n";
	testR << "\t Least Expensive First:\n";
	testR << "\t\t" << test.getd() << "\n";
	testR << "\t Random Execution:\n";
	formatedoutput(testR, e);
	testR << "\t InOrder:\n";
	testR << "\t\t" << test.getf() << "\n";
	testR << "\t Optimized Raw Value:\n";
	testR << "\t\t" << test.getO();

	testR.close();
}

//used for start state of the program
void welcome()
{
	string response;
	cout << "Welcome to the Matrix Heuristic Statistic Calculator\n\n";
	cout << "OPTIONS:\n" << "\tS: standard test\n" <<"\t\tputs random numbers into the dimensions and tests with 10, 15, 20, and 25 dimensions\n\t\t outputs the relative statistics into a file\n" 
		                 << "\tE: enter your own dimensions\n" << "\t\tallow for entering dimensions by console input\n\t\t outputs relative statistics to file\n" 
						 << "\tF: use a file with dimensions\n" << "\t\tallows for file i/o for dimensions\n\t\t file should be comma seperated list of numbers\n\t\t outputs relative statistics to file\n"
						 << "\tT: test heuristics\n"<< "\t\tconsole input of dimensions\n\t\t Prints the exact output of the heuristics to file\n";
	cin >> response;

	//this is for the standard test
	if (response == "S" || response == "s")
	{
		standard();
	}
	//this is the option for inputting console dimensions
	else if (response == "E" || response == "e")
	{
		hTest test;
		test.userDimensions();
		singleTest(test);
	}
	//this is the option for inputing a file
	else if (response == "F" || response == "f")
	{
		hTest test;
		ifstream ifile("./Dimensions.txt");
		//tries to open the file
		while (!(ifile.is_open()))
		{
			cout << "please put a file called Dimenisons.txt in the same direcotory as this exe file";
			cin >> response;
		}

		test.userFileDimensions(ifile);
		singleTest(test);
	}
	else if (response == "T" || response == "t")
	{
		hTest test;
		test.userDimensions();
		singleHTest(test);
	}
}

void main()
{
	welcome();
	system("pause");
}