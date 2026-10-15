#include <iostream>

using namespace std;

int* dynamicArray(int size)
{
    int* dArray = new int[size];
    int eIndex = 0, oIndex = size/2;
    for(int i = 0; i < size; i++)
    {
        if(i%2 == 0)
        {
            dArray[eIndex] = i;
            eIndex++;
        }
        if (i%2 != 0)
        {
            dArray[oIndex] = i;
            oIndex++;
        }
    }
    return dArray;
}

int main()
{
    //create dArray
    int* dArray = dynamicArray(10);

    for(int i = 0; i < 10; i++)
    {
        cout << dArray[i] << "\n";
    }

    //cleanup
    delete[] dArray;
    
    return 0;
}