#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
using namespace std;
using namespace std::chrono;

vector <int> inverse;

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

int modArthInvDyn(int a, int m){
    if (inverse[a]==-1)
        inverse[a]=power(a,m-2,m);
    return inverse[a];
}

int modArthInv(int a,int m){
    return power(a,m-2,m);
}

int main(){
    int n,m;
    cin>>n>>m;
    int i;
    vector <int> a,b,c;
    for (i=0;i<m;i++)
        inverse.push_back(-1);
    for (i=0;i<n;i++)
        a.push_back(rand()%m);
    auto start = high_resolution_clock::now();
    for (i=0;i<n;i++)
        b.push_back(modArthInv(a[i],m));
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time: "<<duration.count()<<endl;
	
	
	auto start1 = high_resolution_clock::now();
    for (i=0;i<n;i++)
        c.push_back(modArthInv(a[i],m));
    auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Time(Dynamic): "<<duration1.count()<<endl;
}
