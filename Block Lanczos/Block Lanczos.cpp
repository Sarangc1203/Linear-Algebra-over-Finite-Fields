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

bool isNull(vector<int> v){
    int flag=0;
    int i,n=v.size();
    for (i=0;i<n;i++){
        if (v[i]!=0){
            flag=1;
            break;}
            }
    if (flag==0) return true; else return false;
        }

// to get v(t).A.w

int multiply(vector<int> v,vector< vector<int> > A,vector<int> w,int m) {
int i,j;
int sum=0,n=v.size();
for (i=0;i<n;i++){
	for (j=0;j<n;j++){
	sum=sum+v[j]*A[j][i]*w[i];
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
	result[i]=result[i]+A[i][j]*v[j];
	result[i]=result[i]%m;}
	}
	return result;
}

// to get v(t).w

int multiply3(vector<int> v,vector<int> w,int m) {
int i;
int sum=0,n=v.size();
for (i=0;i<n;i++){
	sum=sum+v[i]*w[i];
	sum=sum%m;
	}
	return sum;
}

// to get the ith row of a 2d vector

vector<int> getRow(vector<vector<int>> V,int i,int n){
return V[i];}

int main() {
	int n=100,m=101;
	//cin >> n >> m;
	vector< vector<int> > A;
	srand(time(0));
	int i, j, k,flag=0;
	for (i = 0; i < n; i++)
	{
		vector<int> temp;
		if (i!=0){
		for (j=0;j<i;j++)
		temp.push_back(A[j][i]);}
		for (j = i; j <n; j++)
		{
			int t;
			//cin>>t;
			t = rand() % m;
			//cout << t << " ";
			temp.push_back(t);
		}
		//cout << "\n";
		A.push_back(temp);
	}
	/*for (i=0;i<n;i++){
	    for (j=0;j<n;j++){
	        cout<<A[i][j]<<" ";}
	        cout<<endl;
	    }*/
	vector<int> b;
	for (i=0;i<n;i++){
	int t;
	t=rand()%m;
	//cin>>t;
	b.push_back(t);
	//cout<<b[i]<<" ";}
	}
	
	cout<<endl;
	
	auto start = high_resolution_clock::now();
	
	vector<vector<int>> V;
	V.push_back(b);
	auto start2 = high_resolution_clock::now();
	vector<vector<int>> sqrA= square(A,m,n);
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);

	cout << "Time:"<<duration2.count()<<endl;
	int l;
	for (i=1;;i++){
		vector <int> temp;
		vector <int> temp2= multiply2(A,V[i-1],m);
		//for (j=0;j<n;j++)
		//cout<<temp2[j]<<" ";
		vector <int> temp3= V[i-1];
		int c1= multiply(temp3,sqrA,temp3,m)*modArthInv(multiply(temp3,A,temp3,m),m)%m;
		int c2;
		if (i!=1)
		c2=multiply(temp3,A,temp3,m)*modArthInv(multiply(V[i-2],A,V[i-2],m),m)%m;
		for (j=0;j<n;j++){
			if (i!=1)
			temp.push_back((temp2[j]+m-c1*V[i-1][j]%m+m-c2*V[i-2][j]%m+m)%m);
			else
			temp.push_back((temp2[j]+m-c1*V[i-1][j]%m)%m);
		}
		V.push_back(temp);
		if (multiply(temp,A,temp,m)==0){
		if (isNull(temp)==false)
		    flag=1;
		l=i;
		cout<<l<<endl;
		break;
		}
	}
	vector<int> x;
	for (i=0;i<n;i++){
	    x.push_back(0);}
	for (i=0;i<l;i++){
		vector<int> temp= V[i];
		int c=(multiply3(temp,b,m)*modArthInv(multiply(temp,A,temp,m),m))%m;
		for (j=0;j<n;j++){
			x[j]=x[j]+(temp[j]*c);
			x[j]=x[j]%m;
		}
		}
	if (flag==1)
	cout<<" Algorithm fails";
	else{
	for (i=0;i<n;i++)
	    cout<<x[i]<<" ";}

    
	cout<<endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time:"<<duration.count()<<endl;
}
