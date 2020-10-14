#ifndef algorithm_h
#define algorithm_h

#include <string>

using namespace std;

// An object that performs something
class Algorithm {
	
public:

	// Constructor
	Algorithm();

	// Destructor
	virtual ~Algorithm();

	// Load data for the algorithm to use
	virtual void load(const string& filename) = 0;

	// Perform the algorithm to the loaded data
	virtual void execute() = 0;

	// Print out the content of the data (solution)
	virtual void display() = 0;

	// Set the algorithm's mode
	virtual void select(const string& type) = 0;

	// Write the data to a file
	virtual void save(const string& filename) = 0;

	// Print the stats to output
	virtual void stats() = 0;
};

#endif
