#include"matrixHeuristics.h"

//constructors that take either
//nothing
matrixHeuristics::matrixHeuristics()
{
}


//the number of dimensions that you wish to have
// will have n-1 matrixies with random dimensions
//  must be equal or larger than 3
matrixHeuristics::matrixHeuristics(int numDimensions)
{
	if (numDimensions <= 3)
		throw std::invalid_argument("recieved invalid argument (must be larger than 3)");
	//current random dimension
	int D;

	//makes the matrixies with correctly coresponding dimensions
	for (int i = 0; i < numDimensions; i++)
	{
		random_device rd;
		mt19937 gen(rd());
		//creates uniform distribution of numbers
		uniform_int_distribution<> dist(1, INT_MAX);
		D = dist(gen);
		//rand can create zero which dosent make sense as a matrix dimension
		if (D == 0)
			D += 1;
		//add the new matrix to the end of the vector
		dimensions.push_back(D);
	}
}


//input an array of dimension values
// will have n-1 matrixies with specified dimensions
//  array must have at lesat 3 items
matrixHeuristics::matrixHeuristics(int Dimensions[])
{
	//checking for correct number of dimensions
	if (sizeof(Dimensions) <= 3)
		throw std::invalid_argument("recieved invalid argument (must have at least 3 dimensions)");

	//creating matrixies
	for (int i = 0; i < sizeof(Dimensions)-1; i++)
		dimensions.push_back(Dimensions[i]);
}



//getters && setters

//number of dimensions that you wish to have
// will make n-1 dimensions with random dimensions
//  must be at least 3
void matrixHeuristics::setDimensions(int numDimensions)
{
	if (numDimensions <= 3)
		throw std::invalid_argument("recieved invalid argument (must be larger than 3)");
	//current random dimension
	int D;
	//makes the matrixies with correctly coresponding dimensions
	for (int i = 0; i < numDimensions; i++)
	{
		random_device rd;
		mt19937 gen(rd());
		//creates uniform distribution of numbers
		uniform_int_distribution<> dist(1, INT_MAX);
		D = dist(gen);
		//add the new matrix to the end of the vector
		dimensions.push_back(D);
	}
}

//array of dimenison values
// will have n-1 matrixies with specified dimensions
// must have at least 3
void matrixHeuristics::setDimensions(vector<int> Dimensions)
{
	//checking for correct number of dimensions
	if (sizeof(Dimensions) <= 3)
		throw std::invalid_argument("recieved invalid argument (must have at least 3 dimensions)");

	//clears vector
	dimensions.clear();

	//creating matrixies
	for (int i = 0; i < Dimensions.size(); i++)
		dimensions.push_back(Dimensions[i]);
}

//reutrns the number of dimenisons under consideration
int matrixHeuristics::getNumDimensions()
{
	return dimensions.size();
}

//allows you to ask for the dimensions by index
int matrixHeuristics::getDimension(int index)
{
	return dimensions[index];
}


//heuristics
// all return the nuber of multiplications required for that heuristic
// to multiply the given matrixies

//optimal heuristic
//this is an adaptation of an implementation from
//	www.geeksforgeeks.org/dynamic-programming-set-9-matrix-chain-multiplication/
long double matrixHeuristics::optimal()
{
	//number of matrixies
	int n = dimensions.size();

	//creates dynamic array
	//holds the calculations
	//	this is what makes it dynamic programming
	vector<vector<long double>*> m;
	for (int i = 0; i < n; i++)
	{
		m.push_back(new vector<long double>);
		for (int j = 0; j < n; j++)
			(*m[i]).push_back(0);
	}

	for (int L = 2; L < n; L++)
	{
		for (int i = 1; i < n - L + 1; i++)
		{
			int j = i + L - 1;
			for (int k = i; k <= j - 1; k++)
			{
				long double dimension1 = dimensions[i - 1];
				long double dimension2 = dimensions[k];
				long double dimension3 = dimensions[j];
				long double scalerA = (*m[i])[k];
				long double scalerB = (*m[k + 1])[j];
				long double q = (dimension1*dimension2*dimension3) + scalerA + scalerB;
				if (q < (*m[i])[j] || (*m[i])[j] == 0)
					(*m[i])[j] = q;
			}
		}
	}
	return (*m[1])[n - 1];
}

//remove largest dimension first
// removes largest inner dimensions
long double matrixHeuristics::largestFirst()
{
	//used to hold the numbers from the vector
	// had to do so so that the math worked out correctly
	long double prev;
	long double curr;
	long double next;
	//copy of dimensions
	vector<int> D = dimensions;
	//number of operations for multiplication
	long double operations = 0;
	//loops until there are only 2 dimensions
	while (D.size() > 2)
	{
		//used to itterate through
		vector<int>::iterator itt = D.begin() + 1;
		//used to save the largest position/value
		vector<int>::iterator largest = itt;
		for (itt; itt < D.end() - 1; itt++)
		{
			if (*itt > *largest)
				largest = itt;
		}
		//assignes items to variables
		//	did this to make the math work
		prev = (*(largest - 1));
		curr = (*largest);
		next = (*(largest + 1));
		operations += prev * curr * next;
		D.erase(largest);
	}
	return operations;
}

