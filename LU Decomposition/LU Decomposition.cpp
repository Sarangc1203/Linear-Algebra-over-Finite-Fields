#include <iostream>
using namespace std;

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

int main()
{
    int n = 100, m=3, t;
	//cin >> n >> m;
	vector< vector<int> > mat;
	int L[n][n];
	srand(time(0)+ttt*124);
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		vector<int> temp;
		for (j = 0; j <= n; j++)
		{
			//cin >> t;
			t = rand() % m;
			//if (rand()%4 == 0)
                //t = 0;
			//cout << t << " ";
			temp.push_back(t);
			L[i][j] = (i==j)?1:0;
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
			//cout << "No Solution";
			ns++;
			break;
		}
	}
	else
    {
        for(int j = i +1; j < n; j++)
        {
            int p = (modArthInv(m, mat[i][i]) * mat[j][i]) % m
            L[j][i1] = p
            for(int k = 0; k < n; k++)
            {
                U[j][k] -= p * U[i, k];
                U[j][k] %= m;
            }
        }
    }
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout<<duration.count()<<endl;
    return 0;
}
