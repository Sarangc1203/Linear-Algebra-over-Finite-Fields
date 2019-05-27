#include <iostream>
#include <vector>
using namespace std;

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
    while(i <= j)
    {
        t = a[i];
        int k = 0;
        while(k < len)
        {
            //cout<<i+k<<" "<<a[i+k];
            a[i+k] -= t*b[j+k];
            a[i+k] = ((a[i+k] % q) + q) % q;
            k++;
            //cout<<" "<<a[i+k]<<endl;
        }
        i++;
    }
    return a;
}

int main()
{
    int q = 3;
    vector<int> a = {0,1,0,2,2};
    vector<int> b = {0,0,1,2,1};
    vector<int> c = Add(a,b,q);
    vector<int> d = Remainder(a,b,q);
    cout<<"C:"<<endl;
    for(int i = 0; i < a.size(); i++)
        cout<<c[i]<<" ";
    cout<<endl;
    cout<<"D:"<<endl;
    for(int i = 0; i < a.size(); i++)
        cout<<d[i]<<" ";
    return 0;
}
