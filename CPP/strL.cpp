#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main()
{
    cout << "Enter your name:\n";

    string name;
    getline(cin, name);

    ofstream fout ("names.txt");

    fout << name << endl;

    fout.close();

    ifstream fin("names.txt");
    if(!fin)
    {
        cout  << "No saved Contacts\n";
        return 1;
    }


    string fname;
    getline(fin, fname);
    fin.close();
    
    cout << fname << endl;

    string prefix = "Ra";
    if(name.substr(0, prefix.length()) == prefix)
        cout << "match";
    else
        cout << "not match";

    return 0;

}
