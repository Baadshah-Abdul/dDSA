#include <iostream>

using namespace std;

int m = 0, n = 0;

void mAdd(int a[3][3], int b[3][3])
{
    int sum[3][3];

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            cout << sum[i][j] << "\t";
        }
        cout << endl;
    }
}

void mMulti(int a[3][3], int b[3][3])
{
    int prod[3][3];

    int sum = 0;

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            sum = 0;
            for (int k = 0; k <= 2; k++)
            {
                sum = sum + (a[i][k] * b[k][j]);
            }
            prod[i][j] = sum;
        }
    }

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            cout << prod[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int m1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    int m2[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    mAdd(m1, m2);
    cout << endl;
    mMulti(m1, m2);

    return 0;
}