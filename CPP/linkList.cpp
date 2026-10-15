#include <iostream>

using namespace std;

class linkList
{
public:
    int value, size;
    linkList *next;

//public:
    linkList()
    {
        next = NULL;
        value = 0;
        size = 0;
    }
    void display()
    {
        linkList *node = this;
        while (node != NULL)
        {
            cout << node->value << endl;
            node = node->next;
        }
    }

    void insertFront(int value)
    {
        linkList *newNode = new linkList();
        newNode->value = this->value;
        newNode->next = this->next;

        this->value = value;
        this->next = newNode;

        size++;
    }
    void insert(int value)
    {
        linkList *node = this;
        while (node->next != NULL)
        {
            node = node->next;
        }
        node->next = new linkList();
        node->next->value = value;
        size++;
    }

    int deleteNode(int value)
    {
        linkList *node = this;
        linkList *prev = NULL;

        while (node != NULL && node->value != value)
        {
            prev = node;
            node = node->next;
        }

        if (node == NULL)
        {
            cout << "Not FOund\n";
            return 1;
        }

        prev->next = node->next;

        delete node;
        size--;
        return 0;
    }

    int getIndex(int value)
    {
        linkList *node = this;
        int index = 0;

        while (node != NULL)
        {
            if (node->value == value)
            {
                cout << index << " index\n";
                return 0;
            }

            node = node->next;
            index++;
        }
        return -1;
    }
    void getSize()
    {
        cout << "The size is: " << size << endl;
    }
    ~linkList()
    {
        delete next;
    }
};

int main()
{
    linkList *head = new linkList();

    head->value = 11;
    head->insert(1);
    head->insert(2);
    head->insert(3);
    head->insert(4);
    head->insert(5);
    head->insert(6);

    head->display();
    head->getSize();

    head->deleteNode(5);

    head->getIndex(4);

    head->display();
    head->getSize();

    return 0;
}