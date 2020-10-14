
#include "Bubble.h"

// Constructor
Bubble::Bubble() {
}

// Perform bubble sort on the given data
void Bubble::sort(vector<int>& elements) {
	
	for (int i = 0; i < elements.size(); i += 1) {

		bool swapHappened = false;

		for (int j = 1; j < elements.size(); j += 1) {
			
			if (elements[j - 1] > elements[j]) {
				int temp = elements[j - 1];
				elements[j - 1] = elements[j];
				elements[j] = temp;
				swapHappened = true;
			}
		}
		if (!swapHappened)
			break;
	}
}
