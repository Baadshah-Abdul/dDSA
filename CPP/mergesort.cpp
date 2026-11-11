#include <iostream>

using namespace std;

void merge(int arr[], int l, int mid, int h)
{
    //size od arrays
    int ls = mid -l + 1;
    int rs = h - mid;

    //create arr
    int *larr = new int[ls];
    int *rarr = new int[rs];

    for(int i = 0; i < ls; i++)
        larr[i] = arr[l+i];

    for(int i = 0; i < rs; i++)
        rarr[i] = arr[mid + 1 + i];


    //merge
    int  i = 0, j = 0, k = l;
    while(i < ls && j < rs)
    {
        if(larr[i] <= rarr[j])
        {
            arr[k] = larr[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = rarr[j];
            j++;
            k++;
        }
    }

    //copy leftover elements
    while(i < ls)
    {
        arr[k] = larr[i];
        i++;
        k++;
    }
    while(j < rs)
    {
        arr[k] = rarr[j];
        j++;
        k++;
    }

}

void mergeSort(int arr[], int l, int h)
{
    if(l < h)
    {
        int mid = (l+h)/2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, h);
        merge(arr, l, mid, h);
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

    mergeSort(arr, 0, n-1);

    cout << "After Sort\n";
    for(int i = 0; i < n; i++)
    {
        cout << arr[i]<< " ";
    }
    cout << endl;

    return 0;
}
