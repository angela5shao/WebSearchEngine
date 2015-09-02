/* Problem 5 */
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream input(argv[1]);
	if(input.fail()) {
		cout << "Cannot find file" << endl;
		return 1;
	}

	// Create grid dynamically and input values
	int row;
	input >> row;
	cout << "row:" << row << endl;

	double** grid = new double*[row]; // Create 2D int array (an array of pointers to arrays)
	int* lens = new int[row]; // array storing length of each row

	cout << "lens:";
	for (int i=0; i<row; i++) {
		input >> lens[i];
		cout << lens[i] << " ";
		grid[i] = new double[lens[i]]; // Create array of length of the row
	}
	cout << endl;

	// input values (test: print them by rows)
	for (int i=0; i<row; i++) {
		for (int j=0; j<lens[i]; j++) {
			input >> grid[i][j];
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// for each value
	for (int i=0; i<row; i++) {
		for (int j=0; j<lens[i]; j++) {
			int lenSeq = 1;
			// find sequence up
			if (i>=0 && i<row && j>=0 && j<lens[i]) { // if within bounds
				// check if value above is greater
				if (grid[i+1][j] > grid[i][j]) {
					lenSeq++;
				}
			}
			// find sequence down
			if (i>=0 && i<row && j>=0 && j<lens[i]) { 
				if (grid[i-1][j] > grid[i][j]) {
					lenSeq++;
				}
			}
			// find sequence left
			if (i>=0 && i<row && j>=0 && j<lens[i]) { 
				if (grid[i][j-1] > grid[i][j]) {
					lenSeq++;
				}
			}
			// find sequence right
			if (i>=0 && i<row && j>=0 && j<lens[i]) {
				cout << "checking for box to right" << endl;
				if (grid[i][j+1] > grid[i][j]) {
					lenSeq++;
				}
			}
			cout << "grid["<<i<<"]["<<j<<"]" << endl;
		}

	}

	// delete
	delete[] lens;
	for (int y=0; y<row; y++) {
		delete[] grid[y];
	}
	delete[] grid;

	return 0;
}
