#include <iostream>

using namespace std;

int partition(int arr[], int l, int h)
{
    int pivot = arr[l];
    int i = l, j = h;

    while(i < j)
    {
        while(arr[i] <= pivot)
            i++;
        while(arr[j] > pivot)
            j--;
        if(i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[l];
    arr[l] = arr[j];
    arr[j] = temp;

    return j;
}


void quickSort(int arr[], int l, int h)
{
    if(l < h)
    {
        int j = partition(arr, l, h);
        quickSort(arr, l, j - 1);
        quickSort(arr, j+1, h);
    }
}


int main()
{
    int arr[] = {23, 76, 234, 2, 7, 99, 5, 45};

    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Before Sort\n";
    for(int i = 0; i < n; i++)
    {
        cout << arr[i]<< " ";
    }
    cout << endl;

    quickSort(arr, 0, n-1);

    cout << "After quickSort\n";
    for(int i = 0; i < n; i++)
    {
        cout << arr[i]<< " ";
    }
    cout << endl;

    return 0;
}

