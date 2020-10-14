
#ifndef bubble_h
#define bubble_h

#include <vector>

using namespace std;

// An object that uses bubble sort algorithm for sorting
class Bubble {

public:

	// Constructor
	Bubble();

	// Perform bubble sort on the given data
	void sort(vector<int>& elements);
};

#endif
