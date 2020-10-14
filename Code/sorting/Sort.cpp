
#include "Sort.h"
#include <fstream>
#include <chrono>

// Constructor
Sort::Sort() {

	current_mode = "BUBBLE";
}

// Update the mode of the sort to either merge, insertion or bubble
void Sort::select(const string& mode) {

	if (mode == "MERGE" || mode == "INSERTION" || mode == "BUBBLE")
		current_mode = mode;
}

// Load data for the algorithm to use
void Sort::load(const string &filename) {

	ifstream inFile(filename);

	// Input file validation
	if (!inFile.is_open()) {
		cout << "Failed to open file: " << filename << endl;
		exit(0);
	}

	int element;
	elements.clear();

	while (inFile >> element)
		elements.push_back(element);

	inFile.close();
}

// Perform the algorithm to the loaded data
void Sort::execute() {

	elapsed_time = 0;

	// sort and record the sort time
	chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();

	if (current_mode == "MERGE")
		merge.sort(elements);
	else if (current_mode == "INSERTION")
		insertion.sort(elements);
	else if (current_mode == "BUBBLE")
		bubble.sort(elements);

	chrono::time_point<chrono::high_resolution_clock> finish = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;
	elapsed_time = elapsed.count();
}

// Display the data
void Sort::display() {

	cout << "ELEMENTS" << endl;
	cout << "--------" << endl;
	for (int i = 0; i < elements.size(); i += 1) {
		// start a newline after printing 50 elements
		if (i != 0 && i % 50 == 0)
			cout << endl;

		cout << elements[i] << " ";
	}

	cout << endl << endl;
}

// Print out the algorithm name, execution time and dataset size
void Sort::stats() {
	// cout << "STATS" << endl;
	// cout << "-----" << endl;
	cout << "Sort Mode: " << current_mode << ", Dataset Size: " << elements.size() << ", Execution Time: " << elapsed_time << "s" << endl;
}

// Write the elements to the file
void Sort::save(const string& filename) {

	ofstream outFile(filename);

	for (int i = 0; i < elements.size(); i += 1) {
		// start a newline after writing 50 elements
		if (i != 0 && i % 50 == 0)
			outFile << endl;

		outFile << elements[i] << " ";
	}

	outFile.close();
}
