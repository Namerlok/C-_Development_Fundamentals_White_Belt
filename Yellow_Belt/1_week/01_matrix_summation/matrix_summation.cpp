#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix () {
		max_rows = 0;
		max_cols = 0;
	}
	Matrix(int num_rows, int num_columns) {
		Reset(num_rows, num_columns);
	}
	void Reset(int new_rows, int new_cols){
		if (new_rows < 0)
			throw out_of_range("num_rows must be >= 0");
		if (new_cols < 0)
			throw out_of_range("num_columns must be >= 0");
		if (new_rows == 0 || new_cols == 0)
			new_rows = new_cols = 0;

		max_rows = new_rows;
		max_cols = new_cols;
		matrix.assign(new_rows, vector<int>(new_cols));
	}
	int At(int num_rows, int num_cols) const {
//		if (num_rows >= max_rows || num_cols >= max_cols || num_rows < 0 || num_cols < 0)
//			throw out_of_range("Out of range");
//		return matrix[num_rows][num_cols];
		return matrix.at(num_rows).at(num_cols);
	}
	int &At(int num_rows, int num_cols) {
//		if (num_rows >= max_rows || num_cols >= max_cols || num_rows < 0 || num_cols < 0)
//			throw out_of_range("Out of range");
//		return matrix[num_rows][num_cols];
		return matrix.at(num_rows).at(num_cols);
	}
	int GetNumRows() const {
		return max_rows;
	}
	int GetNumColumns() const {
		return max_cols;
	}
private:
	int max_rows;
	int max_cols;
	vector<vector<int>> matrix;
};

Matrix operator+ (const Matrix& matrix1, const Matrix& matrix2) {
	if (matrix1.GetNumRows() != matrix2.GetNumRows()) {
		throw invalid_argument("Mismatched number of rows");
	}

	if (matrix1.GetNumColumns() != matrix2.GetNumColumns()) {
		throw invalid_argument("Mismatched number of columns");
	}

	Matrix summ(matrix1.GetNumRows(), matrix1.GetNumColumns());
	for (int row = 0; row < matrix1.GetNumRows(); row++)
		for (int column = 0; column < matrix1.GetNumColumns(); column++)
			summ.At(row, column) = matrix1.At(row, column) + matrix2.At(row, column);

	return summ;
}

bool operator == (const Matrix& matrix1, const Matrix& matrix2) {
	if (matrix1.GetNumRows() != matrix2.GetNumRows() || matrix1.GetNumColumns() != matrix2.GetNumColumns())
		return false;
	for (int i = 0; i < matrix1.GetNumColumns(); i++)
		for (int j = 0; j < matrix1.GetNumRows(); j++)
			if (matrix1.At(j, i) != matrix2.At(j, i))
				return false;
	return true;
}

istream& operator >> (istream& in, Matrix& matrix) {
	int num_rows = 0, num_cols = 0;

	in >> num_rows >> num_cols;
	matrix.Reset(num_rows, num_cols);
	for (int row = 0; row < num_rows; row++) {
		for (int column = 0; column < num_cols; column++) {
			in >> matrix.At(row, column);
		}
	}
	return in;
}

ostream& operator << (ostream& out, const Matrix& matrix) {
	out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (int row = 0; row < matrix.GetNumRows(); row++) {
		for (int column = 0; column < matrix.GetNumColumns(); column++) {
			if (column > 0)
				out << " ";
			out << matrix.At(row,column);
		}
		out << endl;
	}
	return out;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
//	cin >> one;
//	cout << one << two;
	cout << one + two << endl;
//	one.Reset(0, 0);
//	cout << one;

	return 0;
}


