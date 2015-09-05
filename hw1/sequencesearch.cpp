/* Problem 5 */
#include <iostream>
#include <fstream>
using namespace std;

int searchDown(double** grid, int i, int j, int row, int* lens) {
	// cout << grid[i][j] << " ";
	//len++;
	if (i+1 == row) return 0; // base case: reached end
	else if (i+1<row && j<lens[i+1]) { // if within bounds
		if (grid[i+1][j] > grid[i][j]) { // check if value above is greater
			//cout << grid[i+1][j] << " ";		 // print
			return 1 + searchDown(grid, i+1, j, row, lens); // call for values below
		}
		else return 0;
	}
	else {
		//cout << "len:" << len << endl;
		return 0;
	} 
}

int searchUp(double** grid, int i, int j, int row, int* lens) {
	if (i-1 < 0) return 0; // base case: reached end
	else if (i-1<row && j<lens[i-1]) { // if within bounds
		if (grid[i-1][j] > grid[i][j]) { // check if value above is greater
			//cout << grid[i-1][j] << " ";		 // print
			return 1 + searchUp(grid, i-1, j, row, lens); // call for values below
		}
		else return 0;
	}
	else {
		return 0;
	} 
}

int searchLeft(double** grid, int i, int j, int row, int* lens) {
	if (j-1 < 0) return 0; // base case: reached end
	else if (j-1 >= 0) { // if within bounds
		if (grid[i][j-1] > grid[i][j]) { // check if value above is greater
			//cout << grid[i][j-1] << " ";		 // print
			return 1 + searchLeft(grid, i, j-1, row, lens); // call for values below
		}
		else return 0;
	}
	else {
		return 0;
	} 
}

int searchRight(double** grid, int i, int j, int row, int* lens) {
	if (j+1 < 0) return 0; // base case: reached end
	else if (j+1 < lens[i]) { // if within bounds
		if (grid[i][j+1] > grid[i][j]) { // check if value above is greater
			//cout << grid[i][j+1] << " ";		 // print
			return 1 + searchRight(grid, i, j+1, row, lens); // call for values below
		}
		else return 0;
	}
	else {
		return 0;
	} 
}

int main(int argc, char* argv[]) {
	ifstream input(argv[1]);
	if(input.fail()) {
		cout << "Cannot find file" << endl;
		return 1;
	}
	ofstream output; // create output file and open it
	output.open(argv[2]);

	// Create grid dynamically and input values
	int row;
	input >> row;
	//cout << "row:" << row << endl;

	double** grid = new double*[row]; // Create 2D int array (an array of pointers to arrays)
	int* lens = new int[row]; // array storing length of each row

	// input length of each row (test: print out)
	//cout << "lens:";
	for (int i=0; i<row; i++) {
		input >> lens[i];
		//cout << lens[i] << " ";
		grid[i] = new double[lens[i]]; // Create array of length of the row
	}
	//cout << endl;

	// input values (test: print them by rows)
	for (int i=0; i<row; i++) {
		for (int j=0; j<lens[i]; j++) {
			input >> grid[i][j];
			//cout << grid[i][j] << " ";
		}
		//cout << endl;
	}
	//cout << endl;

	// declare max value
	int maxLen = 0;

	// for each value
	for (int i=0; i<row; i++) {
		for (int j=0; j<lens[i]; j++) {
			//cout << grid[i][j] << " ";

			int a[4];
			a[0] = 1+searchDown(grid, i, j, row, lens);
			a[1] = 1+searchUp(grid, i, j, row, lens);
			a[2] = 1+searchLeft(grid, i, j, row, lens);
			a[3] = 1+searchRight(grid, i, j, row, lens);
			/*
			cout << "len:" << a[0] << endl;
			cout << "len:" << a[1] << endl;
			cout << "len:" << a[2] << endl;
			cout << "len:" << a[3] << endl;

			cout << endl;*/

			for (int w=0; w<4; w++) {
				if (w[a] > maxLen) 
					maxLen = w[a];
			}
		}
	}

	//cout << "maxLength: " << maxLen << endl;

	output << maxLen << endl;
	// close output file
	output.close();

	// delete
	delete[] lens;
	for (int y=0; y<row; y++) {
		delete[] grid[y];
	}
	delete[] grid;

	return 0;
}
