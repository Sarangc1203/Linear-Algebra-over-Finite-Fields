#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
using namespace std;
using namespace std::chrono;

int modArthInv(int a, int b) {
	if (b == 1)
		return 1;
	else {
		int p = a;
		int q = b;
		int l[][3] = { 0,0,0,0 };
		int j = 0;
		while ((p % q) != 0) {
			l[j][0] = 1;
			l[j][1] = p / q;
			l[j][2] = p % q;
			int temp = p;
			p = q;
			q = temp % q;
			j = j + 1;
		}
		int i = j - 2;
		while (i >= 0) {
			l[i][0] = l[i + 1][1];
			l[i][1] = l[i + 1][1] * l[i][1] + l[i + 1][0];
			l[i][2] = -l[i + 1][2];
			i -= 1;
		}
		if (l[0][2] < 0)
			return (l[0][1] % a);
		else
			return (-l[0][1]) % a;
	}
}

int main() {
	int n=20, m=23, t;
	//cin >> n >> m;
	vector< vector<int> > mat;
	srand(time(0));
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		vector<int> temp;
		for (j = 0; j <= n; j++)
		{
			//cin >> t;
			t = rand() % m;
			//cout << t << " ";
			temp.push_back(t);
		}
		//cout << "\n";
		mat.push_back(temp);
	}

	cout<<"Start\n";
	auto start = high_resolution_clock::now();

	for (i = 0; i < n; i++) {
		if (mat[i][i] == 0) {
			for (j = i + 1; j < n; j++) {
				if (mat[j][i] != 0) {
					//swaprows(mat, i, j, n);
					vector<int> temp = mat[j];
					mat[j] = mat[i];
					mat[i] = temp;
					break;
				}
			}
		}
		cout<<"Replace"<<i<<"\n";
		if (mat[i][i] == 0) {
			cout << "No Solution\n";
			break;
			goto exitprog;
		}
		else {
                cout<<"RRE\n";
			if (mat[i][i] != 1) {
				int inv = modArthInv(m, mat[i][i]);
				for (j = 0; j <= n; j++) {
					mat[i][j] *= inv;
					mat[i][j] %= m;
					if (mat[i][j] < 0) {
						mat[i][j] += m;
					}
				}
                cout<<"Modarthinv\n";
			}
			for (j = 0; j < n; j++) {
				if(j != i && mat[j][i] != 0) {
					int temp = mat[j][i];
					for (k = i; k <= n; k++) {
						mat[j][k] -= temp * mat[i][k];
						mat[j][k] %= m;
						if (mat[j][k] < 0) {
							mat[j][k] += m;
						}
					}
				}
			}
		}
	}
    exitprog:
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	/*
	for (i = 0; i < n; i++) {
		cout << mat[i][n]%m << "\n";
	}
	*/

	cout << "Time: "<<duration.count()<<endl;

	int p;
	cin >> p;

	return 0;
}
