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
	vector <double> kramer();
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

vector <double> Matrix::kramer() {
	double d, d_0;
	vector <vector <int>> coef(rows - 1, vector <int>(lines));
	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < lines; j++){
		    coef[i][j] = arr[i][j];
		}
	}
	d_0 = Matrix(coef).determinant();
	if (d_0 == 0){
	    return {};
	}
	vector <double> ans(rows - 1);
	vector <vector <int>> help(rows - 1, vector <int>(lines));
	for (int j = 0; j < lines; j++) {
		help = coef;
		for (int i = 0; i < rows - 1; i++) {
			help[i][j] = arr[i][rows - 1];
		}
		d = Matrix(help).determinant();
		ans[j] = d / d_0;
	}
	return ans;
}

int main() {
	int lines1, rows1, lines2, rows2, num, n;
	cout << "Enter n \n";
	cin >> n;
	lines1 = n;
	rows1 = n + 1;
	vector <vector <int>> mat1(lines1, vector <int>(rows1));
	int i, j;
	cout << "If you want to add an equation a_1*x_1 + a_2*x_2 + ... + a_n*x_n = b_1, enter a string a_1 a_2 ... a_n b_1 \n";
	for (int i = 0; i < lines1; i++) {
		cout << "Enter coefficients of the " << i + 1 << " equation \n";
		for (int j = 0; j < rows1; j++) {
			cin >> mat1[i][j];
		}
	}
	Matrix a(mat1);
	vector <double> z;
	z = a.kramer();
	if (z.size() == 0){
	    cout << "Impossible to solve";
	}
	else{
	    for (int k = 0; k < lines1; k++){
	        cout << z[k];
	        cout << " ";
	    }
	}
	return 0;
}