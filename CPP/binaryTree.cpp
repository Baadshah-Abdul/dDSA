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
        else if(this->right  == nullptr)
        {
            this->right = new BinaryTree(value);
            return;
        }
        else
        {
            if(left->countNodes() <= right->countNodes())
            {
                left->insert(value);
            }
            else
            {
                right->insert(value);
            }
        }
                
    } 

    BinaryTree* del(int value)
    {
        if(this == nullptr)
        {
            return nullptr;
        }
        if(this->data == value)
        {
            //case 1- leasf node
            if(this->left ==nullptr && this->right == nullptr)
            {
                delete this;
                return nullptr;
            }
            //case 2 - one child
            if(this->left !=nullptr && this->right == nullptr)
            {
                BinaryTree *temp = this->left;
                delete this;
                return  temp;
            }
            if(this->left == nullptr && this->right != nullptr)
            {
                BinaryTree *temp = this->right;
                delete this;
                return  temp;
            }

            //case 3- 2 children
            if(this->left != nullptr && this->right != nullptr)
            {
                //replacement value;
                BinaryTree *temp = this->left;
                while(temp->right != nullptr)
                {
                    temp = temp->right;
                }
                //replace value
                this->data = temp->data;
                //delete the node of replaced value 
                this->left = this->left->del(this->data);
                return this;
            }

        }//search if not found
             if(this->left != nullptr)
            {
                this->left = this->left->del(value);
            }
            if(this->right != nullptr)
            {
                this->right = this->right->del(value);
            }
            return this;

    }

    int countNodes()
    {
        if(this == nullptr)
            return 0;
        return (left->countNodes() + right->countNodes() + 1);
    }

    int height()
    {
        if(this == nullptr)
        {
            return 0;
        }
        int x = this->left->height();
        int y = this->right->height();
        return x > y ? x+1 : y+1;
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
    bt->insert(35);
    bt->insert(67);
    bt->insert(93);
    bt->insert(2);
    bt->inOrder();

    bt = bt->del(40);
    bt->inOrder();
    
    cout << bt->countNodes() << endl;
    cout << bt->height() << endl;
    
     
    return 0;
} 



