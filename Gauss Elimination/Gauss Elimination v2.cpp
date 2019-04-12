#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
using namespace std;
using namespace std::chrono;

int power(int x,int n,int m){
    if (n==0)
        return 1;
    int p=power(x,n/2,m)%m;
    p=(p*p)%m;
    if (n%2==0)
        return p;
    else
        return (x*p)%m;
    }

int modArthInv(int a,int m){
    return power(a,m-2,m);
}

int main() {
	int n = 1000, m=101, t;
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
		if (mat[i][i] == 0) {
			cout << "No Solution";
			break;
		}
		else {
			if (mat[i][i] != 1) {
				int inv = modArthInv(m, mat[i][i]);
				for (j = 0; j <= n; j++) {
					mat[i][j] *= inv;
					mat[i][j] %= m;
					if (mat[i][j] < 0) {
						mat[i][j] += m;
					}
				}
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

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	/*
	for (i = 0; i < n; i++) {
		cout << mat[i][n]%m << "\n";
	}
	*/

	cout << "Time: "<<duration.count()<<endl;
	return 0;
}
