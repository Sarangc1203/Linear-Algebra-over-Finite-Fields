#include <iostream>
#include <chrono>
#include <vector>
#include <time.h>
#include <omp.h>
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
	int n1[2] = {100, 1000}, m1[4] = {3, 31, 101, 1009};
	for(int n11 = 0; n11 < 2; n11++)
	{
		for(int m11 = 0; m11 < 4; m11++)
		{
	int ttt = (n11==0)?1000:100;
	float ttt2 = ttt;
	float totaltime = 0;
	int ns = 0;
	int n = n1[n11], m=m1[m11], t;
	while(ttt--){
	//cin >> n >> m;
	vector< vector<int> > mat;
	srand(time(0)+ttt*124);
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		vector<int> temp;
		for (j = 0; j <= n; j++)
		{	/*if (j!=n)
			cin >> t;
			else
			t=0;*/
			t = rand() % m;
			if(rand()%4 == 0)
				t = 0;
			//if (rand()%4 == 0)
                //t = 0;
			//cout << t << " ";
			temp.push_back(t);
		}
		//cout << "\n";
		mat.push_back(temp);
	}
	/*for (i=0;i<n;i++){
		cin>>t;
		mat[i][n]=t;
	}*/

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
		else {
			if (mat[i][i] != 1) {
				int inv = modArthInv(mat[i][i], m);
				#pragma omp parallel for private(j)
				for (j = 0; j <= n; j++) {
					mat[i][j] *= inv;
					mat[i][j] %= m;
					if (mat[i][j] < 0) {
						mat[i][j] += m;
					}
				}
			}
			#pragma omp parallel for private(j,k)
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

	
	/*for (i = 0; i < n; i++) {
		cout << mat[i][n]%m << " ";
	}*/
	//cout << "Time: "<<duration.count()<<endl;
	totaltime += duration.count();
	}
	cout<<n<<"\t"<<m<<endl<<totaltime/ttt2<<"\n"<<ns<<endl<<endl<<endl;
		}
	}
	return 0;
}