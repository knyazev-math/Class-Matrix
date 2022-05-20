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
	vector <double> kramer();
	vector <double> gauss();
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


vector <double> Matrix::gauss() {
	double frac;
	int infinite, check;
	vector <vector <double>> coef(rows - 1, vector <double>(lines));
	vector <double> num(lines);
	vector <double> zero(0);
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < rows - 1; j++) {
			coef[i][j] = arr[i][j];
		}
		num[i] = arr[i][rows - 1];
	}
	for (int i = 0; i < lines; i++) {
		for (int j = i; j < lines; j++) {
			if (coef[j][i] != 0) {
				for (int pos = i; pos < lines; pos++) {
					swap(coef[j][pos], coef[i][pos]);
					swap(num[i], num[j]);
				}
				for (int st = j + 1; st < lines; st++) {
					frac = coef[st][i] / coef[i][i];
					num[st] -= frac * num[i];
					for (int el = i; el < lines; el++) {
						coef[st][el] -= frac * coef[i][el];
					}
				}
				break;
			}
		}
	}
	infinite = 0;
	for (int line = lines - 1; line > -1; line--) {
		check = 0;
		for (int pos = line; pos < lines; pos++) {
			if (coef[line][pos] != 0) {
				check = 1;
				break;
			}
		}
		if (check == 0) {
			infinite = 1;
			if (num[line] != 0) {
				cout << "No solutions";
				return zero;
			}
		}
		if (infinite == 0) {
			num[line] /= coef[line][line];
			coef[line][line] = 1;
			for (int upline = line - 1; upline > -1; upline--) {
				num[upline] -= num[line] * coef[upline][line];
				coef[upline][line] = 0;
			}
		}
	}
	if (infinite == 1) {
		cout << "infinitely many solutions";
		return zero;
	}
	cout << "\n";
	cout << "\n";
	return num;

}




vector <double> Matrix::kramer() {
	double d, d_0;
	vector <vector <int>> coef(rows - 1, vector <int>(lines));
	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < lines; j++) {
			coef[i][j] = arr[i][j];
		}
	}
	d_0 = Matrix(coef).determinant();
	if (d_0 == 0) {
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
	cout << "Hello! This program does basic operations with matrices" << endl;
	string s;
	cin >> s;
	if ((s == "m * m") || (s == "m *m") || (s == "m* m") || (s == "m*m") || (s == "m + m") || (s == "m +m") || (s == "m+ m") || (s == "m+m")) {
		cout << "Enter first matrix sides (strings, rows): " << endl;
	}
	else {
		if (s != "solve") {
			cout << "Enter matrix sides (strings, rows): " << endl;
		}
		else {
			cout << "If you want to add an equation a_1*x_1 + a_2*x_2 + ... + a_n*x_n = b_1, enter a string a_1 a_2 ... a_n b_1 \n";
			cout << "Enter the number of equations and the number of variables: " << endl;
		}
	}
	cin >> lines1 >> rows1;
	vector <vector <int>> mat1(lines1, vector <int>(rows1));
	int i, j;
	for (int i = 0; i < lines1; i++) {
		if (s != "solve") {
			cout << "Enter the " << i + 1 << " string in first matrix: " << endl;
		}
		else {
			cout << "Enter coefficients of the " << i + 1 << " equation \n";
		}
		for (int j = 0; j < rows1; j++) {
			cin >> mat1[i][j];
		}
	}
	Matrix a(mat1);

	if ((s == "m * m") || (s == "m *m") || (s == "m* m") || (s == "m*m") || (s == "m + m") || (s == "m +m") || (s == "m+ m") || (s == "m+m")) {
		cout << "Enter second matrix sides (strings, rows): " << endl;
		cin >> lines2 >> rows2;
		vector <vector <int>> mat2(lines2, vector <int>(rows2));
		for (int i = 0; i < lines2; i++) {
			cout << "Enter the " << i + 1 << " string in second matrix: " << endl;
			for (int j = 0; j < rows2; j++) {
				cin >> mat2[i][j];
			}
		}
		Matrix b(mat2);
		if ((s == "m + m") || (s == "m +m") || (s == "m+ m") || (s == "m+m")) {
			if ((lines1 == lines2) && (rows1 == rows2)) {
				cout << "Sum of two given matrices: " << endl;
				(a + b).output_mat();
				cout << endl;
			}
			else {
				cout << "Error" << endl;
			}
		}
		if ((s == "m * m") || (s == "m *m") || (s == "m* m") || (s == "m*m")) {
			if (rows1 == lines2) {
				cout << "The result of multiplication of the given two matrices is: " << endl;
				(a * b).output_mat();
				cout << endl;
			}
			else {
				cout << "Error" << endl;
			}
		}
	}
	
	if ((s == "m * n") || (s == "m *n") || (s == "m* n") || (s == "m*n")) {
		cout << "Enter a number to multiply the matrix: " << endl;
		cin >> num;
		cout << "The result of multiplication of the given number and matrix is: " << endl;
		(a * num).output_mat();
	}
	if ((s == "m ^ t") || (s == "m ^t") || (s == "m^ t") || (s == "m^t") ){
		cout << "Transponsed matrix: " << endl;
		(a.flip()).output_mat();
	}
	if (s == "det") {
		cout << "Matrix determinant: " << endl;
		cout << a.determinant();
	}
	return 0;
}
