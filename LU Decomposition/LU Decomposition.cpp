#include <iostream>
#include <vector>
#include <chrono>
#include<time.h>
using namespace std;
using namespace std::chrono;

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

int main()
{
    int n = 1000, m=3, t;
    int ttt = 100;
    int ns = 0;
	//cin >> n >> m;
	vector< vector<int> > mat, L;
	vector<int> B;
	srand(time(0)+ttt*124);
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		vector<int> temp, temp1;
		for (j = 0; j <= n; j++)
		{
			//cin >> t;
			t = rand() % m;
			//if (rand()%4 == 0)
                //t = 0;
			//cout << t << " ";
			temp.push_back(t);
			if( i == j)
                temp1.push_back(1);
            else
                temp1.push_back(0);
		}
		//cout << "\n";
		mat.push_back(temp);
		L.push_back(temp1);
		int t1;
		t1 = rand() % m;
		B.push_back(t1);
	}
	/*cout<<"MAT:"<<endl;
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout<<mat[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl<<endl;*/
	auto start = high_resolution_clock::now();
	for (i = 0; i < n; i++) {
		if (mat[i][i] == 0) {
			for (j = i + 1; j < n; j++) {
				if (mat[j][i] != 0) {
					//swaprows(mat, i, j, n);
					vector<int> temp = mat[j];
					mat[j] = mat[i];
					mat[i] = temp;
					break;
				}
			}
		}
		if (mat[i][i] == 0) {
			//cout << "No Solution";
			ns++;
			break;
		}
		else
    {
        for(int j = i +1; j < n; j++)
        {
            int p = (modArthInv(mat[i][i], m) * mat[j][i]) % m;
            if(p<0)
                p+=m;
            L[j][i] = p;
            //cout<<p<<"\t";
            for(int k = 0; k < n; k++)
            {
                mat[j][k] -= p * mat[i][k];
                mat[j][k] %= m;
                if(mat[j][k]<0)
                mat[j][k]+=m;
            }
        }
    }
	}

	/*cout<<"U:"<<endl;
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout<<mat[i][j]<<"\t";
        cout<<endl;
    }
    cout<<"L:"<<endl;
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout<<L[i][j]<<"\t";
        cout<<endl;
    }*/
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    start = high_resolution_clock::now();

    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            B[j] -= L[j][i];
            B[j] %= m;
            if(B[j] < 0)
                B[j] += m;
            L[j][i] = 0;
        }
    }
    for(int i = 0; i < n; i++)
    {
        int p = modArthInv(mat[i][i], m);
        for(int j = i; j < n; j++)
        {
            mat[i][j] *= p;
            mat[i][j] %= m;
            if(mat[i][j] < 0)
                mat[i][j] += m;
        }
        B[i] *= p;
        B[i] %= m;
        if(B[i] < 0)
            B[i] += m;
    }
    for(int i = 0; i < n ; i++)
    {
        for(int j = 0 ; j < i; j++)
        {
            B[j] -= mat[j][i];
            B[j] %= m;
            if(B[j] < 0)
                B[j] += m;
            mat[j][i] = 0;
        }
    }


    /*cout<<"U:"<<endl;
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout<<mat[i][j]<<"\t";
        cout<<endl;
    }
    cout<<"L:"<<endl;
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout<<L[i][j]<<"\t";
        cout<<endl;
    }*/
    stop = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop - start);
	cout<<duration.count()<<endl<<duration2.count();
    return 0;
}
