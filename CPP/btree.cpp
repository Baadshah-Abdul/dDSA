#include <iostream>

using namespace std;

#define MAX 4

typedef struct Node
{
    int keys[MAX-1];
    Node* children[MAX];
    int numKeys;
    bool isLeaf;
    Node(bool leaf = true)
    {
        isLeaf = leaf;
        numKeys = 0;
        for(int i = 0; i < MAX-1; i++)
        {
            keys[i] = 0;
        }
        for(int i = 0; i < MAX; i++)
        {
            children[i] = nullptr;
        }
    }
} Node;


class Btree
{
    Node *root;

    Node *search(Node *n, int key)
    {
        if(n == nullptr)
            return nullptr;

        int i = 0;
        //index: find where key < or > keys[i]
        while(i < n->numKeys && key >  n->keys[i])
            i++;
        //found
        if(i < n->numKeys && key == n->keys[i])
            return n;
        //search next branch
        if(n->isLeaf != true)
            return search(n->children[i], key);
        //leaf node  reached
        return nullptr;
    }


    //inorder
    void traverse(Node* n)
    {
        if(n == nullptr)
            return;
        int i = 0;
        while(i < n->numKeys)
        {
            traverse(n->children[i]);
            cout << n->keys[i] << endl;
            i++;
        }
        traverse(n->children[n->numKeys]);
    }


public:
    Btree()
    {
        root = nullptr;
    }

    void splitChild(Node* parent, int childIndex, Node* fullChild)
    {
        int mid =  MAX/2;
        //create new node for 2nd half
        Node* r = new Node(fullChild->isLeaf);
        r->numKeys = mid - 1;
        //copy 2nd hlf frm fullChild to r
        for(int j = 0; j < mid -1; j++)
            r->keys[j] = fullChild->keys[j+mid];

        //not leaf, thenm copy rest childptr
        if(fullChild->isLeaf == false)
        {
            for(int j = 0; j  < mid; j++)
                r->children[j] = fullChild->children[j+mid];
        }

        //reduce keycount of fullChild
        fullChild->numKeys = mid - 1;

        //shift children to make room for new child r
        for(int j  = parent->numKeys; j >= childIndex; j--)
            parent->children[j+1] = parent->children[j];
        parent->children[childIndex+1] = r;

        //shift parent keys for key frm Fullchild
        for(int j = parent->numKeys - 1; j >= childIndex; j--)
            parent->keys[j + 1] =  parent->keys[j];

        //mv key of fullchild to parent
        parent->keys[childIndex] = fullChild->keys[mid -1];

        parent->numKeys++;
    }

    void insertNonFull(Node* n, int key)
    {
        int keyIndex = n->numKeys - 1;

        if(n->isLeaf)
        {
            //case 1: leaf node
            while( keyIndex >=  0 && n->keys[keyIndex]  > key)
            {
                n->keys[keyIndex+1] = n->keys[keyIndex];
                keyIndex--;
            }
            //insert new key in sorted posotion
            n->keys[keyIndex+1] = key;
            n->numKeys++;
        }

        else
        {
            //case 2: internal node
            //which child to decend intop
            while(keyIndex >= 0 && n->keys[keyIndex] > key)
                keyIndex--;

            keyIndex++; //index of child

            //check if child full
            if(n->children[keyIndex]->numKeys == MAX-1)
            {
                splitChild(n, keyIndex, n->children[keyIndex]);
                //check new key for left or right
                if(n->keys[keyIndex] < key)
                    keyIndex++;
            }
            //insert into non fullchild
            insertNonFull(n->children[keyIndex], key);
        }

    }

    void insert(int key)
    {
        //empty
        if(root == nullptr)
        {
            root = new Node(true);
            root->keys[0] = key;
            root->numKeys = 1;
            return;
        }

        //root full
        if(root->numKeys == MAX-1)
        {
            Node *temp = new Node(false);
            //old root new node child
            temp->children[0] = root;
            //split old root and move key up
            splitChild(temp, 0, root);

            //for new key which child
            int i = 0;
            if(temp->keys[0] < key)
                i++;
            insertNonFull(temp->children[i], key);

            //update root ptr
            root =  temp;
        }
        //root not full
        else
        {
            insertNonFull(root, key);
        }
    }

    void printTree()
    {
        if(root != nullptr)
            traverse(root);
        cout << endl;
    }

    bool searchKey(int key)
    {
        return search(root, key) !=  nullptr;
    }
};

int main()
{
    Btree t;

    // Insert keys into the B-Tree
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for(int k : keys)
    {
        t.insert(k);
    }

    cout << "Traversal of the constructed B-Tree (Sorted order): \n";
    t.printTree();
    // Test searching
    int searchVal = 6;
    if(t.searchKey(searchVal))
        cout << "Key " << searchVal << " found in the B-Tree.\n";
    else
        cout << "Key " << searchVal << " not found.\n";
    return 0;
}
