#include <iostream>
#include <chrono>
#include <vector>
#include<time.h>
#include <cmath>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
using namespace std::chrono;

vector<int> Add(vector<int> a, vector<int> b, int q)
{
    int n  = a.size();
    int t;
    vector<int> c;
    for(int i = 0; i < n; i++)
    {
        t = a[i] + b[i];
        t %= q;
        c.push_back(t);
    }
    return c;
}

vector<int> Subtract(vector<int> a,vector<int> b, int q){
	int n=b.size();
	for (int i=0;i<n;i++){
		b[i]=q-b[i];
	}
	return Add(a,b,q);
}

vector<int> Remainder(vector<int> a, vector<int> b, int q)
{
    int na = a.size();
    int nb = b.size();
    int i, j;
    for(i = 0; i < na; i++)
    {
        if(a[i] != 0)
            break;
    }
    for(j = 0; j < nb; j++)
    {
        if(b[j] != 0)
            break;
    }
    int len = nb-j;
    //cout<<"len: "<<len<<endl;
    int t;
    while(i <= (na-len))
    {
        t = a[i];
       // cout<<t<<endl;
        int k = 0;
        while(k < nb-j)
        {
            //cout<<i+k<<" "<<a[i+k];
            a[i+k] -= t*b[j+k];
            a[i+k] = ((a[i+k] % q) + q) % q;
            k++;
            //cout<<" "<<a[i+k]<<endl;
        }
        i++;
    }
    vector<int> c;
    for (i=(na-nb+1);i<na;i++){
        c.push_back(a[i]);
        //cout<<a[i]<<endl;
    }
    return c;
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

vector<int> Multiply(vector<int> a,vector<int> b,vector<int> poly,int q){
    int l1=a.size();
    int l2=b.size();
    vector<int> c;
    int i;
    for (i=0;i<(l1+l2-1);i++){
        c.push_back(0);
    }
    while (l2>0){
        l1=a.size();
        while (l1>0){
            c[l1+l2-2]=(c[l1+l2-2]+a[l1-1]*b[l2-1])%q;
            l1--;
        }
        l2--;
    }
    return Remainder(c,poly,q);
}

int gcd(int a, int b)
{
    if(b>a)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    while(a%b!=0)
    {
        int temp = a%b;
        a = b;
        b = temp;
    }
    return b;
}

vector<int> toVec(int a,int q,int n){
    vector<int> temp;
    while (n>0){
        temp.push_back(a%q);
        a=a/q;
        n--;
    }
    reverse(temp.begin(),temp.end());
    return temp;
}

int toInt(vector<int> n,int q){
    int a=1,result=0;
    int l=n.size();
    while (l>0){
        result=result+a*n[l-1];
        a=a*q;
        l--;
    }
    return result;
}

int generator(int n, vector<int> poly, int n1=1){
    if (n1==1){
        int i, j;
        int order = n-1;
        int g;
        for (i=2;i<n;i++)
        {
            int temp = i;
            for(j = 2; j < n; j++)
            {
                temp = (temp*i)%n;
                if(temp == 1)
                    break;
            }
            if(j == order){
                g=i;
                break;
            }
        }
        return g;
    }
    else{
        int i;
        int p=llround(pow(n,n1));
        for (i=2;i<p;i++){
            int j;
            vector<int> num=toVec(i,n,n1);
            vector<int> temp,temp3;
            for (j=0;j<n1;j++){
                temp.push_back(0);
                temp3.push_back(0);
            }
            temp3[n1-1]=1;
            for (j=0;j<poly.size();j++){
                int k;
                vector<int> temp2;
                for (k=0;k<n1;k++)
                    temp2.push_back(0);
                temp2[n1-1]=poly[poly.size()-j-1];
                temp2=Multiply(temp2,temp3,poly,n);
        //       for (int i1=0;i1<temp2.size();i1++){
      //  cout<<temp2[i1]<<" ";
    //}
    //cout<<endl;
                temp=Add(temp,temp2,n);
                temp3=Multiply(temp3,num,poly,n);
            }
            if (isNull(temp))
                break;
        }
        return i;
    }
}

long long int power(long long int x, unsigned int y, int p)
{
    long long int res = 1;      // Initialize result
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

vector<int> power(vector<int> a,int n,vector<int> poly,int q,int n1){
	vector<int> temp=toVec(1,q,n1);
	while (n>0){
		if (n%2==1)
			temp=Multiply(temp,a,poly,q);
		n=n/2;
		a=Multiply(a,a,poly,q);
	}
	return temp;
}

int main(){
    int n=1;
    int q=23;
    int p=llround(pow(q,n));
    vector<int> P;
    int g=generator(q,{1});
    P.push_back(g);
    for (int i=2;i<p-1;i++){
        if (gcd(p-1,i)==1)
            P.push_back(power(g,i,p));
    }
    sort(P.begin(),P.end());
    int N=P.size();

    for (int i=1;i<p;i++){
        for (int j=0;j<p;j++){
            for (int k=0;k<p;k++){
                int red=0;
                vector<int> A={i,j,k};
                //if ((j*j-4*i*k)%p!=0){
                    for (int m=0;m<p;m++){
                        if (((i*m*m+j*m+k)%p)==0){
                            red=1;
                            break;
                        }
                    }
                    //cout<<red<<endl;
                    int count=0;
                    int foundP=0;
                    if (red==0){
                        for (int m=0;m<N;m++){
                            int a=P[m];
                            count=count+1;
                            if (foundP==0){
                                if (binary_search(P.begin(),P.end(),(i*a*a+j*a+k)%p)){
                                    foundP=1;
                                    //cout<<"jjj"<<endl;
                                }
                                else{
                                    if (count==N)
                                        cout<<"False"<<endl;
                                }
                            }
                        }
                    }
                //}
            }
        }
    }
}
