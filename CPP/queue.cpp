#include <iostream>

using namespace std;

class Queue
{
private:
    int *arr;
    int size, capacity;

public:
    Queue(int cap)
    {
        capacity = cap;
        arr = new int[cap];
        size = 0;
    }

    void push(int value)
    {
        if (size == capacity)
        {
            cout << "Queue overflow\n";
            return;
        }
        size++;
        arr[size] = value;
    }

    void pop()
    {
        if (size == 0)
        {
            cout << "Queue underflow\n";
            return;
        }
        for (int i = 1; i < size; i++)
        {
            arr[i - 1] = arr[i];
        }
        size--;
    }

    void peekF()
    {
        if (size == 0)
        {
            cout << "empty\n";
            return;
        }
        cout << arr[0] << endl;
    }

    void peekL()
    {
        if (size == 0)
        {
            cout << "empty\n";
            return;
        }
        cout << arr[size - 1] << endl;
    }
};

int main()
{
    Queue q(4);

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.peekF();
    q.peekL();
    q.pop();
    q.peekF();
    q.peekL();
    q.pop();
    q.peekF();
    q.peekL();
    q.pop();
    q.peekF();
    q.peekL();

    return 0;
}