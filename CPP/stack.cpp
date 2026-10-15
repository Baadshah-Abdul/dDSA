#include <iostream>

using namespace std;

class Stack
{
private:
    int top, cap, size;
    int *arr;

public:
    Stack(int capacity)
    {
        top = -1;
        size = 0;
        cap = capacity;
        arr = new int[cap];
    }

    int push(int value)
    {
        if (top == cap - 1)
        {
            cout << "Stack Overflow\n";
            return 2;
        }
        top++;
        arr[top] = value;
        size++;
        return 0;
    }

    int isEmpty()
    {
        if (top == -1)
        {
            cout << "EMpty\n";
            return 0;
        }
        cout << "NOt Empty\n";
        return 5;
    }

    int pop()
    {
        if (top == -1)
        {
            cout << "Stack Underflow\n";
            return 3;
        }
        top--;
        size--;
        cout << arr[top] << endl;
        return 0;
    }
    int peek()
    {
        if (top == -1)
        {
            cout << " Stack Empty\n";
            return 4;
        }
        cout << arr[top] << endl;
        return 0;
    }
};

int main()
{
    Stack s(4);

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    s.peek();
    s.pop();
    s.peek();
    s.pop();
    s.peek();
    s.pop();
    s.peek();

    s.isEmpty();

    s.pop();
    s.peek();

    return 0;
}