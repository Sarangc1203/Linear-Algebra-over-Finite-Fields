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


vector<int> Difference(vector<int> a,vector<int> b){
    int i=0,j=0;
    vector<int> c;
    for (i=0;i<a.size();i++){
        if (j < b.size() && a[i]==b[j])
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

int generator(int n, int n1=1, vector<int> poly={1}){
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
        int p=pow(n,n1);
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



int main()
{
    int b=0;
    vector<int> q1;
    vector<vector<int>> R1;
    //q1.push_back(3);
    //R1.push_back({2});
    for (int p=1621;p<=1621;p=p+2){
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
                    //cout<<d<<" "<<endl;
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    //cout<<"haaa"<<endl;
    /*for (int o=0;o<q1.size();o++){
        cout<<q1[o]<<" ";
    }
    cout<<endl;
    for (int o=0;o<R1.size();o++){
        for (int t=0;t<R1[o].size();t++){
            cout<<R1[o][t]<<" ";
        }
        cout<<endl;
    }*/


    //----------------------------------------


    for(int index = 0; index < q1.size(); index++)
    {
        //cout<<"index"<<endl;
        int q = q1[index];
        for(int n1 = 0; n1 < R1[index].size(); n1++)
        {	
			if (R1[index][n1]==1)
			{
				//cout<<"nq"<<endl;
				int g = generator(q);
				//cout<<g<<endl;
				int p = pow(q,R1[index][n1]);
				//cout<<p<<endl;
				set<int> F;
				for(int i = 0; i < p; i++)
					F.insert(i);
				vector<int> dlist;
				//cout<<"dlist:"<<endl;
				for(int i = 1; i<=(p-1)/2; i+=2)
				{
					if( (p-1)%i == 0 )
					{
						if( gcd(i,(p-1)/i) == 1)
						{
							dlist.push_back(i);
							//cout<<i<<" ";
						}
					}
				}
				//cout<<"dlist"<<endl;
				set<int> P;
				for(int i = 1; i <= p-1; i++)
				{
					if(gcd(i, p-1)== 1)
					{
						P.insert(power(g,i,p));
					}
				}
				//cout<<"P"<<endl;
				reverse(dlist.begin(), dlist.end());
				int flag = 0;
				for(int d1 = 0; d1 < dlist.size(); d1++)
				{
					int d = dlist[d1];
					vector<int> Ad;

					vector<long long> e1 = PrimeDivisors((p-1)/d);
					int e = 1;
					for(int i = 0; i < e1.size(); i++)
						e*=e1[i]%p;

					for(int n11 = 0; n11 < e; n11++)
						Ad.push_back(power(g,n11*d, p));
					sort(Ad.begin(), Ad.end());
					vector< long long> dfacts = PrimeDivisors(d);
					int s = dfacts.size();
					vector< vector<int> > R;
					for(int i =0; i < s; i++)
					{
						vector<int> tempv;
						for(int j = 1; j <= (dfacts[i]-1)/2; j++)
						{
							tempv.push_back(j);
						}
						R.push_back(tempv);
					}

					vector< vector<int> > epsilon;
					for(int i = 0; i < pow(2,s); i++)
					{
						vector<int> tempv;
						for(int j = 0; j < s; j++)
						{
							if( ((i)%(int)pow(2,j+1)) - pow(2, j) < 0)
							   tempv.push_back(1);
							else
							   tempv.push_back(-1);
						}
						epsilon.push_back(tempv);
					}

					vector< set<int> > x;
					set<int> y;
					for(int i = 0; i < epsilon.size(); i++)
					{
						set<int> xtemp = F;
						vector< set<int> > epsR;
						for(int j = 0; j < s; j++)
						{
							set<int> temp2;
							set<int> epsRtemps;
							for(int k = 0; k < R[j].size(); k++)
							{
								epsRtemps.insert((((epsilon[i][j]*R[j][k]) % dfacts[j])+dfacts[j])%dfacts[j]);
							}
							epsRtemps.insert(0);
							epsR.push_back(epsRtemps);
							for(int k = 1; k < p; k++)
							{
								if(epsR[j].find(k % dfacts[j]) != epsR[j].end())
									temp2.insert(power(g,k,p));
							}
							set<int> xtemptemp;
							set_intersection(xtemp.begin(), xtemp.end(), temp2.begin(), temp2.end(), inserter(xtemptemp, xtemptemp.begin()));
							xtemp = xtemptemp;
						}
						x.push_back(xtemp);
						set<int> ytemp;
						set_union(xtemp.begin(), xtemp.end(), y.begin(), y.end(), inserter(ytemp, ytemp.begin()));
						y = ytemp;
					}
					y.insert(0);
					/*cout<<endl<<"X:"<<endl;
					for(int i = 0; i < x.size(); i++)
					{
						set<int>::iterator itr;
						for(itr = x[i].begin(); itr != x[i].end(); ++itr)
							cout<<*itr<<" ";
						cout<<endl;
					}
					cout<<"y:"<<endl;
						set<int>::iterator itr;
						for(itr = y.begin(); itr != y.end(); ++itr)
							cout<<*itr<<" ";
						cout<<endl;*/
					if(y.size() == p)
						cout<<"";
					else
						cout<<"";
					for (int alp=0;alp<Ad.size();alp++){
						int alpha=Ad[alp];
						for (int bet=0;bet<Ad.size();bet++){
							int beta=Ad[bet];
							set<int> A;
							set<int> B;
							for (int xdind=0;xdind<x.size();xdind++){
								set<int> xd=x[xdind];
								vector<int> yrange;
								set_intersection(P.begin(),P.end(),xd.begin(),xd.end(),back_inserter(yrange));
								for (int xeind=0;xeind<x.size();xeind++){
									set<int> xe=x[xeind];
									vector<int> xrange;
									set_intersection(P.begin(),P.end(),xe.begin(),xe.end(),back_inserter(xrange));
									for (int x1i=0;x1i<xrange.size();x1i++){
										int x1=xrange[x1i];
										for (int y1i=0;y1i<yrange.size();y1i++){
											int y1=yrange[y1i];
											A.insert((((alpha*x1+1)*(alpha*x1+1)-beta*y1)%p+p)%p);
										}
									}
								}
								set<int>::iterator x1;
								for (x1=P.begin();x1!=P.end();++x1){
									for (int y1i=0;y1i<yrange.size();y1i++){
										int y1=yrange[y1i];
										B.insert((((*x1)*(*x1)-beta*y1)%p+p)%p);
									}
								}
							}
							A.insert(0);
							B.insert(0);
							/*cout<<"A:"<<endl;
							set<int>::iterator itr;
							for(itr = A.begin(); itr != A.end(); ++itr)
								cout<<*itr<<" ";
							cout<<endl;
							cout<<"B:"<<endl;
							for(itr = B.begin(); itr != B.end(); ++itr)
								cout<<*itr<<" ";
							cout<<endl;*/
							if (A.size()!=p)
								flag=1;
							if (B.size()!=p)
								flag=1;
							if (flag==1)
								break;
						}
						if (flag==1)
							break;
					}
					if (flag==0)
						break;
				}
				if (flag==0)
					cout<<q<<"^"<<R1[index][n1]<<"\t\tNot Exception"<<endl;
				else
					cout<<q<<"^"<<R1[index][n1]<<"\t\tException"<<endl;
			}
			else
			{
				vector<int> poly={1,38,6};
				//cout<<"nq"<<endl;
				//cout<<g<<endl;
				int n = R1[index][n1];
				
				int g = generator(q,n,poly);
				int p = pow(q,n);
				//cout<<p<<endl;
				set<int> F;
				for(int i = 0; i < p; i++)
					F.insert(i);
				vector<int> dlist;
				//cout<<"dlist:"<<endl;
				for(int i = 1; i<=(p-1)/2; i+=2)
				{
					if( (p-1)%i == 0 )
					{
						if( gcd(i,(p-1)/i) == 1)
						{
							dlist.push_back(i);
							//cout<<i<<" ";
						}
					}
				}
				//cout<<"dlist"<<endl;
				set<int> P;
				for(int i = 1; i <= p-1; i++)
				{
					if(gcd(i, p-1)== 1)
					{
						P.insert(toInt(power(toVec(g,q,n),i,poly,q,n),q));
					}
				}
				//cout<<"P"<<endl;
				reverse(dlist.begin(), dlist.end());
				int flag = 0;
				for(int d1 = 0; d1 < dlist.size(); d1++)
				{
					int d = dlist[d1];
					vector<int> Ad;

					vector<long long> e1 = PrimeDivisors((p-1)/d);
					int e = 1;
					for(int i = 0; i < e1.size(); i++)
						e*=e1[i]%p;
					for(int n11 = 0; n11 < e; n11++)
						Ad.push_back(toInt(power(toVec(g,q,n),n11*d,poly,q,n),q));
					sort(Ad.begin(), Ad.end());
					//cout<<"Ad";
					vector< long long> dfacts = PrimeDivisors(d);
					int s = dfacts.size();
					vector< vector<int> > R;
					for(int i =0; i < s; i++)
					{
						vector<int> tempv;
						for(int j = 1; j <= (dfacts[i]-1)/2; j++)
						{
							tempv.push_back(j);
						}
						R.push_back(tempv);
					}
					vector< vector<int> > epsilon;
					for(int i = 0; i < pow(2,s); i++)
					{
						vector<int> tempv;
						for(int j = 0; j < s; j++)
						{
							if( ((i)%(int)pow(2,j+1)) - pow(2, j) < 0)
							   tempv.push_back(1);
							else
							   tempv.push_back(-1);
						}
						epsilon.push_back(tempv);
					}
					//cout<<"eps"<<endl;
					vector< set<int> > x;
					set<int> y;
					for(int i = 0; i < epsilon.size(); i++)
					{
						set<int> xtemp = F;
						vector< set<int> > epsR;
						//cout<<"xyz"<<endl;
						for(int j = 0; j < s; j++)
						{
							set<int> temp2;
							set<int> epsRtemps;
							for(int k = 0; k < R[j].size(); k++)
							{
								epsRtemps.insert((((epsilon[i][j]*R[j][k]) % dfacts[j])+dfacts[j])%dfacts[j]);
							}
							epsRtemps.insert(0);
							epsR.push_back(epsRtemps);
							//cout<<"start"<<endl;
							vector<int> gen=toVec(g,q,n);
							for(int k = 1; k < p; k++)
							{
								if(epsR[j].find(k % dfacts[j]) != epsR[j].end())
									temp2.insert(toInt(power(gen,k,poly,q,n),q));
							}
							//cout<<"end"<<endl;
							set<int> xtemptemp;
							set_intersection(xtemp.begin(), xtemp.end(), temp2.begin(), temp2.end(), inserter(xtemptemp, xtemptemp.begin()));
							xtemp = xtemptemp;
						}
						x.push_back(xtemp);
						set<int> ytemp;
						set_union(xtemp.begin(), xtemp.end(), y.begin(), y.end(), inserter(ytemp, ytemp.begin()));
						y = ytemp;
					}
					y.insert(0);
					/*cout<<endl<<"X:"<<endl;
					for(int i = 0; i < x.size(); i++)
					{
						set<int>::iterator itr;
						for(itr = x[i].begin(); itr != x[i].end(); ++itr)
							cout<<*itr<<" ";
						cout<<endl;
					}
					cout<<"y:"<<endl;
						set<int>::iterator itr;
						for(itr = y.begin(); itr != y.end(); ++itr)
							cout<<*itr<<" ";
						cout<<endl;*/
					if(y.size() == p)
						cout<<"";
					else
						cout<<"";
					cout<<"hhh"<<endl;
					for (int alp=0;alp<Ad.size();alp++){
						vector<int> alpha=toVec(Ad[alp],q,n);
						for (int bet=0;bet<Ad.size();bet++){
							vector<int> beta=toVec(Ad[bet],q,n);
							set<int> A;
							set<int> B;
							for (int xdind=0;xdind<x.size();xdind++){
								set<int> xd=x[xdind];
								vector<int> yrange;
								set_intersection(P.begin(),P.end(),xd.begin(),xd.end(),back_inserter(yrange));
								for (int xeind=0;xeind<x.size();xeind++){
									set<int> xe=x[xeind];
									vector<int> xrange;
									set_intersection(P.begin(),P.end(),xe.begin(),xe.end(),back_inserter(xrange));
									for (int x1i=0;x1i<xrange.size();x1i++){
										vector<int> x1=toVec(xrange[x1i],q,n);
										for (int y1i=0;y1i<yrange.size();y1i++){
											vector<int> y1=toVec(yrange[y1i],q,n);
											A.insert(toInt(Subtract(Multiply(Add(Multiply(alpha,x1,poly,q),toVec(1,q,n),q),Add(Multiply(alpha,x1,poly,q),toVec(1,q,n),q),poly,q),Multiply(beta,y1,poly,q),q),q));
										}
									}
								}
								set<int>::iterator x1i;
								for (x1i=P.begin();x1i!=P.end();++x1i){
									vector<int> x1=toVec(*x1i,q,n);
									for (int y1i=0;y1i<yrange.size();y1i++){
										vector<int> y1=toVec(yrange[y1i],q,n);
										B.insert(toInt(Subtract(Multiply(x1,x1,poly,q),Multiply(beta,y1,poly,q),q),q));
									}
								}
							}
							A.insert(0);
							B.insert(0);
							/*cout<<"A:"<<endl;
							set<int>::iterator itr;
							for(itr = A.begin(); itr != A.end(); ++itr)
								cout<<*itr<<" ";
							cout<<endl;
							cout<<"B:"<<endl;
							for(itr = B.begin(); itr != B.end(); ++itr)
								cout<<*itr<<" ";
							cout<<endl;*/
							if (A.size()!=p)
								flag=1;
							if (B.size()!=p)
								flag=1;
							if (flag==1)
								break;
						}
						if (flag==1)
							break;
					}
					if (flag==0)
						break;
				}
				if (flag==0)
					cout<<q<<"^"<<R1[index][n1]<<"\t\tNot Exception"<<endl;
				else
					cout<<q<<"^"<<R1[index][n1]<<"\t\tException"<<endl;
			}
        }
    }
    return 0;
}
