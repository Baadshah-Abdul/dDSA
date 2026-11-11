#include <iostream>

using namespace std;

void adjustMax(int arr[], int i, int n)
{
    int j = 2 * i + 1;
    int x = arr[i];
    while (j <= n - 1)
    {
        if (j < n - 1 && arr[j] < arr[j + 1]) j = j + 1;
        if (x >= arr[j]) break;
        arr[(j - 1) / 2] = arr[j];
        j = 2 * j + 1;
    }
    arr[(j - 1) / 2] = x;
}

void insertMax(int arr[], int &n, int x)
{
    int i = n;
    n++;
    while (i > 0 && arr[(i - 1) / 2] < x)
    {
        arr[i] = arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    arr[i] = x;
}

int delMax(int arr[], int &n)
{
    if (n == 0) return -1;
    int maxVal = arr[0];
    arr[0] = arr[n - 1];
    n--;
    adjustMax(arr, 0, n);
    return maxVal;
}

void heapifyMax(int arr[], int n)
{
    for (int i = (n - 2) / 2; i >= 0; i--)
        adjustMax(arr, i, n);
}

void adjustMin(int arr[], int i, int n)
{
    int j = 2 * i + 1;
    int x = arr[i];
    while (j <= n - 1)
    {
        if (j < n - 1 && arr[j] > arr[j + 1]) j = j + 1;
        if (x <= arr[j]) break;
        arr[(j - 1) / 2] = arr[j];
        j = 2 * j + 1;
    }
    arr[(j - 1) / 2] = x;
}

void insertMin(int arr[], int &n, int x)
{
    int i = n;
    n++;
    while (i > 0 && arr[(i - 1) / 2] > x)
    {
        arr[i] = arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    arr[i] = x;
}

int delMin(int arr[], int &n)
{
    if (n == 0) return -1;
    int minVal = arr[0];
    arr[0] = arr[n - 1];
    n--;
    adjustMin(arr, 0, n);
    return minVal;
}

void heapifyMin(int arr[], int n)
{
    for (int i = (n - 2) / 2; i >= 0; i--)
        adjustMin(arr, i, n);
}

void heapSort(int arr[], int n)
{
    heapifyMax(arr, n);
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        adjustMax(arr, 0, i);
    }
}

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int maxHeap[20];
    int maxSize = 0;

    insertMax(maxHeap, maxSize, 45);
    insertMax(maxHeap, maxSize, 23);
    insertMax(maxHeap, maxSize, 99);
    insertMax(maxHeap, maxSize, 7);
    insertMax(maxHeap, maxSize, 76);

    print(maxHeap, maxSize);

    delMax(maxHeap, maxSize)  ;
    print(maxHeap, maxSize);

    int minHeap[20];
    int minSize = 0;

    insertMin(minHeap, minSize, 45);
    insertMin(minHeap, minSize, 23);
    insertMin(minHeap, minSize, 99);
    insertMin(minHeap, minSize, 7);
    insertMin(minHeap, minSize, 76);

    print(minHeap, minSize);

    delMin(minHeap, minSize);
    print(minHeap, minSize);

    return 0;
}
