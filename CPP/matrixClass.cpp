#include <iostream>

using namespace std;

// // Dynamic 2D Ararys
//     int rows, cols;
//     // 1
//     cout << "rows: \ncols: " << endl;
//     cin >> rows >> cols;
//     // 2
//     int **table = new int *[rows];
//     // 3
//     for (int i = 0; i < rows; i++)
//     {
//         table[i] = new int[cols];
//     }
//     // accessing elements
//     table[0][0] = 88;
//     // deallocate
//     for (int i = 0; i < rows; i++)
//     {
//         delete[] table[i];
//     }
//     delete[] table;
//     table = NULL;

class dMatrix
{
private:
    int **d2Array;
    int rows, cols, sum, prod;

public:
    dMatrix(int m, int n)
    {
        rows = m, cols = n;
        d2Array = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            d2Array[i] = new int[cols];
        }
    }

    ~dMatrix()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] d2Array[i];
        }
        delete[] d2Array;
        d2Array = NULL;
    }

    void setMatrix()
    {
        int a;
        int b;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << "Enter for matrix:[" << i << "][" << j << "]  ";
                cin >> a;
                d2Array[i][j] = a;
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << d2Array[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void addMatrix(const dMatrix &other)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                int sum = d2Array[i][j] + other.d2Array[i][j];
                cout << sum << "\t";
            }
            cout << endl;
        }
    }

    void multimatrix(const dMatrix &other)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                prod = 0;
                for (int k = 0; k <= 2; k++)
                {
                    prod = prod + (d2Array[i][k] * d2Array[k][j]);
                }
                cout << prod << "\t";
            }
            cout << endl;
        }
    }
};

int main()
{
    dMatrix m1(3, 3);
    dMatrix m2(3, 3);
    m1.setMatrix();
    m2.setMatrix();
    cout << endl;
    m1.addMatrix(m2);
    cout << endl;
    m1.multimatrix(m2);

    return 0;
}