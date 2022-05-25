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
	vector <vector <long double>> arr;
public:
	Matrix(vector <vector <long double>>);
	Matrix operator+ (Matrix);
	Matrix operator* (long double);
	Matrix operator* (Matrix);
	Matrix flip();
	Matrix gaussian();
	Matrix jordan();
	int determinant();
	vector <long double> kramer();
	int solve();
	void output_mat();
};

Matrix::Matrix(vector <vector <long double>> m) {
	arr = m;
	rows = m[0].size();
	lines = m.size();
}


Matrix Matrix::operator+(Matrix m) {
	vector <vector <long double>> ans(lines, vector <long double>(rows));
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
	vector <vector <long double>> ans(lines, vector <long double>(m.rows));
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


Matrix Matrix::operator*(long double n) {
	vector <vector <long double>> ans(lines, vector <long double>(rows));
	int i, j;
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < rows; j++) {
			ans[i][j] = n * arr[i][j];
		}
	}
	return Matrix(ans);
}


Matrix Matrix::flip() {
	vector <vector <long double>> ans(rows, vector <long double>(lines));
	int x, y;
	for (int x = 0; x < lines; x++) {
		for (int y = 0; y < rows; y++) {
			ans[y][x] = arr[x][y];
		}
	}
	return Matrix(ans);

}


Matrix Matrix::jordan() {
	long double b = (-1) * (arr[0][0] + arr[1][1]);
	long double c = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
	if (b * b < 8 * c) {
		cout << "Jordan form doesn't exist" << endl;
	}
	else {
		long double x1 = (sqrt(b * b - 8 * c) - b) / 2;
		long double x2 = (sqrt(b * b - 8 * c) + b) / (-2);
		vector <vector <long double>> ans(2, vector <long double>(2));
		ans[0][0] = x1;
		ans[1][1] = x2;
		if (x1 == x2) {
			ans[0][1] = 1;
		}
		return Matrix(ans);
	}

}


int Matrix::determinant() {
	int det = 0;
	if (lines == rows) {
		if (lines == 1) {
			return arr[0][0];
		}
		vector <vector <long double>> ivan(lines - 1, vector <long double>(rows - 1));
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


int Matrix::solve() {
	vector <vector <long double>> coef(lines, vector <long double>(rows - 1));
	vector <vector <long double>> ans(rows - 1, vector <long double>(rows, 0));
	vector <long double> num(lines);
	vector <bool> random(rows - 1, true);
	int pos = rows;
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < rows - 1; j++) {
			coef[i][j] = arr[i][j];
		}
		num[i] = arr[i][rows - 1];
	}
	for (int i = lines - 1; i > -1; i--) {
		bool zero = true;
		for (int j = rows - 2; j > -1; j--) {
			if (coef[i][j] != 0) {
				zero = false;
				pos = j;
			}
		}
		if (zero) {
			if (num[i] != 0) {
				cout << "No solutions" << endl;
				return 0;
			}
		}
		else {
			random[pos] = false;

			for (int s = pos + 1; s < rows - 1; s++) {
				coef[i][s] = coef[i][s] / coef[i][pos];
			}
			num[i] /= coef[i][pos];
			ans[pos][rows - 1] = num[i];
			coef[i][pos] = 1;



			for (int t = pos + 1; t < rows - 1; t++) {
				if (random[t]) {
					ans[pos][t] += (-1) * coef[i][t];
				}
				else {
					for (int d = t + 1; d < rows; d++) {
						ans[pos][d] += ((-1) * coef[i][t]) * ans[t][d];
					}
					ans[pos][t] = 0;
				}
			}
		}
	}

	for (int i = 0; i < rows - 1; i++) {
		bool zero = true;
		if (random[i]) {
			cout << "x_" << i + 1 << " is a random real number" << endl;
		}
		else {
			cout << "x_" << i + 1 << " = ";
			for (int j = 0; j < rows - 1; j++) {
				if (ans[i][j] > 0) {
					cout << "+ " << abs(ans[i][j]) << " * x_" << j + 1 << " ";
				}
				else {
					if (ans[i][j] < 0) {
						cout << "- " << abs(ans[i][j]) << " * x_" << j + 1 << " ";
					}
				}
			}
			if (ans[i][rows - 1] > 0) {
				cout << "+ " << ans[i][rows - 1] << endl;
			}
			if (ans[i][rows - 1] < 0) {
				cout << "- " << abs(ans[i][rows - 1]) << endl;
			}
		}
	}
	return 0;

}



Matrix Matrix::gaussian() {
	vector <vector <long double>> coef(lines, vector <long double>(rows));
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < rows; j++) {
			coef[i][j] = arr[i][j];
		}
	}
	int pos = 0;
	for (int i = 0; i < lines; i++){
		for (int k = pos; k < rows; k++) {
			bool found = false;
			for (int j = i; j < lines; j++) {
				if ((coef[j][k] != 0) && (not found)) {
					pos = k;
					found = true;
					for (int u = k; u < rows; u++) {
						swap(coef[i][u], coef[j][u]);
					}
				}
				if ((j != i) && (found)) {

					long double t = coef[j][pos] / coef[i][pos];
					for (int v = pos; v < rows; v++) {

						coef[j][v] -= t * coef[i][v];
					}
				}
			}
			if (found) {
				break;
			}
			
		}

	}
	return Matrix(coef);
}


vector <long double> Matrix::kramer() {
	long double d, d_0;
	vector <vector <long double>> coef(rows - 1, vector <long double>(lines));
	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < lines; j++) {
			coef[i][j] = arr[i][j];
		}
	}
	d_0 = Matrix(coef).determinant();
	if (d_0 == 0) {
		return {};
	}
	vector <long double> ans(rows - 1);
	vector <vector <long double>> help(rows - 1, vector <long double>(lines));
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
	int lines1, rows1, lines2, rows2;
	long double num;
	cout << "Hello! This program does basic operations with matrices" << endl;
	string s;
	cin >> s;
	if (s == "jordan") {
		cout << "Warning! This program calculates the jordan from only for matrices 2x2; this feature will be improved later" << endl;
	}
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
	if (s == "solve") {
		rows1 += 1;
	}
	vector <vector <long double>> mat1(lines1, vector <long double>(rows1));
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
		vector <vector <long double>> mat2(lines2, vector <long double>(rows2));
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
	if (s == "gauss") {
		cout << "Gaussian elimination: " << endl;
		(a.gaussian()).output_mat();
	}
	
	if (s == "solve") {
		cout << "Solution: " << endl;
		(a.gaussian()).solve();
	}
	if (s == "jordan") {
		cout << "Jordan form: " << endl;
		(a.jardin()).output_mat();
	}
	return 0;
}
