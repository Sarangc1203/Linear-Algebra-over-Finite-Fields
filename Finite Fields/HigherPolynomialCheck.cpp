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

vector<int> constMult(vector<int> v, int i, int q)
{
    for(int j = 0; j < v.size(); j++)
    {
        v[j] = (v[j]*i)%q;
    }
    return v;
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

vector<int> MinPoly(int q, int n)
{
    vector<int> minpoly;
    if(n==2)
    {
        switch(q)
        {
            case 3: minpoly = {1,2,2}; break;
			case 5: minpoly = {1,4,2}; break;
			case 7: minpoly = {1,6,3}; break;
			case 11: minpoly = {1,7,2}; break;
			case 13: minpoly = {1,12,2}; break;
			case 17: minpoly = {1,16,3}; break;
			case 19: minpoly = {1,18,2}; break;
			case 23: minpoly = {1,21,5}; break;
			case 29: minpoly = {1,24,2}; break;
			case 31: minpoly = {1,29,3}; break;
			case 37: minpoly = {1,33,2}; break;
			case 41: minpoly = {1,38,6}; break;
			case 43: minpoly = {1,42,3}; break;
			case 47: minpoly = {1,45,5}; break;
			case 53: minpoly = {1,49,2}; break;
			case 59: minpoly = {1,58,2}; break;
			case 61: minpoly = {1,60,2}; break;
			case 67: minpoly = {1,63,2}; break;
			case 71: minpoly = {1,69,7}; break;
			case 73: minpoly = {1,70,5}; break;
			case 79: minpoly = {1,78,3}; break;
			case 83: minpoly = {1,82,2}; break;
			case 89: minpoly = {1,82,3}; break;
			case 97: minpoly = {1,96,5}; break;
			case 101: minpoly = {1,97,2}; break;
			case 103: minpoly = {1,102,5}; break;
			case 109: minpoly = {1,108,6}; break;
			case 113: minpoly = {1,101,3}; break;
			case 131: minpoly = {1,127,2}; break;
			case 139: minpoly = {1,138,2}; break;
			case 149: minpoly = {1,145,2}; break;
			case 151: minpoly = {1,149,6}; break;
			case 181: minpoly = {1,177,2}; break;
			case 211: minpoly = {1,207,2}; break;
			case 229: minpoly = {1,228,6}; break;
			case 239: minpoly = {1,237,7}; break;
			case 281: minpoly = {1,280,3}; break;
			case 349: minpoly = {1,348,2}; break;
			case 379: minpoly = {1,374,2}; break;
			case 419: minpoly = {1,418,2}; break;
			case 461: minpoly = {1,460,2}; break;
			case 571: minpoly = {1,570,3}; break;
			case 659: minpoly = {1,655,2}; break;
			case 769: minpoly = {1,765,11}; break;
			case 911: minpoly = {1,909,17}; break;
			case 1231: minpoly = {1,1229,3}; break;
			case 1429: minpoly = {1,1425,6}; break;
        }
    }
    else if(n==3)
    {
        switch(q)
        {
            case 3: minpoly = {1,0,2,1}; break;
			case 5: minpoly = {1,0,3,3}; break;
			case 7: minpoly = {1,6,0,4}; break;
			case 11: minpoly = {1,0,2,9}; break;
			case 13: minpoly = {1,0,2,11}; break;
			case 17: minpoly = {1,0,1,14}; break;
			case 19: minpoly = {1,0,4,17}; break;
        }
    }
    else if(n==4)
    {
        switch(q)
        {
            case 3: minpoly = {1,2,0,0,2}; break;
			case 5: minpoly = {1,0,4,4,2}; break;
			case 7: minpoly = {1,0,5,4,3}; break;
			case 11: minpoly = {1,0,8,10,2}; break;
			case 13: minpoly = {1,0,3,12,2}; break;
        }
    }
    else if(n==5)
    {
    	switch(q)
    	{
    		case 3: minpoly = {1,0,0,0,2,1}; break;
			case 5: minpoly = {1,0,0,0,4,3}; break;
    	}
    }
    else if(n==6)
    {
        switch(q)
        {
        	case 3: minpoly = {1,0,2,0,1,2,2}; break;
            case 5: minpoly = {1,0,1,4,1,0,2}; break;
        }
    }
    else if(n==7)
    {
    	switch(q)
    	{
    		case 3: minpoly = {1,0,0,0,0,2,0,1}; break;
    	}
    }
    else if(n==8)
    {
    	switch(q)
    	{
    		case 3: minpoly = {1,0,0,2,1,0,2,2,2}; break;
    	}
    }
    return minpoly;
}


int main(){
    int n=4;
    int q=3;
    int p = llround(pow(q,n));
    vector<int> P;
    if(n == 1)
    {
        int g=generator(q,{1});
        P.push_back(g);
        for (int i=2;i<p-1;i++){
            if (gcd(p-1,i)==1)
                P.push_back(power(g,i,p));
        }
        sort(P.begin(),P.end());
        int N=P.size();

        for (int i=1;i<p;i++){
            for (int j=1;j<p;j++){
                for (int k=1;k<p;k++){
                    for (int l=1;l<p;l++){
                        int red=0;
                        vector<int> A={i,j,k,l};
                        for (int m=0;m<p;m++){
                            if (((i*m*m*m+j*m*m+k*m+l)%p)==0){
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
                                    if (binary_search(P.begin(),P.end(),(i*a*a*a+j*a*a+k*a+l)%p)){
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
                    }
                }
            }
        }
    }
    else
    {
        vector<int> minpoly = MinPoly(q,n);
        //cout<<toInt(power(toVec(3,q,n),17,minpoly,q,n),q);
        int g=generator(q,minpoly,n);
        //cout<<"gen:"<<g<<endl;
        //cout<<toInt(Subtract(toVec(g,q,n),Multiply(toVec(4,q,n),toVec(g,q,n),minpoly,q),q),q)<<endl;
        for(int i = 1; i < p; i++)
        {
            //cout<<toInt(power(toVec(g,q,n),i,minpoly,q,n),q)<<endl;
        }
        P.push_back(g);
        for (int i=2;i<p-1;i++){
            if (gcd(p-1,i)==1)
                {
                    P.push_back(toInt(power(toVec(g,q,n),i,minpoly,q,n),q));
                    //cout<<P[P.size()-1]<<endl;
                }
        }
        sort(P.begin(),P.end());
        int N=P.size();
    int counter = 0;
        for (int i=1;i<p;i++){
            for (int j=1;j<p;j++){
                for (int k=1;k<p;k++){
                    for (int l=1;l<p;l++){
                        int red=0;
                        vector<int> A={i,j,k};
                        vector<int> i1,j1,k1,l1,fouri1;
                        i1 = toVec(i,q,n);
                        j1 = toVec(j,q,n);
                        k1 = toVec(k,q,n);
                        l1 = toVec(l,q,n);
                        fouri1 = constMult(i1,4,q);
                        for (int m=0;m<p;m++){
                            vector<int> m1=toVec(m,q,n);
                            vector<int> m2=power(m1,2,minpoly,q,n);
                            vector<int> m3=power(m1,3,minpoly,q,n);
                            if (toInt(Add(Multiply(i1,m3,minpoly,q),Add(Multiply(j1,m2,minpoly,q),Add(Multiply(k1,m1,minpoly,q),l1,q),q),q),q)==0)
                            {
                                red = 1;
                                break;
                            }
                        }
                        //cout<<red<<endl;
                        /*for (int m=0;m<p;m++){
                            if (((i*m*m+j*m+k)%p)==0){
                                red=1;
                                break;
                            }
                        }*/
                        //cout<<red<<endl;
                        int count=0;
                        int foundP=0;
                        if (red==0){
                            for (int m=0;m<N;m++){
                                int a=P[m];
                                count=count+1;
                                if (foundP==0){
                                    vector<int> a1 = toVec(a,q,n);
                                    vector<int> a2 = power(a1,2,minpoly,q,n);
                                    vector<int> a3 = power(a1,3,minpoly,q,n);
                                    int res = toInt(Add(Multiply(i1,a3,minpoly,q),Add(Multiply(j1,a2,minpoly,q),Add(Multiply(k1,a1,minpoly,q),l1,q),q),q),q);
                                    //cout<<res<<endl;
                                    if (binary_search(P.begin(),P.end(),res)){
                                        //cout<<"res: "<<res<<endl;
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
                    }
                }
            }
        }
        //cout<<"counter: "<<counter<<endl;
    }
}
