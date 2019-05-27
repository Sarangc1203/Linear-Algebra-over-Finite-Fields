#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

int generator(int n){
    int i, j;
    //int p = pow(n,n1);
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

int power(int g, int t, int n)
{
    int x = 1;
    for(int i = 1; i <= t; i++)
    {
        x = x*g;
        x %= n;
        //cout<<"\tPower: "<<x<<endl;
    }
    return x;
}

int main()
{
    ifstream inf;
    inf.open("otp");
    int ttt = 12;
    //cout<<generator(11)<<endl;
    while(!inf.eof())
    {
        string s;
        getline(inf, s);
        stringstream str(s);
        int q, n;
        str>>q>>n;
        int n1 = n;
        n++;
        vector<int> minpoly;
        //cout<<"\nNew data:"<<endl;
        //cout<<q<<" "<<n1<<endl;
        for(int i = 0; i < n; i++)
        {
            minpoly.push_back(0);
        }
        getline(inf,s);
        int len = s.length();
        cout<<s<<endl;
        while(len > 0)
        {
            if(s[0] == 'x')
            {
                //cout<<"x_1"<<endl;
                s = s.substr(3, len-1);
                len = s.length();
                if(s[0] == '^')
                {
                    //cout<<"^"<<endl;
                    int t;
                    for(int i = 1; i < len; i++)
                    {
                        if(i == len-1)
                        {
                            i++;
                            stringstream str1(s.substr(1, i-1));
                            str1>>t;
                            //cout<<t<<endl;
                            s = s.substr(i, len-1);
                            len = s.length();
                            minpoly[n-1-t] = 1;
                            //cout<<"89 Update minpoly power: "<<n-1-t<<" with "<<1<<endl;
                            break;
                        }
                        else if(s[i]=='+' || s[i] == '-')
                        {
                            stringstream str1(s.substr(1, i-1));
                            str1>>t;
                            //cout<<t<<endl;
                            s = s.substr(i, len-1);
                            len = s.length();
                            minpoly[n-1-t] = 1;
                            //cout<<"100 Update minpoly power: "<<n-1-t<<" with "<<1<<endl;
                            break;
                        }
                    }
                }
                else
                {
                    minpoly[n-2] = 1;
                    //cout<<"108 Update minpoly power: "<<n-2<<" with "<<1<<endl;
                }
            }
            else if(s[0] == 'Z')
            {
                //cout<<"Z"<<endl;
                int coeff;
                int t;
                for(int i = 2; i < len; i++)
                {
                    if(s[i] == ')')
                    {
                        stringstream str1(s.substr(2, i-1));
                        str1>>t;
                        //cout<<t<<endl;
                        int g = generator(t);
                        //cout<<"generator: "<<g<<endl;
                        s = s.substr(i+1, len-1);
                        len = s.length();
                        if(s[0] == '^')
                        {
                            //cout<<"^"<<endl;
                            for(int j = 1; j < len; j++)
                            {
                                if(j == len-1)
                                {
                                    j++;
                                    stringstream str2(s.substr(1, j-1));
                                    str2>>t;
                                    //cout<<t<<endl;
                                    s = s.substr(j, len-1);
                                    len = s.length();
                                    //cout<<"power for coeff: "<<g<<" "<<t<<" "<<n1<<endl;
                                    coeff = power(g,t,q);
                                    break;
                                }
                                else if(s[j]=='+' || s[j] == '-' || s[j] == '*')
                                {
                                    stringstream str2(s.substr(1, j-1));
                                    str2>>t;
                                    //cout<<t<<endl;
                                    s = s.substr(j, len-1);
                                    len = s.length();
                                    coeff = power(g,t,q);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            coeff = g;
                        }
                        break;
                    }
                }
                //cout<<"s[0] = "<<s[0]<<endl;
                if(len!=0 && s[0] =='*')
                {
                    //cout<<"*"<<endl;
                    s = s.substr(4,len-1);
                    len = s.length();
                    if(s[0] == '^')
                    {
                        int t;
                        for(int i = 1; i < len; i++)
                        {
                            if(i == len-1)
                            {
                                i++;
                                stringstream str1(s.substr(1, i-1));
                                str1>>t;
                                s = s.substr(i, len-1);
                                len = s.length();
                                minpoly[n-1-t] = coeff;
                                //cout<<"180 Update minpoly power: "<<n-1-t<<" with "<<coeff<<endl;
                                break;
                            }
                            else if(s[i]=='+' || s[i] == '-')
                            {
                                stringstream str1(s.substr(1, i-1));
                                str1>>t;
                                s = s.substr(i, len-1);
                                len = s.length();
                                minpoly[n-1-t] = coeff;
                                //cout<<"190 Update minpoly power: "<<n-1-t<<" with "<<coeff<<endl;
                                break;
                            }
                        }
                    }
                    else
                    {
                        minpoly[n-2] = coeff;
                        //cout<<"198 Update minpoly power: "<<n-2<<" with "<<coeff<<endl;
                    }
                }
                else
                {
                    minpoly[n-1] = coeff;
                    //cout<<"204 Update minpoly power: "<<n-1<<" with "<<coeff<<endl;
                }
            }
            else if(s[0] == '+')
            {
                s = s.substr(1,len-1);
                len = s.length();
            }
            else if(s[0] == '-')
            {
                s = s.substr(1,len-1);
                len = s.length();
                if(s[0] == 'x')
                {
                    s = s.substr(3, len-1);
                    len = s.length();
                    if(s[0] == '^')
                    {
                        int t;
                        for(int i = 1; i < len; i++)
                        {
                            if( i == len-1)
                            {
                                i++;
                                stringstream str1(s.substr(1, i-1));
                                str1>>t;
                                s = s.substr(i, len-1);
                                len = s.length();
                                minpoly[n-1-t] = q-1;
                                //cout<<"233 Update minpoly power: "<<n-1-t<<" with "<<q-1<<endl;
                                break;
                            }
                            else if(s[i]=='+' || s[i] == '-')
                            {
                                stringstream str1(s.substr(1, i-1));
                                str1>>t;
                                s = s.substr(i, len-1);
                                len = s.length();
                                minpoly[n-1-t] = q-1;
                                //cout<<"243 Update minpoly power: "<<n-1-t<<" with "<<q-1<<endl;
                                break;
                            }
                        }
                    }
                    else
                    {
                        minpoly[n-2] = q-1;
                        //cout<<"251 Update minpoly power: "<<n-2<<" with "<<q-1<<endl;
                    }
                }
                else if(s[0] == 'Z')
                {
                    int coeff;
                    int t;
                    for(int i = 2; i < len; i++)
                    {
                        if(s[i] == ')')
                        {
                            stringstream str1(s.substr(2, i-1));
                            str1>>t;
                            int g = generator(t);
                            //cout<<"generator: "<<g<<endl;
                            s = s.substr(i+1, len-1);
                            len = s.length();
                            if(s[0] == '^')
                            {
                                for(int j = 1; j < len; j++)
                                {
                                    if(j == len-1)
                                    {
                                        j++;
                                        stringstream str2(s.substr(1, j-1));
                                        str2>>t;
                                        s = s.substr(j, len-1);
                                        len = s.length();
                                        coeff = power(g,t,q);
                                        break;
                                    }
                                    else if(s[j]=='+' || s[j] == '-' || s[j] == '*')
                                    {
                                        stringstream str2(s.substr(1, j-1));
                                        str2>>t;
                                        s = s.substr(j, len-1);
                                        len = s.length();
                                        coeff = power(g,t,q);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                coeff = g;
                            }
                            break;
                        }
                    }
                    coeff = q - coeff;
                    //cout<<"s[0] = "<<s[0]<<endl;
                    if(len != 0 && s[0] == '*')
                    {
                        //cout<<"*"<<endl;
                        s = s.substr(4,len-1);
                        len = s.length();
                        if(s[0] == '^')
                        {
                            int t;
                            for(int i = 1; i < len; i++)
                            {
                                if(i == len-1)
                                {
                                    i++;
                                    stringstream str1(s.substr(1, i-1));
                                    str1>>t;
                                    s = s.substr(i, len-1);
                                    len = s.length();
                                    minpoly[n-1-t] = q - coeff;
                                    //cout<<"318 Update minpoly power: "<<n-1-t<<" with "<<q-coeff<<endl;
                                    break;
                                }
                                else if(s[i]=='+' || s[i] == '-')
                                {
                                    stringstream str1(s.substr(1, i-1));
                                    str1>>t;
                                    s = s.substr(i, len-1);
                                    len = s.length();
                                    minpoly[n-1-t] = q - coeff;
                                    //cout<<"328 Update minpoly power: "<<n-1-t<<" with "<<q-coeff<<endl;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            minpoly[n-2] = coeff;
                            //cout<<"336 Update minpoly power: "<<n-2<<" with "<<q-coeff<<endl;
                        }
                    }
                    else
                    {
                        minpoly[n-1] = coeff;
                        //cout<<"342 Update minpoly power: "<<n-1<<" with "<<q-coeff<<endl;
                    }
                }
            }
        }
        cout<<q<<" "<<n1<<endl;
        cout<<"generator: "<<generator(q)<<endl;
        cout<<"MinPoly:"<<endl;
        for(int i = 0; i < minpoly.size(); i++)
        {
            cout<<minpoly[i]<<" ";
        }
        cout<<endl<<endl;;
    }
    return 0;
}
