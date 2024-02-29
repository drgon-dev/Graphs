#include "Matrix.h"
using namespace std;

Matrix::Matrix() {
	for (int i = 0; i < matrixSize; i++) {
		contents[i] = new bool[matrixSize];
		for (int j = 0; j < matrixSize; j++)
			contents[i][j] = 0;
	}
	name = "null";
}

Matrix::Matrix(string input) {
	for (int i = 0; i < matrixSize; i++) {
		contents[i] = new bool[matrixSize];
		for (int j = 0; j < matrixSize; j++)
			contents[i][j] = 0;
	}
	name = input;
}

Matrix::~Matrix(){
	delete[] contents;
}

inline bool Matrix::operator()(int string, int row){
	return contents[string][row];
}

inline string Matrix::GetName(){
	return this.name;
}

inline void Matrix::SetName(string input){
	this.name = input;
}
