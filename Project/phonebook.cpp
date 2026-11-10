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
        cout << c.name << " | " << (!c.countryCode.empty() ? c.countryCode : "") << " " << c.phone << " | " << (!c.email.empty() ? c.email : " - ") << " | " << (!c.city.empty() ? c.city : " - ") << endl;
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

    void insertKeepId(Contact c)
    {
        root = insertNode(root, c);
        count++;
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

        Node *temp = findDuplicate(root, c, 0);
        if(temp)
        {
            cout << "This contact already exists!\n";
            print(temp->data);
            return false;
        }
        insert(c);
        return true;

    }

    string pickContact(string text)
    {
        text = toLowerStr(trimStr(text));
        if(text.empty())
        {
            cout << "Phonebook empty!\n";
            return "";
        }

        if(count == 0)
            return  "";

        //counter and ptr for searching and storing
        int a = 0, b = 0;
        string* starts = new string[count];
        string* contains = new  string[count];

        collect(root, text, starts, a, contains, b);
        if(a+b == 0)
        {
            cout << "No Contacts Found!\n";
            delete[] starts;
            delete[] contains;
            return "";
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

        cout << "Select number (0 to cancel)\n";
        int option;
        cin >> option;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            delete[] starts;
            delete[] contains;
            return "";
        }
        cin.ignore(1000, '\n');

        if(option == 0)
        {
            delete[] starts;
            delete[] contains;
            return "";
        }
        if(option >= 1 &&  option <= a)
        {
            string chosen = starts[option - 1];
            delete[] starts;
            delete[] contains;
            return chosen;
        }
        if(option > a && option <= a+b)
        {
            string chosen = contains[option - a -1];
            delete[] starts;
            delete[] contains;
            return chosen;
        }

        delete[] starts;
        delete[] contains;
        return "";
    }

    void deleteContact(string text)
    {
        string key = pickContact(text);

        if(key == "")
            return;

        Node *temp = findNode(root, key);
        if(!temp)
            return;
        print(temp->data);
        cout << "Delete this contact? (y/n)\n";
        string answer;
        cin >> answer;
        cin.ignore(1000, '\n');

        if(answer == "y" || answer == "Y")
        {
            if(remove(key))
                cout << "Deleted\n";
        }
        else
        {
            cout << "Cancelled\n";
        }
    }



    void updateContact(string text)
    {
        string key = pickContact(text);
        if(key == "")
            return;
        Node *temp = findNode(root, key);
        if(temp == nullptr)
            return;
        print(temp->data);
        cout << "1. Name\n" << "2. Country code\n" << "3. Phone\n" << "4. Email\n" << "5. City\n" << "6. Cancel\n";
        int option;
        cin >> option;
        cin.ignore(1000, '\n');

        Contact copy = temp->data;

        string city;
        string email;
        string phone;
        string code;
        string name;
        switch(option)
        {
        case 1:
            cout << "Enter the Name:\n";
            getline(cin, name);
            name = trimStr(name);
            copy.name = name;
            break;

        case 2:
            cout << "Enter the Country code\n";
            getline(cin, code);
            code = digitsOnly(code);
            copy.countryCode = code;
            if(code.empty())
                copy.countryCode = "00";
            break;

        case 3:
            cout << "Enter the phone number\n";
            getline(cin, phone);
            phone = digitsOnly(phone);
            copy.phone = phone;
            break;

        case 4:
            cout << "Enter the email\n";
            getline(cin, email);
            email = trimStr(email);
            copy.email  = email;
            break;

        case 5:
            cout << "Enter the City:\n";
            getline(cin, city);
            city = trimStr(city);
            copy.city =  city;
            break;

        case  6:
            cout << "Cancelled\n";
            return;

        default:
            cout  << "Wrong Option\n";
            return;
        }

        if(cin.fail())
            return;

        if(copy.name.empty() || copy.phone.empty())
        {
            cout << "No entry without name or phone number allowed\n";
            return;
        }

        Node *dup = findDuplicate(root, copy, temp->data.id);
        if(dup)
        {
            cout << "Already in Phonebook\n";
            print(dup->data);
            return;
        }
        if(option == 1)
        {
            remove(key);
            insertKeepId(copy);
        }
        else
            temp->data = copy;

        cout << "Updated\n";
    }


    void saveNode(Node* n, ofstream &fout)
    {
        if(n == nullptr)
            return;

        fout << n->data.id << endl;
        fout << n->data.name << endl;
        fout << n->data.countryCode << endl;
        fout << n->data.phone << endl;
        fout << n->data.email << endl;
        fout << n->data.city << endl;

        saveNode(n->left, fout);
        saveNode(n->right, fout);
    }
    void savephonebook()
    {
        ofstream fout("phonebook.txt");
        fout << nextId << endl;
        fout << count << endl;
        saveNode(root, fout);
        fout.close();
    }

    int loadPhonebook()
    {
        ifstream fin("phonebook.txt");
        if(!fin)
        {
            cout << "No saved Contacts!\n";
            return 0;
        }

        int loaded = 0, maxId = 0, savedNextId = 0;

        try
        {
            string line;
            int cnt;
            getline(fin, line);
            int savedNextId = stoi(line);
            getline(fin, line);
            int n = stoi(line);

            for(int i = 0; i < n; i++)
            {
                string id, name, code, phone, email, city;
                if(!getline(fin, id))
                    break;
                if(!getline(fin, name))
                    break;
                if(!getline(fin, code))
                    break;
                if(!getline(fin, phone))
                    break;
                if(!getline(fin, email))
                    break;
                if(!getline(fin, city))
                    break;

                Contact c;
                c.id = stoi(id);
                c.name = name;
                c.countryCode = code;
                c.phone = phone;
                c.email = email;
                c.city = city;

                insertKeepId(c);
                loaded++;
                if(c.id > maxId)
                    maxId = c.id;
            }
        }
        catch(...)
        {
            cout << "saved file is damaged. Loaded " << loaded <<  " contact(s)\n";
        }
        fin.close();
        nextId = savedNextId;
        if(nextId <= maxId)
            nextId = maxId + 1;
        return loaded;
    }

    string readLine(string prompt)
    {
        string s;
        cout << prompt;
        getline(cin, s);
        return trimStr(s);
    }

    Contact askContact()
    {
        Contact c;
        c.name = readLine("Name: ");
        c.countryCode = digitsOnly(readLine("Country code: "));
        if(!c.countryCode.empty())
            c.countryCode = "00";
        c.phone = digitsOnly(readLine("Phone: "));
        c.email = readLine("Email: ");
        c.city = readLine("City: ");

        return c;
    }





};


int main()
{
    AVLTree t;
    Contact c;
    c.name="Ram Kumar";
    c.countryCode="91";
    c.phone="111";
    c.email="r@x.com";
    c.city="New Delhi";
    t.add(c);
    c.name="Amit";
    c.phone="222";
    c.countryCode = "";
    t.add(c);
    t.savephonebook();

    AVLTree t2;
    cout << "loaded: " << t2.loadPhonebook() << "\n";
    t2.display();
    c.name="Zara";
    c.phone="333";
    t2.add(c);   // must get ID 3, not 1 or 2
    t2.display();


}

