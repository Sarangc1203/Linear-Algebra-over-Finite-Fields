#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
using namespace std;
using namespace std::chrono;

int modArthInv1(int a, int b) {
	if (b == 1)
		return 1;
	else {
		int p = a;
		int q = b;
		vector< vector<int> > l;
		int j = 0;
		while ((p % q) != 0) {
			vector<int> v;
			v.push_back(1);
			v.push_back(p / q);
			v.push_back(p % q);
			l.push_back(v);
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

int modArthInv2(int a,int m){
    return power(a,m-2,m);
}

int main()
{
    int n = 1000, m = 7919;
    int t = 0;

    auto start = high_resolution_clock::now();

    for(int i = 1; i < m; i++)
    {
        //cout<<i<<endl;
        t = modArthInv1(m, i);
    }

    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time: "<<duration.count()<<endl;

	start = high_resolution_clock::now();

    for(int i = 1; i < m; i++)
    {
        //cout<<i<<endl;
        t = modArthInv1(m, i);
    }

    stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Time: "<<duration.count()<<endl;
    return 0;
}
