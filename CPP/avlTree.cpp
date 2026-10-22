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


    ~AVL()
    {
        delete left;
        delete right;
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

    AVL* del(int value)
    {
        //if value is smaller, go left
        if(value < this->data)
        {
            if(this->left != nullptr)
                this->left = this->left->del(value);
            //NOTE: do NOT return here; must fall through to rebalance on the way up
        }
        //if value is greater, go right
        else if(value > this->data)
        {
            if(this->right != nullptr)
                this->right = this->right->del(value);
            //NOTE: do NOT return here; must fall through to rebalance on the way up
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
                AVL *temp = this->left;
                this->left = this->right = nullptr;
                delete this;
                return temp;
            }
            if(this->left == nullptr && this->right != nullptr)
            {
                AVL *temp = this->right;
                this->left = this->right = nullptr;
                delete this;
                return temp;
            }
            //case 3
            if(this->left != nullptr && this->right != nullptr)
            {
                AVL *temp = this->left;
                while(temp->right != nullptr)
                {
                    temp = temp->right;
                }
                //save predecessor value BEFORE overwriting
                int predVal = temp->data;
                this->data = predVal;
                this->left  = this->left->del(predVal);
            }
        }

        //uppdate height
        this->height = this->heightNode();

        //balance factor
        int bf = this->balanceFactor();

        //child balance factors (used for delete; cannot compare with value anymore)
        int lb = this->left  ? this->left->balanceFactor()  : 0;
        int rb = this->right ? this->right->balanceFactor() : 0;

        //if imbalanced
        //case 1: LL
        if(bf > 1 && lb >= 0)
        {
            return this->Rrotation();
        }
        //case RR
        if(bf < -1 && rb <= 0)
        {
            return this->Lrotation();
        }
        //case LR
        if(bf > 1 && lb < 0)
        {
            this->left = this->left->Lrotation();
            return this->Rrotation();
        }
        //case RL
        if(bf < -1 && rb > 0)
        {
            this->right = this->right->Rrotation();
            return this->Lrotation();
        }
        return this;
    }


    int heightNode()
    {
        int hl = this->left ? this->left->height : 0;
        int hr  = this->right ? this->right->height : 0;
        return (hl > hr ? hl : hr) + 1;
    }

    int balanceFactor()
    {
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

    avl = avl->del(30);
    avl->inOrder();


    delete avl;

    return 0;
}
