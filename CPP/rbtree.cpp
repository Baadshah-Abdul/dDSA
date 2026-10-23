#include < iostream>

using namespace std;

class RBT
{
    int data;
    //black: 0, red: 1
    int color;
    RBT *left;
    RBT *right;

    RBT(int value)
    {
        this->color = 0;
        this->data =  value;
        this->left = this->right = nullptr;
    }

    RBT* insert(int  value);

    RBT* del(int value);

    RBT* Rrotation();

    RBT* Lrotation();

    void inOrder();
    void preOrder();
    void postOrder();

};
