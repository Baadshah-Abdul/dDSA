#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct Book
{
    int id;
    string title;
    string author;
} Book;


void saveBooks(Book b[], int n)
{
    ofstream fout("books.txt");
    fout << n  << endl;
    for(int i = 0; i < n; i++)
    {
        fout << b[i].id << endl;
        fout << b[i].title << endl;
        fout << b[i].author << endl;
    }
}

int loadBooks(Book b[], int max)
{
    ifstream fin("books.txt");
    if(!fin)
    {
        cout <<"No saved books\n";
        return 0;
    }
    string line;

    getline(fin, line);
    int n = stoi(line);

    int loaded = 0;
    for(int i = 0; i < n && loaded < max; i++)
    {
        string idText, title, author;
        if(!getline(fin, idText))
            break;
        if(!getline(fin, title))
            break;
        if(!getline(fin, author))
            break;
        b[loaded].id = stoi(idText);
        b[loaded].title = title;
        b[loaded].author = author;
        loaded++;
    }
    fin.close();
    return loaded;
}

int main()
{
    Book books[3];
    for(int i = 0; i < 3; i++)
    {
        cout << "Book id:\n";
        cin >> books[i].id;
        cin.ignore(1000, '\n');
        cout << "Book title\n";
        getline(cin,books[i].title);
        cout << "Book author:\n";
        getline(cin, books[i].author);
    }
    saveBooks(books, 3);
    Book newbooks[3];
    loadBooks(newbooks, 3);
    for(int i = 0; i < 3; i++)
    {
        cout << "Book id:\n";
        cout << newbooks[i].id << endl;
        cout << "Book title\n";
        cout << newbooks[i].title << endl;
        cout << "Book author:\n";
        cout << newbooks[i].author << endl;
    }
    return 0;
}
