//#ifndef matrixHeuristics.h
//#define matrixHeuristics.h

#include <random>
#include <vector>
#include <iterator>

using namespace std;

//allows the containment/abstraction of matrix
// chain heuristics inorder to study their effects
// on the efficiency of their execution paths
//
//impliments 7 different matrix chain algorithms
// does not actually multiply matrixies
class matrixHeuristics
{
private:
	vector<int> dimensions;

public:
	//constructors that take either
	//nothing
	matrixHeuristics();
	//the number of dimensions that you wish to have
	// will have n-1 matrixies with random dimensions
	//  must be equal or larger than 3
	matrixHeuristics(int dimensions);
	//input an array of dimension values
	// will have n-1 matrixies with specified dimensions
	//  must be equal or larger than 3
	matrixHeuristics(int dimensions[]);


	//getters && setters

	//number of dimensions that you wish to have
	// will make n-1 dimensions with random dimensions
	//  must be equal or larger than 3
	void setDimensions(int dimensions);
	//array of dimenison values
	// will have n-1 matrixies with specified dimensions
	//  must be equal or larger than 3
	void setDimensions(vector<int> dimensions);
	//reutrns the number of dimenisons under consideration
	int getNumDimensions();
	//allows you to ask for the dimensions by index
	int getDimension(int index);


	//heuristics
	// all return the nuber of multiplications required for that heuristic
	// to multiply the given matrixies

	//optimal heuristic
	//	this is heuristic O in document
	long double optimal();
	//remove largest first
	//	this is heuristic a in document
	long double largestFirst();
	//most expensive multiplication first
	//	this is heuristic b in document
	long double mostExpensive();
	//remove smallest first
	//	this is heuristic c in document
	long double smallestFirst();
	//least expensive multiplication first
	//	this is heuristic d in document
	long double leastExpensive();
	//random execution
	//	this is heuristic e in document
	long double randomExecution();
	//in order
	//	this is heuristic f in documnet
	long double inOrder();
};

