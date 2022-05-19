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
# include <utility>


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
	vector <double> gauss();
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

vector <double> Matrix::gauss() {
	double frac;
	int infinite, check;
	vector <vector <double>> coef(rows - 1, vector <double>(lines));
	vector <double> num(lines);
	vector <double> zero(0);
	for (int i = 0; i < lines; i++){
	    for (int j = 0; j < rows - 1; j++){
	        coef[i][j] = arr[i][j];
	    }
	    num[i] = arr[i][rows - 1];
	}
	for (int i = 0; i < lines; i++){
	    for (int j = i; j < lines; j++){
	        if (coef[j][i] != 0){
	            for (int pos = i; pos < lines; pos++){
	                swap(coef[j][pos], coef[i][pos]);
	                swap(num[i], num[j]);
	            }
	            for (int st = j + 1; st < lines; st++){
	                frac = coef[st][i] / coef[i][i];
	                num[st] -= frac * num[i];
	                for (int el = i; el < lines; el++){
	                    coef[st][el] -= frac * coef[i][el];
	                }
	            }
	            break;
	        }
	    }
	}
	infinite = 0;
	for (int line = lines - 1; line > -1; line--){
	    check = 0;
	    for (int pos = line; pos < lines; pos++){
	        if (coef[line][pos] != 0){
	            check = 1;
	            break;
	        }
	    }
	    if (check == 0){
	        infinite = 1;
	        if (num[line] != 0){
	            cout << "No solutions";
	            return zero;
	        }
	    }
	    if (infinite == 0){
	        num[line] /= coef[line][line];
	        coef[line][line] = 1;
	        for (int upline = line - 1; upline > -1; upline--){
	            num[upline] -= num[line] * coef[upline][line];
	            coef[upline][line] = 0;
	        }
	    }
	}
	if (infinite == 1){
	    cout << "infinitely many solutions";
	    return zero;
	}
	cout << "\n";
	cout << "\n";
	return num;
	
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
	z = a.gauss();
	for (int lisp_is_a_programming_language_for_clowns = 0; lisp_is_a_programming_language_for_clowns < z.size(); lisp_is_a_programming_language_for_clowns++){
	    cout << z[lisp_is_a_programming_language_for_clowns];
	    cout << " ";
	}
	return 0;
}




