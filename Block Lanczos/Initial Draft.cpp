#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
using namespace std;
using namespace std::chrono;

//to square a matrix A

vector<vector<int>> square(vector<vector<int>> A, int m, int n){
vector<vector<int>> sqr;
int i,j,k;
for (i=0;i<n;i++){
	vector<int> temp;
	for (j=0;j<n;j++){
		temp.push_back(0);
		for (k=0;k<n;k++){
			temp[j]=temp[j]+A[i][k]*A[k][j];
			temp[j]=temp[j]%m;
			}
		}
	sqr.push_back(temp);
	}
	return sqr;
}

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

// to get v(t).A.w

int multiply(vector<int> v,vector< vector<int> > A,vector<int> w,int m) {
int i,j;
int sum=0,n=v.size();
for (i=0;i<n;i++){
	for (j=0;j<n;j++){
	sum=sum+v[i]*A[j][i]*w[i];
	sum=sum%m;}
	}
	return sum;
}

// to get A.v

vector<int> multiply2(vector<vector<int>> A,vector<int>v,int m){
vector<int> result;
int i,j;
int n=v.size();
for (i=0;i<n;i++){
	result.push_back(0);
	for (j=0;j<n;j++){
	result[i]=result[i]+A[i][j]*v[i];
	result[i]=result[i]%m;}
	}
	return result;
}

// to get v(t).w

int multiply3(vector<int> v,vector<int> w,int m) {
int i,j;
int sum=0,n=v.size();
for (i=0;i<n;i++){
	for (j=0;j<n;j++){
	sum=sum+v[i]*w[i];
	sum=sum%m;}
	}
	return sum;
}

// to get the ith row of a 2d vector

vector<int> getRow(vector<vector<int>> V,int i,int n){
vector<int> temp;
int j;
for (j=0;j<n;j++){
temp.push_back(V[i][j]);}
return temp;}

int main() {
	int n,m;
	cin >> n >> m;
	vector< vector<int> > A;
	srand(time(0));
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		vector<int> temp;
		for (j=0;j<i;j++)
		temp.push_back(A[j][i]);
		for (j = i; j <n; j++)
		{
			int t;
			t = rand() % m;
			//cout << t << " ";
			temp.push_back(t);
		}
		//cout << "\n";
		A.push_back(temp);
	}
	vector<int> b;
	for (i=0;i<n;i++){
	b.push_back(rand()%m);}
	
	
	auto start = high_resolution_clock::now();
	
	vector<vector<int>> V;
	V.push_back(b);
	
	vector<vector<int>> sqrA= square(A,m,n);
	int l;
	for (i=1;;i++){
		vector <int> temp;
		vector <int> temp2= multiply2(A,getRow(V,i-1,n),m);
		int c1= multiply(temp2,sqrA,temp2,m)*modArthInv(multiply(temp2,A,temp2,m),m)%m;
		if (i!=1);
		int c2=multiply(temp2,A,temp2,m)*modArthInv(multiply(getRow(V,i-2,n),A,getRow(V,i-2,n),m),m)%m;
		for (j=0;j<n;j++){
			if (i!=1)
			temp.push_back((temp2[j]-c1*getRow(V,i-1,n)[j]-c2*getRow(V,i-2,n)[j])%m);
			else
			temp.push_back((temp2[j]-c1*getRow(V,i-1,n)[j])%m);}
		V.push_back(temp);
		if (multiply(temp,A,temp,m)==0){
		l=i;
		break;
		}
	}
	vector<int> x;
	for (i=0;i<l;i++){
		vector<int> temp= getRow(V,i,n);
		int c=multiply3(temp,b,m)*modArthInv(multiply(temp,A,temp,m),m)%m;
		for (j=0;j<n;j++){
			x.push_back(temp[j]);
		}
		}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time:"; 
}
