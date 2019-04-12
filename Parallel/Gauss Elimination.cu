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

__global__
void rre(int i, int j, int n, int *mat, int p, int m)
{
	int k = blockIdx.x * blockDim.x + threadIdx.x;
  	//int stride = blockDim.x * gridDim.x;
	//for(; k+i <= n; k+=stride)
	//{
		//mat[j*(n+1) + k+i] -= p * mat[i*(n+1) + k+i];
		//mat[j*(n+1) + k+i] %= m;
		//if (mat[j*(n+1) + k+i] < 0) {
			//mat[j*(n+1) + k+i] += m;
		//}
	//}
	if(k+i <= n)
	{
		mat[j*(n+1) + k+i] -= p * mat[i*(n+1) + k+i];
		mat[j*(n+1) + k+i] %= m;
		if (mat[j*(n+1) + k+i] < 0) {
			mat[j*(n+1) + k+i] += m;
		}
	}
}

int main() {
	cudaError_t err = cudaSuccess;
	int n = 1000, m=1009, t;
	cout<<n<<m<<endl;
	//cin >> n >> m;
	int *mat;
	err = cudaMallocManaged((void **)&mat, n*(n+1)*sizeof(int));
	if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
	//unordered_map
	srand(time(0));
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		//vector<int> temp;
		for (j = 0; j <= n; j++)
		{
			//cin >> t;
			t = rand() % m;
			//cout << t << " ";
			//temp.push_back(t);
			mat[i*(n+1) + j] = t;
		}
		//cout << "\n";
		//mat.push_back(temp);
	}

	auto start = high_resolution_clock::now();

	for (i = 0; i < n; i++) {
		//cout<<i<<endl;
		if (mat[i*(n+1) + i] == 0) {
			for (j = i + 1; j < n; j++) {
				if (mat[j*(n+1) + i] != 0) {
					//swaprows(mat, i, j, n);
					//vector<int> temp = mat[j];
					//mat[j] = mat[i];
					//mat[i] = temp;
					for(k = 0; k <=n; k++)
					{
						int t = mat[i*(n+1) + k];
						mat[i*(n+1) + k] = mat[j*(n+1) + k];
						mat[j*(n+1) + k] = t;
					}
					break;
				}
			}
		}
		if (mat[i*(n+1) + i] == 0) {
			cout << "No Solution";
			exit(0);
		}
		else {
			if (mat[i*(n+1) + i] != 1) {
				int inv = modArthInv(m, mat[i*(n+1) + i]);
				for (j = 0; j <= n; j++) {
					mat[i*(n+1) + j] *= inv;
					mat[i*(n+1) + j] %= m;
					if (mat[i*(n+1) + j] < 0) {
						mat[i*(n+1) + j] += m;
					}
				}
			}

			for (j = 0; j < n; j++) {
				if(j !=i && mat[j*(n+1) + i] != 0)
				{
					rre<<<(n + 1023)/1024,1024>>>(i, j, n, mat, mat[j*(n+1) + i], m);
					cudaDeviceSynchronize();
				}
			}

			/*
			for (j = 0; j < n; j++) {
				if(j != i && mat[j][i] != 0) {
					int temp = mat[j][i];
					for (k = i; k <= n; k++) {
						mat[j][k] -= temp * mat[i][k];
						mat[j][k] %= m;
						if (mat[j][k] < 0) {
							mat[j][k] += m;
						}
					}			} */
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	/*
	for (i = 0; i < n; i++) {
		cout << mat[i*(n+1) + n]%m << "\n";
	}
	*/

	cout << "Time: "<<duration.count()<<endl;

	cudaFree(mat);
	return 0;
}
