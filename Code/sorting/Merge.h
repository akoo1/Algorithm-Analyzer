#ifndef merge_h
#define merge_h

#include <vector>

using namespace std;

// An object that uses merge sort algorithm for sorting
class Merge {

public:

	// Constructor
	Merge();

	// Perform merge sort on the given data
	void sort(vector<int>& elements);

private:

	// Recursively do divide and conquer each partition by 2
	// then merge each partition in sorted order
	void sort(vector<int>& elements, int* temp, int size, int left, int right);


	// Perform a merge between two partitions, while it merges it makes
	// sure that the merged list is sorted
	void merge(vector<int>& elements, int* temp, int leftPos, int rightPos, int rightEnd);
};

#endif
