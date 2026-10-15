#include <iostream>
using namespace std;

class DynamicArray
{
private:
    int *dArray;
    int size, eCount, oCount, capacity;

public:
    DynamicArray(int arraySize)
    {
        dArray = new int[arraySize];
        size = 0;
        eCount = 0;
        oCount = 0;
        capacity = arraySize;
    }

    int insert(int index, int value)
    {
        if (size >= capacity)
        {
            return 1;
        }

        if (index < 0 || index > size)
        {
            return 2;
        }

        for (int i = size - 1; i >= index; i--)
        {
            dArray[i + 1] = dArray[i];
        }
        dArray[index] = value;
        size++;

        if (value % 2 == 0)
        {
            eCount++;
        }
        else
        {
            oCount++;
        }

        return 0;
    }

    int insertEO(int value)
    {
        int index = 0;
        if (size >= capacity)
            return 1;

        if (value % 2 == 0)
        {
            index = eCount;
        }
        else
        {
            index = size;
        }

        for (int i = size - 1; i >= index; i--)
        {
            dArray[i + 1] = dArray[i];
        }
        dArray[index] = value;
        size++;
        if (value % 2 == 0)
        {
            eCount++;
        }
        else
        {
            oCount++;
        }
        return 0;
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << dArray[i] << " ";
        }
    }

    int getSize()
    {
        return size;
    }

    ~DynamicArray()
    {
        if (dArray != nullptr)
        {
            delete[] dArray;
        }
    }
};

int main()
{
    DynamicArray array = DynamicArray(10);

    array.insertEO(1);
    array.insertEO(2);
    array.insertEO(3);
    array.insertEO(4);
    array.insertEO(6);
    array.insertEO(5);
    array.insertEO(8);
    array.insertEO(7);
    array.insertEO(9);
    array.insertEO(10);

    array.display();
}