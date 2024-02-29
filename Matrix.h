#pragma once
#include <string>

class Matrix {
private:
	const int matrixSize = 10;
	bool** contents;
	std::string name;
public:
	Matrix();
	Matrix(std::string);
	~Matrix();
	inline bool operator()(int, int);
	inline std::string GetName();
	inline void SetName(std::string);
};