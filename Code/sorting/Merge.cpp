#include "Merge.h"
#include <cstdlib>

// Constructor
Merge::Merge() {
}

// Perform merge sort on the given data
void Merge::sort(vector<int>& elements) {

	int* temp = new int[elements.size()];
	sort(elements, temp, (int)elements.size() - 1, 0, (int)elements.size() - 1);
	delete[] temp;
}

void Merge::sort(vector<int>& elements, int* temp, int size, int left, int right) {

	if (left < right) {
		int center = (left + right) / 2;

		// Divide and solve left partition
		sort(elements, temp, size, left, center);

		// Divide and solve right partition
		sort(elements, temp, size, center + 1, right);

		// Merge the two partitions as sorted
		merge(elements, temp, left, center + 1, right);
	}
}


// Perform a merge between two partitions, while it merges it makes
// sure that the merged list is sorted
void Merge::merge(vector<int>& elements, int* temp, int leftPos, int rightPos, int rightEnd) {

	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (elements[leftPos] <= elements[rightPos])
			temp[tmpPos++] = elements[leftPos++];
		else
			temp[tmpPos++] = elements[rightPos++];

	// Whatever data is left on the left partition, just add it up to the list
	while (leftPos <= leftEnd)
		temp[tmpPos++] = elements[leftPos++];

	while (rightPos <= rightEnd)
		temp[tmpPos++] = elements[rightPos++];

	// Put the sorted elements back to the original list as sorted
	for (int i = 0; i < numElements; i += 1, rightEnd -= 1)
		elements[rightEnd] = temp[rightEnd];
}
