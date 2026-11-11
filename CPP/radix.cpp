#include <iostream>

using namespace std;

int getmax(int arr, int n)
{
    int max = arr[0];
    for(int i = 0; i < n; n++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    return max;
}

void countingSort(int arr[], int place, int n)
{
    int output[100];
    int count[10] = {0};

    //count occurences of each digit
    for(int i = 0; i < n; i++)
    {
        int digit = (arr[i]/place) % 10;
        count[digit]++;
    }

    //total count
    for(int i = 1; i < n; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for(int i = n - 1, i >= 0; i--)
    {
        int digit = (arr[i]/place) % 10;
        output[count[digit]-1] = arr[i];
        count[digit]--;
    }

    //copy to original arr
    for(int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);
    for(int place = 1; max/place > 0; place = place *10)
        countingSort(arr, place, n);
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

    radixSort(arr, 0, n-1);

    cout << "After Sort\n";
    for(int i = 0; i < n; i++)
    {
        cout << arr[i]<< " ";
    }
    cout << endl;

    return 0;
}
