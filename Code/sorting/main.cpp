#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <ctime>
#include "Algorithm.h"
#include "Sort.h"

using namespace std;

int main() {

	// Create 3 Sort objects and call the select method to select a mode for each 
	Sort* bubble_sort = new Sort();
	bubble_sort->select("BUBBLE");

	Sort* insertion_sort = new Sort();
	insertion_sort->select("INSERTION");

	Sort* merge_sort = new Sort();
	merge_sort->select("MERGE");

	vector<Algorithm *> sorting_algorithms;

	sorting_algorithms.push_back(bubble_sort);
	sorting_algorithms.push_back(insertion_sort);
	sorting_algorithms.push_back(merge_sort);


	string input_file_names[] = { 
		// Size 10
		"random-10.txt", 
		"reverse_sorted-10.txt",
		"20%__unique-10.txt",
		"30%__random-10.txt",

		// Size 1000
		"random-1000.txt", 
		"reverse_sorted-1000.txt",
		"20%__unique-1000.txt",
		"30%__random-1000.txt",

		// Size 10000
		"random-10000.txt", 
		"reverse_sorted-10000.txt",
		"20%__unique-10000.txt",
		"30%__random-10000.txt",

		// Size 100000
		"random-100000.txt", 
		"reverse_sorted-100000.txt",
		"20%__unique-100000.txt",
		"30%__random-100000.txt"
	};

	string output_file_names[] = {
		// Size 10
		"out_random-10.txt", 
		"out_reverse_sorted-10.txt",
		"out_20%__unique-10.txt",
		"out_30%__random-10.txt",

		// Size 1000
		"out_random-1000.txt", 
		"out_reverse_sorted-1000.txt",
		"out_20%__unique-1000.txt",
		"out_30%__random-1000.txt",

		// Size 10000
		"out_random-10000.txt", 
		"out_reverse_sorted-10000.txt",
		"out_20%__unique-10000.txt",
		"out_30%__random-10000.txt",

		// Size 100000
		"out_random-100000.txt", 
		"out_reverse_sorted-100000.txt",
		"out_20%__unique-100000.txt",
		"out_30%__random-100000.txt"
	};

	string sort_names[] = { "bubble", "insertion", "merge" };

	cout << endl;
	// Sort the results
	for (int i = 0; i < sorting_algorithms.size(); i += 1) {
		// For each of the 3 Sort objects, it will go through 16 datasets
		for (int j = 0; j < 16; j += 1) {
			sorting_algorithms[i]->load("../../Data/sorting_data/" + input_file_names[j]);
			sorting_algorithms[i]->execute();
			sorting_algorithms[i]->stats();
			cout << "Input dataset filename: " << input_file_names[j] << endl << endl;
			// There will be a total of 48 solutions
			sorting_algorithms[i]->save("../../Data/sorting_outputs/" + sort_names[i] + "_" + output_file_names[j]);
		}
	}

	// Delete the 3 sort objects on the heap 
	for (int i = 0; i < sorting_algorithms.size(); i += 1) {
		delete sorting_algorithms[i];
	}

	return 0;
}

