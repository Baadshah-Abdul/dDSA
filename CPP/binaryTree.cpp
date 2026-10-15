#include <iostream>

using namespace std;


class BinaryNode
{
    int data;
    BinaryNode *left;
    BinaryNode *right;

public:
    BinaryNode(int data)
    {
        this->data = data;
        left = right = nullptr;
    }

    void insert(int value)
    {
        if (value < this->data)
        {
            if (this->left == nullptr)
            {
                this->left = new BinaryNode(value);
            }
            else
            {
                this->left->insert(value);
            }
        }
        else
        {
            if (this->right == nullptr)
            {
                this->right = new BinaryNode(value);
            }
            else
            {
                this->right->insert(value);
            }
        }
    }

    void preOrder()
    {
        if (this == nullptr)
        {
            return;
        }
        cout << this->data << endl;
        this->left->preOrder();
        this->right->preOrder();
    }
    
    void inOrder()
    {
        if (this->left != nullptr)
        {
            this->left->inOrder();
        }
        cout << this->data << endl;

        if (this->right != nullptr)
        {
            this->right->inOrder();
        }
    }

    void search(int value)
    {
        if (this->data == value)
        {
            cout << "value found\n";
            return;
        }
        if (value < this->data)
        {
            if (this->left != nullptr)
            {
                this->left->search(value);
            }
            else
            {
                cout << "Value Not Found\n";
            }
        }
        else
        {
            if (this->right != nullptr)
            {
                this->right->search(value);
            }
            else
            {
                cout << "Value Not Found\n";
            }
        }
    }

    BinaryNode *del(int value)
    {

        if (value < this->data)
        {
            if (this->left != nullptr)
            {
                this->left = this->left->del(value);
            }
            else
            {
                cout << "Value Not Found\n";
            }
        }
        else if (value > this->data)
        {
            if (this->right != nullptr)
            {
                this->right = this->right->del(value);
            }
            else
            {
                cout << "Value Not Found\n";
            }
        }
        else
        {
            // 1. if leaf node(0 children)
            if (this->left == nullptr && this->right == nullptr)
            {
                delete this;
                return nullptr;
            }

            // 2. node with one child
            if (this->left == nullptr)
            {
                BinaryNode *temp = this->right;
                delete this;
                return temp;
            }
            else if (this->right == nullptr)
            {
                BinaryNode *temp = this->left;
                delete this;
                return temp;
            }

            // 3. node with 2 children
            BinaryNode *temp = this->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            this->data = temp->data;
            this->right = this->right->del(temp->data);
        }
        return this;
    }
};

int main()
{
    BinaryNode *root = new BinaryNode(1);

    root->insert(4);
    root->insert(5);
    root->insert(2);
    root->insert(3);
    root->inOrder();

    root->search(6);
    root->search(2);

    root->del(7);
    root->del(5);
    root->inOrder();
    cout << endl;
    root->del(2);
    root->inOrder();

    return 0;
}
