#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix() {
		iCols = 0;
		iRows = 0;
	}
	Matrix(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw std::out_of_range("Negative columns or rows");
		}
		iCols = num_cols;
		iRows = num_rows;
	}

	void Reset(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw std::out_of_range("Negative columns or rows");
		}
		iCols = num_cols;
		iRows = num_rows;
	}

	int At(const int& num_row, const int& num_col) const {
		if (num_row > iRows || num_col > iCols || num_row < 0 || num_col < 0) {
			throw std::out_of_range("Out of rows or columns range");
		}
		int iRowIndx = num_row;
		int iColIndx = num_col;
		return vecMatrix[iRowIndx*iCols + iColIndx];
	}

	int& At(const int& num_row, const int& num_col) {
		if (num_row > iRows || num_col > iCols || num_row < 0 || num_col < 0) {
			throw std::out_of_range("Out of rows or columns range");
		}
		int iRowIndx = num_row;
		int iColIndx = num_col;
		return vecMatrix[iRowIndx*iCols + iColIndx];
	}

	int GetNumRows() const {
		return iRows;
	}

	int GetNumColumns() const {
		return iCols;
	}

	void SetNumRows(int num_row) {
		iRows = num_row;
	}

	void SetNumColumns(int num_col) {
		iCols = num_col;
	}

	void AddElement(int element) {
		vecMatrix.push_back(element);
	}

	int operator [](int pos) const {
		return vecMatrix[pos];
	}

	auto GetVector() const {
		return vecMatrix;
	}

private:
	std::vector<int> vecMatrix;
	int iCols, iRows;
};


bool operator == (const Matrix& leftMat, const Matrix& rightMat) {
	if (leftMat.GetNumColumns() == rightMat.GetNumColumns() &&
		leftMat.GetNumRows() == rightMat.GetNumRows() &&
		leftMat.GetVector() == rightMat.GetVector()) {
		return true;
	}
	else {
		return false;
	}
}

Matrix operator + (const Matrix& leftMat, const Matrix& rightMat) {
	Matrix resMat;
	if (leftMat.GetNumColumns() == rightMat.GetNumColumns() &&
		leftMat.GetNumRows() == rightMat.GetNumRows()) {
		int iRows = leftMat.GetNumRows();
		int iCols = leftMat.GetNumColumns();
		resMat.SetNumColumns(iCols);
		resMat.SetNumRows(iRows);
		for (int i = 0; i < iRows; ++i) {
			for (int j = 0; j < iCols; ++j) {
				resMat.AddElement(leftMat[i*iCols + j] + rightMat[i*iCols + j]);
			}
		}
		return resMat;
	}
	else {
		throw std::invalid_argument("Different matrices dimensions");
	}
}


istream& operator >> (istream& stream, Matrix& mat) {
	int iCols, iRows, iValue;
	stream >> iRows;
	mat.SetNumRows(iRows);
	stream >> iCols;
	mat.SetNumColumns(iCols);

	for (int i = 0; i < iRows; ++i) {
		for (int j = 0; j < iCols; ++j) {
			stream >> iValue;
			mat.AddElement(iValue);
		}
	}
	return stream;
}

ostream& operator << (ostream& stream, const Matrix& mat) {
	int iCols = mat.GetNumColumns(); 
	int iRows = mat.GetNumRows();
	stream << iRows
		<< " "
		<< iCols
		<< std::endl;

	for (int i = 0; i < iRows; ++i) {
		for (int j = 0; j < iCols; ++j) {
			
			stream << mat[i*iCols + j] << " ";
		}
		stream << std::endl;
	}
	return stream;
}
