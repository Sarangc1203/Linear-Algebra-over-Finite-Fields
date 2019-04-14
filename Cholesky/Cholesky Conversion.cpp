#include <iostream>
#include <chrono>
#include <cmath>
#include<time.h>
#include <cstring> 
using namespace std;
using namespace std::chrono;

int main() 
{ 
	int n,m;
	cin>>n>>m;
	int matrix[n][n];
	int i,j,k;
  // Create a symmetric matrix
	for (i=0;i<n;i++){
	    for (j=i;j<n;j++){
	        matrix[i][j]=rand()%m;
	        matrix[j][i]=matrix[i][j];
	    }
	}
	auto start = high_resolution_clock::now();
	int lower[n][n];
	memset(lower, 0, sizeof(lower));
  // Convert to lower echleon form
    for (i = 0; i < n; i++) { 
		for (j = 0; j <= i; j++) { 
			int sum = 0; 
      //Using general term formula
			if (j == i)
			{
				for (k = 0; k < j; k++) 
					sum += pow(lower[j][k], 2); 
				lower[j][j] = sqrt((matrix[j][j] - 
										sum)); 
			} else { 

				for (k = 0; k < j; k++) 
					sum += (lower[i][k] * lower[j][k]); 
				lower[i][j] = (matrix[i][j] - sum)/lower[j][j]; 
			} 
		} 
	}
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time: "<<duration.count()<<endl;
} 
