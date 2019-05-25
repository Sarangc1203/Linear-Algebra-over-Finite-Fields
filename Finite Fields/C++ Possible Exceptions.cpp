#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
#include <cmath>
using namespace std;
using namespace std::chrono;

vector<int> Difference(vector<int> a,vector<int> b){
	int i=0,j=0;
	vector<int> c;
	for (i=0;i<a.size();i++){
		if (a[i]==b[j])
			j++;
		else
			c.push_back(a[i]);
	}
	return c;
}

vector<long long int> Divisors(long long int n){
	vector<long long int> a;
	vector<long long int> b;
	for (long long int i=1;i<=sqrt(n);i++){
		if (n%i==0){
			if (i==n/i)
				a.push_back(i);
			else{
				a.push_back(i);
				b.push_back(n/i);
			}
		}
	}
	for (int i=b.size()-1;i>=0;i--){
		a.push_back(b[i]);
	}
	return a;
}

vector<long long int> PrimeDivisors(long long int n){
	vector<long long int> v;
	long long int a=n;
	while (n%2==0){
	    if (a==n){
			v.push_back(2);}
		n=n/2;
	}
	for (long long int i=3;i<=sqrt(n);i=i+2){
	    long long int a=n;
		while (n%i==0){
			if (a==n)
				v.push_back(i);
			n=n/i;
		}
	}
	if (n>2)
		v.push_back(n);
	return v;
}

int power(int x, unsigned int y, int p) 
{ 
    int res = 1;      // Initialize result 
    x = x % p;  // Update x if it is more than or 
                // equal to p 
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x) % p; 
  
        // y must be even now 
        y = y>>1; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 

bool miillerTest(int d, int n) 
{ 
    // Pick a random number in [2..n-2] 
    // Corner cases make sure that n > 4 
    int a = 2 + rand() % (n - 4); 
  
    // Compute a^d % n 
    int x = power(a, d, n); 
  
    if (x == 1  || x == n-1) 
       return true; 
  
    // Keep squaring x while one of the following doesn't 
    // happen 
    // (i)   d does not reach n-1 
    // (ii)  (x^2) % n is not 1 
    // (iii) (x^2) % n is not n-1 
    while (d != n-1) 
    { 
        x = (x * x) % n; 
        d *= 2; 
  
        if (x == 1)      return false; 
        if (x == n-1)    return true; 
    } 
  
    // Return composite 
    return false; 
} 

bool isPrime(int n, int k) 
{ 
    // Corner cases 
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
  
    // Find r such that n = 2^d * r + 1 for some r >= 1 
    int d = n - 1; 
    while (d % 2 == 0) 
        d /= 2; 
  
    // Iterate given nber of 'k' times 
    for (int i = 0; i < k; i++) 
         if (!miillerTest(d, n)) 
              return false; 
  
    return true; 
} 

int generator(int n){
    int i,j;
    int a[n];
    
    for (i=0;i<n;i++)
        a[i]=1;
        
    for (i=2;i<n;i++){
        int flag=0;
        int temp=i;
        for (j=0;j<n;j++){
            a[temp]=0;
            temp=(temp*i)%n;
        }
        for (j=1;j<n;j++){
            if (a[j]!=0){
                flag=1;
                break;
            }
        }
        if (flag==0)
            break;
    }
    return i;
}

int main()
{
    int b=0;
	vector<int> q1;
	vector<vector<int>> R1;
	int p;
	for (p=3;p<=501;p=p+2){
		if (isPrime(p,4)){
		    vector<int> K={1,2,3,4,5};
		    vector<int> B;
		    int k;
		    for (k=0;k<K.size();k++){
		        vector<long long int> D=Divisors(pow(p,K[k])-1);
				vector<long long int> P=PrimeDivisors(pow(p,K[k])-1);
				int counts=0;
				for (int l=0;l<D.size();l++){
					float d=1.0;
					int count=0;
					for (int m=0;m<P.size();m++){
						if (D[l]%P[m]!=0){
							d=d-2.0/P[m];
							count++;
						}
					}
					//cout<<d<<" ";
					if (d>0){
						float dlt=((2.0*count-1.0)/d)+2;
						vector<long long int> e=PrimeDivisors(D[l]);
						int f=e.size();
						float z=pow(p,K[k]/2.0);
						float z2=pow(2,f);
						if (counts==0 && z>(dlt*(2*z2*(z2-1.5)+1.5*z2/z)+1+1.5*z2/z)){
							B.push_back(K[k]);
							counts=1;
						}
					}
				}
		    }
			vector<int> R=Difference(K,B);
			//for (int k=0;k<B.size();k++)
			  //  cout<<B[k]<<" ";
			//cout<<endl;
			if (R.size()>0){
				q1.push_back(p);
				R1.push_back(R);
			}
		}
	}
	for (int o=0;o<q1.size();o++){
		cout<<q1[o]<<" ";
	}
	cout<<endl;
	for (int o=0;o<R1.size();o++){
		for (int t=0;t<R1[o].size();t++){
		    cout<<R1[o][t]<<" ";
		}
		cout<<endl;
	}
}
