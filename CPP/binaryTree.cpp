#include <iostream>

using namespace std;

class BinaryTree
{
    int data;
    BinaryTree  *left;
    BinaryTree *right;

public:      
    BinaryTree(int value)
    {
       
        data = value;
        left = right = nullptr;
    }
 

    void insert(int value)
    {
        if(this->left == nullptr)
        {
            this->left = new BinaryTree(value);
            return;
        }
        if(this->left != nullptr && this->right  == nullptr)
        {
            this->right = new BinaryTree(value);
            return;
        }
        else
        {
            this->left->insert(value);
        }
    } 

    int countNodes()
    {
        int x, y;
        if(this != nullptr)
        {
            x = this->left->countNodes();
            y = this->right->countNodes();
            return (x+y+1);
        }
        return 0;
    }

    int height()
    {
        int x=0, y=0;
        if(this == nullptr)
        {
            return 0;
        }
        x = this->left->height();
        y = this->right->height();
    
        if(x > y) 
        {
            return x+1;
        }
        return y+1;
    }

    void inOrder()
    {
        if(this->left != nullptr)
        {
            this->left->inOrder();
        }
        cout << this->data  << endl;
        if(this->right != nullptr)
        {
            this->right->inOrder();
        }
    }  
    void preOrder()
    {
        cout << this->data  << endl;
        if(this->left != nullptr)
        {
            this->left->preOrder();
        }
        if(this->right != nullptr)
        {
            this->right->preOrder();
        }
    } 
    void postOrder()
    {
        if(this->left != nullptr)
        {
            this->left->postOrder();
        }
        if(this->right != nullptr)
        {
            this->right->postOrder();
        }
        cout << this->data  << endl;
    } 
};


int main()
{
    BinaryTree *bt = new BinaryTree(40);

    bt->insert(10);
    bt->insert(32);
    bt->inOrder();
    
    cout << bt->countNodes() << endl;
    cout << bt->height() << endl;
     
    return 0;
} 



