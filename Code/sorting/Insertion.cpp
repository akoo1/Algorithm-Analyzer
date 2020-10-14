#include "Insertion.h"

// Constructor
Insertion::Insertion() {
}

// Perform an insertion sort on the given data
void Insertion::sort(vector<int>& elements) {

	for (int i = 1; i < elements.size(); i += 1) {
		// Get the next data 
		int temp = elements[i];
		int j;

		for (j = i - 1; j >= 0 && temp < elements[j]; j -= 1)
			elements[j + 1] = elements[j];

		elements[j + 1] = temp;
	}
}
