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

    //for displaying data
    void print(Contact c)
    {
        cout << c.id << "|" << c.name <<"| +" << c.countryCode << " " << c.phone <<"|" << c.email << "|" << c.city << endl;
    }

    void inorder(Node* n)
    {
        if(n ==  nullptr)
            return;

        if(n->left != nullptr)
        {
            inorder(n->left);
        }

        print(n->data);

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

    void collect(Node* n,string text, string* starts, int &a, string* contains, int &b)
    {
        if(n == nullptr)
            return;
        if(text.empty())
            return;

        //left node
        collect(n->left, text, starts, a, contains, b);

        //name in node
        string name = toLowerStr(n->data.name);

        //check if matches
        size_t f = name.find(text);
        if(f == 0)
        {
            starts[a++] = n->key;
        }
        else if(f != string::npos)
        {
            contains[b++] = n->key;
        }


        //right node
        collect(n->right, text, starts, a, contains, b);
    }

    Node* findNode(Node* n, string key)
    {
        if(n ==  nullptr)
            return nullptr;
        if(n->key > key)
            return findNode(n->left, key);
        if(n->key < key)
            return findNode(n->right, key);
        return n;
    }

    bool sameCode(string a, string b)
    {
        if(a == b || a == "00" || b == "00")
            return true;
        return false;
    }

    bool sameContact(Contact x, Contact y)
    {
        string xname = toLowerStr(x.name);
        string xemail = toLowerStr(x.email);
        string xcity = toLowerStr(x.city);

        string yname = toLowerStr(y.name);
        string yemail = toLowerStr(y.email);
        string ycity = toLowerStr(y.city);

        if(xname == yname && xemail == yemail && xcity == ycity && x.phone == y.phone && sameCode(x.countryCode, y.countryCode))
            return true;

        return false;
    }



    Node* findDuplicate(Node* n, Contact c, int skipId)
    {
        if(n == nullptr)
            return nullptr;

        string prefix = toLowerStr(c.name) + JOINER;

        string head = n->key.substr(0, prefix.length());
        if(prefix == head)
        {
            if(sameContact(n->data, c) && n->data.id != skipId)
                return n;

            Node *r = findDuplicate(n->left, c, skipId);
            if(r)
                return  r;
            return findDuplicate(n->right, c, skipId);

        }
        if(prefix < head)
        {
            return findDuplicate(n->left, c, skipId);
        }
        if(prefix > head)
        {
            return findDuplicate(n->right, c, skipId);
        }
        return n;

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

    void search(string text)
    {
        //check usr input
        text = toLowerStr(trimStr(text));
        if(text.empty())
        {
            cout << "Please enter a Name:\n";
            return;
        }
        if(count == 0)
        {
            cout << "Phonebook Empty!\n";
            return;
        }

        //counter and ptr for searching and storing
        int a = 0, b = 0;
        string* starts = new string[count];
        string* contains = new  string[count];

        collect(root, text, starts, a, contains, b);

        //print only when there
        if(a+b == 0)
        {
            cout << "No Contacts Found!\n";
            delete[] starts;
            delete[] contains;
            return;
        }

        if(a > 0)
        {
            cout <<  "Names starting with " << text << endl;

            for(int i = 0;  i < a; i++)
            {
                Node *temp = findNode(root, starts[i]);
                cout << (i + 1) << ". ";
                if(temp)
                    print(temp->data);
            }
        }
        if(b > 0)
        {
            cout <<  "Names containing " << text << endl;
            for(int i = 0;  i < b; i++)
            {
                Node *temp = findNode(root, contains[i]);
                cout << (a + i + 1) << ". ";
                if(temp)
                    print(temp->data);
            }
        }

        delete[] starts;
        delete[] contains;

    }


    bool add(Contact c)
    {
        if(!c.name.empty())
        {
            c.name = trimStr(c.name);
        }
        else
        {
            cout << "Enter name!\n";
            return false;
        }
        if(!c.phone.empty())
        {
            c.phone = digitsOnly(c.phone);
        }
        else
        {
            cout << "Enter a phone number!\n";
            return false;
        }
        c.city =  trimStr(c.city);
        c.email = trimStr(c.email);
        if(!c.countryCode.empty())
        {
            c.countryCode =  digitsOnly(c.countryCode);
        }
        else
        {
            c.countryCode = "00";
        }

        if(findDuplicate(root, c, 0))
        {
            print(c);
            return false;
        }
        insert(c);
        return true;

    }

    int pickContact(string text)
    {

    }

};


int main()
{
    AVLTree t;
    string names[] = {"Rahul", "Rajesh", "ram", "Ram Kumar", "Amit Rao",
                      "Arun", "Kiran", "Priya", "Sridhar", "Amit"
                     };
    for (string n : names)
    {
        Contact c;
        c.name = n;
        t.insert(c);
    }

    cout << "--- search R ---\n";
    t.search("R");
    cout << "\n--- search r (must be identical) ---\n";
    t.search("r");
    cout << "\n--- search zzz ---\n";
    t.search("zzz");
    cout << "\n--- empty search ---\n";
    t.search("   ");

    Contact c;
    c.name="Rahul";
    c.countryCode="91";
    c.phone="9876543210";
    c.email="abd@mail.com";
    c.city="Delhi";
    t.add(c);

    c.name="RAHUL";
    c.countryCode="+91";
    c.phone="98765-43210";
    c.email="ABD@MAIL.COM";
    c.city="delhi";
    cout << "expect 0: " << t.add(c) << "\n";

    c.countryCode="1";
    cout << "expect 1: " << t.add(c) << "\n";
    c.countryCode="00";
    cout << "expect 0: " << t.add(c) << "\n";
    c.countryCode="91";
    c.city="Pune";
    cout << "expect 1: " << t.add(c) << "\n";

    return 0;
}
