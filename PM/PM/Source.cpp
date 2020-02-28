#include<iostream>
#include<vector>
using namespace std;
void PM(int n, vector<vector<double>> a, vector<double> y0, vector<double> lam1, double eps, double delta) {
	vector<double> x0(n);
	vector<double> x0prev(n);
	vector<double> lam0(n);
	int tick = 0;
	int counter = 0;
	double normay0 = 0;
	for (double& i : y0)
		normay0 += pow(i, 2);
	normay0 = sqrt(normay0);
	for (int i = 0; i < n; ++i)
		x0[i] = y0[i] / normay0;
	double currentNorma = 0;
	do {
		x0prev = x0;
		lam0 = lam1;
		counter++;
		for (int i = 0; i < n; ++i) {
			double tempSum = 0;
			for (int j = 0; j < n; ++j)
				tempSum += a[i][j] * x0[j];
			y0[i] = tempSum;
		}
		cout << "y(" << counter << "): ";
		for (double& i : y0) 
			cout << i << " ";
		cout << "\n";
		normay0 = 0;
		for (double& i : y0)
			normay0 += pow(i, 2);
		normay0 = sqrt(normay0);
		for (int i = 0; i < n; ++i)
			x0[i] = y0[i] / normay0;
		cout << "x(" << counter << "): ";
		for (double& i : x0) 
			cout << i << " ";
		cout << "\n";
		for (double& i : x0prev) {
			if (fabs(i) <= delta) {
				cout << "Division on very small number!!!\n";
				tick = 1;
				break;
			}
		}
		if (tick)break;
		for (int i = 0; i < n; ++i)
			lam1[i] = y0[i] / x0prev[i];
		cout << "lambda(" << counter << "): ";
		for (double& i : lam1) 
			cout << i << " ";
		cout << "\n";
		currentNorma = 0;
		for (int i = 0; i < n; ++i) {
			currentNorma += pow(lam1[i] - lam0[i], 2);
		}
		currentNorma = sqrt(currentNorma);
		cout << "CurrentNorma: " << currentNorma << endl;
	} while (currentNorma > eps);
	if (tick) {
		system("pause");
		return;
	}
	double lamRes;
	double tempsum1 = 0;
	for (int i = 0; i < n; ++i)
		tempsum1 += lam1[i];
	lamRes = (double)(tempsum1 / n);
	cout << "\nlamRes: " << lamRes;
	cout << "\nx1: ";
	for (auto& i : x0) 
		cout << i << " ";
	cout << "\nCounter: " << counter << endl;
}
int main() {
	int n;
	double eps, delta;
	cout << "Input n:";
	cin >> n;
	vector<vector<double>> a(n);
	for (int i = 0; i < n; ++i)
		a[i].resize(n);
	cout << "Input matrix: \n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> a[i][j];
		}
	}
	vector<double> y0(n);
	vector<double> lam1(n);
	cout << "Input y0: ";
	for (double& i : y0)
		cin >> i;
	cout << "Input lambda0: ";
	for (double& i : lam1)
		cin >> i;
	cout << "Input eps, delta: ";
	cin >> eps >> delta;
	PM(n, a, y0, lam1, eps, delta);
	system("pause");
	return 0;
}