#include <iostream>

using namespace std;

class AVL
{
public:
    int data;
    int height;
    AVL *left;
    AVL *right;

    AVL(int value)
    {
        this->data = value;
        this->height = 1;
        left = right = nullptr;
    }


    AVL* insert(int  value)
    {
        if(this->data > value)
        {
            if(this->left == nullptr)
            {
                this->left = new AVL(value);
            }
            else
            {
                this->left = this->left->insert(value);
            }
        }
        else if(this->data < value)
        {
            if(this->right == nullptr)
            {
                this->right = new AVL(value);
            }
            else
            {
                this->right = this->right->insert(value);
            }
        }  
        else
            return this;

        //uppdate height of new node
        //check if children exist;
        //int hl = this->left ? this->left->height : 0;
        //int hr  = this->right ? this->right->height : 0;
        //this->height = (hl > hr ? hl : hr) + 1;
        this->height = this->heightNode();

        //balance factor
        int bf = this->balanceFactor();

        //if imbalanced
        //case 1: LL
        if(bf > 1 && value < this->left->data)
        {
            return this->Rrotation();
        }
        //case RR
        if(bf < -1 && value > this->right->data)
        {
            return this->Lrotation();
        }
        //case LR
        if(bf > 1 && value > this->left->data)
        {
            this->left = this->left->Lrotation();
            return this->Rrotation();
        }
        //case RL
        if(bf < -1 && value < this->right->data)
        {
            this->right = this->right->Rrotation();
            return this->Lrotation();
        } 
        return this;
    }

    AVL* Rrotation()
    {
        //leftchild & leftchilds->rightchild
        AVL *lc = this->left;
        AVL *lcr = this->left->right;
        //assign
        lc->right = this;
        this->left = lcr;
        this->height = this->heightNode();
        lc->height = lc->heightNode();

        return lc;
    }
    
    AVL* Lrotation()
    {
        //rightchild & rightchilds left child
        AVL *rc = this->right;
        AVL *rcl = this->right->left;
        //assign
        rc->left = this;
        this->right = rcl;
        this->height = this->heightNode();
        rc->height = rc->heightNode();

        return rc;
    }

    int heightNode()
    {
        int hl = this->left ? this->left->height : 0;
        int hr  = this->right ? this->right->height : 0;
        return (hl > hr ? hl : hr) + 1;
    }

    int balanceFactor()
    {
       if(this == nullptr)
       {
           return 0;
       }
       int hl = this->left ? this->left->height : 0;
       int hr  = this->right ? this->right->height : 0;

       return hl - hr;
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
};

int main()
{
    AVL *avl = new AVL(2);

    avl = avl->insert(10);
    avl = avl->insert(20);
    avl = avl->insert(30);
    avl = avl->insert(40);
    avl = avl->insert(50);
    avl->inOrder();
    return 0;
}


