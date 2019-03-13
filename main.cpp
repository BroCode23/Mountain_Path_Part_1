#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"
using namespace std;

static int elevations[MAX_ROWS][MAX_COLS];
static Pixel image[MAX_ROWS][MAX_COLS];

int main() {
	int num_rows;
	int num_cols;
	string file_name;

	cout << "How many Rows?" << endl; 
	cin >> num_rows; 
	if (!cin.good()) { //checks if good input
		cout << "Error: Read a non-integer value." << endl;
		exit(1);
	}

	cout << "How many Columns?" << endl;
	cin >> num_cols;
	if (!cin.good()) { //checks if good input
		cout << "Error: Read a non-integer value." << endl;
		exit(1);
	}

	cout << "What is the input filename?" << endl;
	cin >> file_name;
	ifstream inputFile(file_name);
	if (!inputFile.is_open()) { //checks if the program found the file
		cout << "Error: Problem reading the file." << endl;
		exit(1);
	}
	loadData(elevations, num_rows, num_cols, inputFile); //loads values into the array

	int max;
	int min; 
	findMaxMin(elevations, num_rows, num_cols, max, min); //finds the minimum and maximum elevations
	loadGreyscale(image, elevations, num_rows, num_cols, max, min); //loads the color values into the parallel arrays

	ofstream outputFile(file_name + ".ppm");
	outputImage(image, num_rows, num_cols, outputFile); //outputs the values into the image file

	return 0;
}