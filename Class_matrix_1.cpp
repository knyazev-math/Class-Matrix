#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <string>
#include <functional>

using namespace std;

const int INF = 1000000000;

class Matrix {
	int lines, rows;
	vector <vector <int>> arr;
public:
	Matrix(vector <vector <int>>);
	Matrix operator+ (Matrix);
	Matrix operator* (int);
	Matrix operator* (Matrix);
	Matrix flip();
	int determinant();
	void output_mat();
};

Matrix::Matrix(vector <vector <int>> m) {
	arr = m;
	rows = m[0].size();
	lines = m.size();
}


Matrix Matrix::operator+(Matrix m) {
	vector <vector <int>> ans(lines, vector <int>(rows));
	if ((lines == m.lines) && (rows == m.rows)) {
		int i, j;
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < rows; j++) {
				ans[i][j] = arr[i][j] + m.arr[i][j];
			}
		}
	}
	return Matrix(ans);
}


Matrix Matrix::operator*(Matrix m) {
	vector <vector <int>> ans(lines, vector <int>(m.rows));
	if (rows == m.lines) {
		int i, j, k;
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < m.rows; j++) {
				ans[i][j] = 0;
				for (k = 0; k < rows; k++) {
					ans[i][j] += arr[i][k] * m.arr[k][j];
				}

			}

		}
	}
	return Matrix(ans);
}


Matrix Matrix::operator*(int n) {
	vector <vector <int>> ans(lines, vector <int>(rows));
	int i, j;
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < rows; j++) {
			ans[i][j] = n * arr[i][j];
		}
	}
	return Matrix(ans);
}


Matrix Matrix::flip() {
	vector <vector <int>> ans(rows, vector <int>(lines));
	int x, y;
	for (int x = 0; x < lines; x++) {
		for (int y = 0; y < rows; y++) {
			ans[y][x] = arr[x][y];
		}
	}
	return Matrix(ans);

}


int Matrix::determinant() {
	int det = 0;
	if (lines == rows) {
		if (lines == 1) {
			return arr[0][0];
		}
		vector <vector <int>> ivan(lines - 1, vector <int>(rows - 1));
		int elem, row, pos;
		for (int elem = 0; elem < rows; elem++) {
			for (int row = 0; row < rows; row++) {
				if (row != elem) {
					for (int pos = 1; pos < lines; pos++) {
						if (row < elem) {
							ivan[pos - 1][row] = arr[pos][row];
						}
						else {
							ivan[pos - 1][row - 1] = arr[pos][row];
						}
					}
				}
			}
			det += arr[0][elem] * pow(-1, elem) * (Matrix(ivan)).determinant();
		}
	}
	return det;
}

void Matrix::output_mat() {
	int i, j;
	for (int i = 0; i < lines; i++) {
		cout << "\n";
		for (int j = 0; j < rows; j++) {
			cout << arr[i][j];
			cout << " ";
		}
	}
}

int main() {
	int lines1, rows1, lines2, rows2, num;
	cout << "Enter the means of first matrix sides (strings, rows): ";
	cin >> lines1 >> rows1;
	vector <vector <int>> mat1(lines1, vector <int>(rows1));
	int i, j;
	for (int i = 0; i < lines1; i++) {
		cout << "Enter the " << i + 1 << " string in first matrix: ";
		for (int j = 0; j < rows1; j++) {
			cin >> mat1[i][j];
		}
	}
	Matrix a(mat1);

	cout << "Enter the means of second matrix sides (strings, rows): ";
	cin >> lines2 >> rows2;
	vector <vector <int>> mat2(lines2, vector <int>(rows2));
	for (int i = 0; i < lines2; i++) {
		cout << "Enter the " << i + 1 << " string in second matrix: ";
		for (int j = 0; j < rows2; j++) {
			cin >> mat2[i][j];
		}
	}
	Matrix b(mat2);

	cout << "Enter a number to multiply the matrix: ";
	cin >> num;
	if ((lines1 == lines2) && (rows1 == rows2)) {
		cout << "The result of summation of the given two matrixes: ";
		(a + b).output_mat();
	}
	if (rows1 == lines2) {
		cout << "\nThe result of multiplication of the given two matrixes is: ";
		(a * b).output_mat();
	}
	cout << "\nThe result of multiplication of the given number and matrix is: ";
	(a * num).output_mat();
	cout << "\nThe transponsed first matrix:";
	(a.flip()).output_mat();
	cout << "\nDeterminant of the first matrix: ";
	cout << a.determinant();
	system("pause");
	return 0;
}