//most expensive multiplication first
long double matrixHeuristics::mostExpensive()
{
	//used to hold the numbers from the vector
	// had to do so so that the math worked out correctly
	long double prev;
	long double curr;
	long double next;
	//copy of dimensions
	vector<int> D = dimensions;
	//number of operations for chain
	long double numOp = 0;

	while (D.size() > 2)
	{
		//used to iterate through
		vector<int>::iterator itt = D.begin() + 1;
		//holds the value of the largest value location
		vector<int>::iterator  largest = itt;
		//holds the number of multiplication operations for this iteration
		long double maxMult = 0;
		//temp for value of 
		long double value = 0;
		for (itt; itt < D.end() - 1; itt++)
		{
			//assignes items to variables
			//	did this to make the math work
			prev = (*(itt - 1));
			curr = (*itt);
			next = (*(itt + 1));
			value = prev * curr * next;
			if (value > maxMult)
			{
				maxMult = value;
				largest = itt;
			}
		}
		numOp += maxMult;
		D.erase(largest);
	}
	return numOp;
}

//remove smallest first
long double matrixHeuristics::smallestFirst()
{
	//used to hold the numbers from the vector
	// had to do so so that the math worked out correctly
	long double prev;
	long double curr;
	long double next;
	//copy of dimensions
	vector<int> D = dimensions;
	//number of operations for multiplication
	long double operations = 0;

	//loops until there are only 2 dimensions
	while (D.size() > 2)
	{
		//used to itterate through
		vector<int>::iterator itt = D.begin() + 1;
		//used to save the largest position/value
		vector<int>::iterator smallest = itt;
		for (itt; itt < D.end() - 1; itt++)
		{
			if (*itt < *smallest)
				smallest = itt;
		}
		//assignes items to variables
		//	did this to make the math work
		prev = (*(smallest - 1));
		curr = (*smallest);
		next = (*(smallest + 1));
		operations += prev * curr * next;
		D.erase(smallest);
	}
	return operations;
}

//least expensive multiplication first
long double matrixHeuristics::leastExpensive()
{
	//copy of dimensions
	vector<int> D = dimensions;
	//number of operations for chain
	long double numOp = 0;
	//used to point to the vector
	//	this will be the middle dimension of the most expensive operation
	vector<int>::iterator  smallest;
	//	this is used to look through the array
	vector<int>::iterator itt;
	//used to hold the numbers from the vector
	// had to do so so that the math worked out correctly
	long double prev;
	long double curr;
	long double next;

	while (D.size() > 2)
	{
		//used to iterate through
		itt = D.begin() + 1;
		//holds the value of the largest value location
		smallest = itt;
		//holds the number of multiplication operations for this iteration
		long double minMult = 0;
		for (itt; itt < D.end() - 1; itt++)
		{
			//assignes items to variables
			//	did this to make the math work
			prev = (*(itt - 1));
			curr = (*itt);
			next = (*(itt + 1));
			long double value = prev * curr * next;
			if (value < minMult || minMult == 0)
			{
				minMult = value;
				smallest = itt;
			}
		}
		numOp += minMult;
		D.erase(smallest);
	}
	return numOp;
}

//random execution
long double matrixHeuristics::randomExecution()
{
	//copy of dimensions
	vector<int> D = dimensions;
	//used to iterate through
	vector<int>::iterator itt;
	//index of location in vector
	int item;
	//number of operations
	long double operations = 0;
	//used to hold the numbers from the vector
	// had to do so so that the math worked out correctly
	long double prev;
	long double curr;
	long double next;

	//sums up the items until there are only 2 dimensions
	while (D.size() != 2)
	{
		random_device rd;
		mt19937 gen(rd());
		//creates uniform distribution of numbers
		uniform_int_distribution<> dist(1, D.size()-2);
		//calculating the random index of item
		item = dist(gen);
		//sets iterator to the appropriate item
		itt = D.begin() + item;
		//assignes items to variables
		//	did this to make the math work
		prev = (*(itt - 1));
		curr = (*itt);
		next = (*(itt + 1));
		//sums up the number of operations
		operations += prev * curr * next;
		//removes the item from the list
		D.erase(itt);
	}
	return operations;
}

//in order
long double matrixHeuristics::inOrder()
{
	//copy of dimensions
	vector<int> D = dimensions;
	//used to iterate through
	vector<int>::iterator itt = D.begin() + 1;
	//used to mark the end
	vector<int>::iterator end = D.end() - 1;
	//holds the number of operations
	long double operations = 0;
	long double prev;
	long double curr;
	long double next;

	while (itt != end)
	{
		prev = (*(itt - 1));
		curr = (*itt);
		next = (*(itt + 1));
		//adding to the number of operations
		operations += prev * curr * next;
		//deletes that item from the list
		itt = D.erase(itt);
		end = D.end() - 1;
	}
	return operations;
}