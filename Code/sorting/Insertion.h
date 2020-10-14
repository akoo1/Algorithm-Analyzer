#ifndef insertion_h
#define insertion_h

#include <vector>

using namespace std;

// An object that uses insertion sort algorithm for sorting
class Insertion {

public:

	// Constructor
	Insertion();

	// Perform an insertion sort on the given data
	void sort(vector<int>& elements);
};

#endif
