#include <time.h>
#include <chrono>
#include <vector>
#include <math.h>
#include <random>
#include <iostream>
using namespace std;
using namespace std::chrono;
void ijkalgorithm(vector< vector<float> > A, int n)
{
    vector< vector<float> > B;
    for (int i = 0; i < n; i++)
    {
        vector<float> temp2;
        for (int j = 0; j < n; j++)
        {
            float temp = 0;
            for (int k = 0; k < n; k++)
            {
                temp += A[k][i] * A[k][j];
            }
            temp2.push_back(temp);
            cout<<temp<<"\t";
        }
        B.push_back(temp2);
        cout<<"\n";
    }
}



vector< vector<float> > QRDecomp(vector <vector<float> > mat, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            float sum1 = 0, sum2 = 0;
            for(int k = 0; k < n; k++)
            {
                sum1 += mat[k][i]*mat[k][j];
                sum2 += mat[k][j]*mat[k][j];
            }
            for(int k = 0; k < n; k++)
            {
                mat[k][i] -= sum1*mat[k][j]/sum2;
                //mat[k][i] %= m;
            }
        }
        float sum = 0;
        for(int k = 0; k < n; k++)
        {
            sum += mat[k][i]*mat[k][i];
        }
        sum = sqrt(sum);
        for(int k = 0; k < n; k++)
        {
            mat[k][i] /= sum;
        }
    }
    return mat;
}

vector< float > MatMult(vector <vector<float> > Q, vector <int> B, int n)
{
    vector <float> R;
    for(int i = 0; i < n; i++)
    {
        float row = 0;
        for(int j = 0; j < n; j++)
        {
            row += Q[j][i]*B[j];
        }
        R.push_back(row);
    }
    return R;
}

int main()
{
    int n = 1000;
    int m = 1009;
    float t;
    vector< vector<float> > mat;
    vector<int> B;
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		vector<float> temp;
		for (int j = 0; j < n; j++)
		{
			//cin >> t;
			t = rand() % m;
			//cout << t << " ";
			temp.push_back(t);
		}
		//cout << "\n";
		mat.push_back(temp);
		t = rand() % m;
		B.push_back(t);
	}
	auto start = high_resolution_clock::now();
	/*cout<<"Mat:"<<endl;
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<mat[i][j]<<"\t";
        }
        cout<<"\n";
    }*/
    vector< vector<float> > Q = QRDecomp(mat, n);
    /*cout<<"\nQ:"<<endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<Q[i][j]<<"\t";
        }
        cout<<"\n";
    }*/
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time: "<<duration.count()<<endl;
	start = high_resolution_clock::now();
	vector< float > R = MatMult(Q, B, n);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Time: "<<duration.count()<<endl;
	/*for(int i = 0; i < n; i++)
    {
        cout<<R[i];
        cout<<"\n";
    }*/
    //ijkalgorithm(Q, n);
    return 0;
}
