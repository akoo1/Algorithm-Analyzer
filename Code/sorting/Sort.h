
#ifndef sort_h
#define sort_h

#include <iostream>
#include <vector>
#include <string>
#include "Algorithm.h"
#include "Merge.h"
#include "Insertion.h"
#include "Bubble.h"

using namespace std;

// An object that performs sorting algorithms => strategy pattern

// The Sort class inherits from Algorithm and overrides all its virtual functions
class Sort : public Algorithm {

public:

	// Constructor
	Sort();

	// Update the mode of the sort to either merge, insertion or bubble
	void select(const string &mode);

	// Load data for the algorithm to use
	void load(const string &filename);

	// Perform the algorithm to the loaded data
	void execute();

	// Display the data
	void display();

	// Print out the algorithm name, execution  time and record size
	void stats();

	// Write the elements to the file
	void save(const string &filename);

private:

	string current_mode;
	vector<int> elements;
	double elapsed_time;

	// Composition strategy
	Merge merge;
	Insertion insertion;
	Bubble bubble;
};

#endif
