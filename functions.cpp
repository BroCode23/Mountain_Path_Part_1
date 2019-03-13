#include <iostream>
#include <fstream>
#include <cmath>
#include "functions.h"
using namespace std;

void findMaxMin(const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int& max, int& min) {
	max = elevations[0][0];// ensures the max and min to have a real value
	min = elevations[0][0];
	for (size_t curr_row = 0; curr_row < rows; ++curr_row) {
		for (size_t curr_col = 0; curr_col < cols; ++curr_col) {
			if (elevations[curr_row][curr_col] > max) //checks if less than min or greater than max
				max = elevations[curr_row][curr_col];
			if (elevations[curr_row][curr_col] < min)
				min = elevations[curr_row][curr_col];
		}
	}
	return;
}

void loadData(int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, istream& inData) {
	for (size_t curr_row = 0; curr_row < rows; ++curr_row) {
		for (size_t curr_col = 0; curr_col < cols; ++curr_col) {
			if (inData.eof()) {
				cout << "Error: End of file reached prior to getting all the required data.";
				exit(1);
			}
			inData >> elevations[curr_row][curr_col]; //moves each value to a spot in the array
		}
	}
	return;
}

int scaleValue(int value, int max, int min) {
	int shade = lround(((value - min) / static_cast<double>((max - min))) * 255); //calculates the respective grey value
    return shade;
}

void loadGreyscale(Pixel image[MAX_ROWS][MAX_COLS], const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int max, int min) {
	for (size_t curr_row = 0; curr_row < rows; ++curr_row) {
		for (size_t curr_col = 0; curr_col < cols; ++curr_col) {
			int shade_value = scaleValue(elevations[curr_row][curr_col], max, min);
			image[curr_row][curr_col].red = shade_value;
			image[curr_row][curr_col].green = shade_value; //moves value into each array
			image[curr_row][curr_col].blue = shade_value;
		}
	}
	return;
}

void outputImage(const Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, ostream& outData) {
	outData << "P3" << endl;  //Creates the PPM file
	outData << rows << " " << cols << endl;
	outData << 255 << endl;
	for (size_t curr_row = 0; curr_row < rows; ++curr_row) {
		for (size_t curr_col = 0; curr_col < cols; ++curr_col) {
			outData << image[curr_row][curr_col].red << " " << image[curr_row][curr_col].green << " " << image[curr_row][curr_col].blue << " ";
		}
	}
	return;
}