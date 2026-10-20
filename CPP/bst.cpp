#include <iostream>

using namespace std;

class BST
{
    public: 
        int data;
        BST *left;
        BST *right;

        BST(int value)
        {
            this->data = value;
            this->left = this->right = nullptr;
        }

        void insert(int value)
        {
            if(value < this->data)
            {
                if(this->left == nullptr)
                {
                    this->left = new  BST(value);
                    return;
                }
                else
                {
                    left->insert(value);
                }
            }
            if(value > this->data)
            {
                if(this->right == nullptr)
                {
                    this->right = new BST(value);
                    return;
                }
                else
                {
                    this->right->insert(value);
                }
            }
        }

        BST* del(int value)
        {
            if(this == nullptr) return nullptr;           

            if(value < this->data)
            {
                if(this->left != nullptr)
                    this->left = this->left->del(value);
                return this;
            }
            else if(value > this->data)
            {
               if(this->right != nullptr)
                    this->right = this->right->del(value);
                return this;
            }
            else
            {
                //case leaf node
                if(this->left == nullptr && this->right == nullptr)
                {
                    delete this;
                    return nullptr;
                }
                //case onme child
                if(this->left != nullptr && this->right == nullptr)
                {
                    BST *temp = this->left;
                    delete this;
                    return temp;
                }
                if(this->left == nullptr && this->right != nullptr)
                {
                    BST *temp = this->right;
                    delete this;
                    return temp;
                }
                //case 3
                if(this->left != nullptr && this->right != nullptr)
                {
                    BST *temp = this->left;
                    while(temp->right != nullptr)
                    {
                        temp = temp->right;
                    }
                    this->data = temp->data;
                    this->left  = this->left->del(this->data);
                    return this;
                }
            }
        }

        BST* iSearch(int value)
        {
            BST *temp = this;

            while(temp != nullptr)
            {
                if(temp->data == value)
                {
                    cout << "Found search(i)\n";
                    return temp;
                }

                else if(value < temp->data)
                {
                    temp = temp->left;
                }
                else
                {
                    temp  = temp->right;
                }
            }
            cout << "NOT Found search(i)\n";
            return nullptr;
        }

        BST* rSearch(int value)
        {
            if(this == nullptr)
            {
                cout << "Not Found search(r)\n";
                return nullptr;
            }
            if(this->data == value)
            {
                cout << "Found search(r)\n";
                return this;
            }
            else if(this->data > value)
            {
                if (this->left == nullptr)
                {
                    cout << "Not Found search(r)\n";
                    return nullptr; 
                }
                return this->left->rSearch(value);            }
            else
            {
                if (this->right == nullptr)
                {
                    cout << "Not Found search(r)\n";
                    return nullptr; 
                }

                return this->right->rSearch(value);
            }
        }

        void inOrder()
        {
            if(this->left != nullptr)
            {
                this->left->inOrder();
            }
            cout << this->data << endl;
            if(this->right != nullptr)
            {
                this->right->inOrder();
            }
        }

};

int main()
{
    BST *bst = new BST(45);

    bst->insert(34);
    bst->insert(78);
    bst->insert(23);
    bst->insert(44);
    bst->insert(34);
    bst->insert(32);
    bst->insert(55);
    bst->inOrder();
    bst->rSearch(34);

    return 0;
}
