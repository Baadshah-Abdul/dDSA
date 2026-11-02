#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

typedef struct Contact
{
    int id;
    string name;
    string countryCode;
    string phone;
    string email;
    string city;
} Contact;

//for key balancing
const char JOINER = '\x01';

string toLowerStr(string s)
{
    string result= "";
    for(char c : s)
    {
        result += tolower(c);
    }
    return result;
}

string trimStr(string s)
{

    size_t f =  s.find_first_not_of(' ');
    if(f == string::npos)
        return "";

    size_t l = s.find_last_not_of(' ');
    l = (l - f + 1);

    return s.substr(f, l);

}


string digitsOnly(string s)
{
    string result;
    for(char c : s)
    {
        if(isdigit(static_cast<unsigned char>(c)))
            result += c;
    }
    return result;
}

string makeKey(string name, int id)
{
    if(name.empty())
        return "";

    string key = toLowerStr(name);
    string idstr = to_string(id);
    while(idstr.length() < 6)
        idstr = "0" + idstr;

    return key + JOINER + idstr;
}

class Node
{
public:
    Contact data;
    string key;
    int height;
    Node *left;
    Node *right;

    Node(const Contact &c) : data(c)
    {
        key = makeKey(c.name, c.id);
        this->height = 1;
        this->left = this->right = nullptr;
    }
};


class AVLTree
{
private:
    Node *root;
    int nextId;
    int count;


    int updateHeight(Node* n)
    {
        int hl = n->left ? n->left->height : 0;
        int hr = n->right ? n->right->height:  0;
        return (hl > hr ? hl : hr) +1;
    }

    int balanceFactor(Node* n)
    {
        if(n == nullptr)
            return 0;

        int hl = n->left ? n->left->height : 0;
        int hr = n->right ? n->right->height:  0;
        return hl - hr;

    }

    Node* rotateRight(Node* n)
    {
        //left child and left child's right
        Node *lc = n->left;
        Node *lcr = n->left->right;
        //assign values
        lc->right = n;
        n->left = lcr;
        n->height = updateHeight(n);
        lc->height = updateHeight(lc);
        return lc;
    }

    Node* rotateLeft(Node* n)
    {
        //right child and right childs left
        Node *rc = n->right;
        Node *rcl = n->right->left;
        //assign values
        rc->left =  n;
        n->right = rcl;
        n->height = updateHeight(n);
        rc->height = updateHeight(rc);
        return rc;
    }

    Node* rebalance(Node* n)
    {
        //upodate height
        n->height = updateHeight(n);

        //balance factor
        int bf = balanceFactor(n);
        int bflc = balanceFactor(n->left);
        int bfrc =balanceFactor(n->right);

        //balance tree
        //case 1: LL
        if(bf > 1 && bflc >= 0)
            return rotateRight(n);
        //case 2: RR
        if(bf  < -1 && bfrc <= 0)
            return rotateLeft(n);
        //case 3: LR
        if(bf  > 1 && bflc < 0)
        {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        //case 4: RL
        if(bf < -1 && bfrc > 0)
        {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insertNode(Node* n, Contact c)
    {
        string value = makeKey(c.name, c.id);

        if(n == nullptr)
        {
            return new Node(c);
        }
        if(n->key > value)
        {
            if(n->left == nullptr)
            {
                n->left = new Node(c);
            }
            else
            {
                n->left = insertNode(n->left, c);
            }
        }
        else if(n->key  < value)
        {
            if(n->right == nullptr)
            {
                n->right = new Node(c);
            }
            else
            {
                n->right = insertNode(n->right, c);
            }
        }
        else
            return n;

        return rebalance(n);
    }

    void inorder(Node* n)
    {
        if(n ==  nullptr)
            return;

        if(n->left != nullptr)
        {
            inorder(n->left);
        }
        cout << n->data.id << "|" << n->data.name <<"| +" << n->data.countryCode << " " << n->data.phone <<"|" << n->data.email << "|" << n->data.city << endl;
        if(n->right != nullptr)
        {
            inorder(n->right);
        }
    }

    Node* deleteNode(Node* n, string key, bool &deleted)
    {
        if(n == nullptr)
        {
            return 0;
        }

        if(n->key > key)
        {
            n->left = deleteNode(n->left, key, deleted);
        }
        else if(n->key < key)
        {
            n->right = deleteNode(n->right, key, deleted);
        }
        else
        {
            //case leaf node
            if(n->left ==nullptr && n->right == nullptr)
            {
                delete n;
                deleted = true;
                return nullptr;
            }
            //case 1 child
            if(n->left != nullptr && n->right == nullptr)
            {
                Node *temp = n->left;
                delete n;
                deleted = true;
                return temp;
            }
            if(n->left == nullptr && n->right != nullptr)
            {
                Node *temp = n->right;
                delete n;
                deleted = true;
                return temp;
            }
            //case 2 children
            if(n->left != nullptr && n->right != nullptr)
            {
                Node  *temp = n->left;
                while(temp->right != nullptr)
                {
                    temp = temp->right;
                }
                //save
                Contact c = temp->data;
                string predecessorKey = temp->key;
                n->data = c;
                n->key = temp->key;
                n->left = deleteNode(n->left, predecessorKey, deleted);
            }
        }
        return rebalance(n);
    }
    void destroy(Node* n)
    {
        if(n ==  nullptr)
            return;

        if(n->left != nullptr)
        {
            destroy(n->left);
        }
        if(n->right != nullptr)
        {
            destroy(n->right);
        }
        delete n;
    }



public:
    AVLTree()
    {
        root = nullptr;
        nextId= 1;
        count = 0;
    }

    ~AVLTree()
    {
        destroy(root);
    }

    void insert(Contact c)
    {
        c.id = nextId;
        nextId++;
        root = insertNode(root, c);
        count++;
    }

    void display()
    {
        inorder(root);
    }

    int getHeight()
    {
        return root ? root->height: 0;
    }

    bool remove(string key)
    {
        bool deleted = false;
        root = deleteNode(root, key, deleted);
        if(deleted)
            count--;
        return deleted;
    }

    int collect(Node* n,string text, string* contains, int a, string* contains, int b);


    void search(string text)
    {
        
        text = toLowerStr(trimStr(text));
        if(text)
        {
            cout << "Please Enter a Name:\n";
            return;
        }
        if(count == 0)
        {
            cout << "Phonebook Empty!\n";
            return;
        }

        string* starts = new string[count];
        string* contains = new  string][count];
    }



};


int main()
{
    AVLTree t;
    string names[] = {"Amit", "Bina", "Charu", "Dev", "Esha", "Farhan", "Gita"};
    for (string n : names)
    {
        Contact c;
        c.name = n;
        t.insert(c);
    }

    cout << "--- Delete Dev (root, two children) ---\n";
    cout << "returned: " << t.remove(makeKey("Dev", 4)) << "\n";
    t.display();
    cout << "Height: " << t.getHeight() << "\n";

    cout << "\n--- Delete missing key ---\n";
    cout << "returned (expect 0): " << t.remove(makeKey("Zara", 99)) << "\n";

    cout << "\n--- Delete leaf Amit ---\n";
    cout << "returned: " << t.remove(makeKey("Amit", 1)) << "\n";
    t.display();

    cout << "\n--- Delete Gita, Farhan, Esha (forces a rotation) ---\n";
    t.remove(makeKey("Gita", 7));
    t.remove(makeKey("Farhan", 6));
    t.remove(makeKey("Esha", 5));
    t.display();
    cout << "Height: " << t.getHeight() << "\n";
    return 0;
}
