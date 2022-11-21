// Contains the 'fragment' functions
// CHANGES: 'filesystem' -> 'experimental/filesystem'
#include "utils.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <experimental/filesystem> // remove(), rename()

namespace fs = std::experimental::filesystem;

using fs::remove;
using fs::rename;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::noskipws;
using std::ofstream;
using std::string;
using std::ws;

extern const string dir = ".\\files\\"; // avoids var. duplication
extern string keyContainer;

void decrypt(string &fileName)
{
    ifstream fin;
    ofstream fout;
    char chars;

    fin.open(dir + fileName);
    fout.open(dir + "tmp.txt");

    // file decryption
    if (fin.is_open() && fout.is_open())
    {
        while (fin >> noskipws >> chars) // place content on a temp file
        {
            chars -= 69; // minus 69 to every character including spaces
            fout << chars;
        }
        fin.close();
        fout.close();
    }

    fin.open(dir + "tmp.txt");
    fout.open(dir + fileName);

    if (fin.is_open() && fout.is_open()) // put back the decrypted content of the temp file on the source file
    {
        while (fin >> noskipws >> chars)
        {
            chars -= 69;
            fout << chars;
        }
    }
    fin.close();
    fout.close();

    remove(dir + "tmp.txt"); // deletes the tmp file
}

void encrypt(string &fileName)
{
    ifstream fin;
    ofstream fout;
    char chars;

    fin.open(dir + fileName);
    fout.open(dir + "tmp.txt");

    // file encryption
    if (fin.is_open() && fout.is_open())
    {
        while (fin >> noskipws >> chars) // place content on a temp file
        {
            chars += 69; // adds 69 to every character including spaces
            fout << chars;
        }
        fin.close();
        fout.close();
    }

    fin.open(dir + "tmp.txt");
    fout.open(dir + fileName);

    if (fin.is_open() && fout.is_open()) // put back the encrypted content of the temp file on the source file
    {
        while (fin >> noskipws >> chars)
        {
            chars += 69;
            fout << chars;
        }
    }
    fin.close();
    fout.close();

    remove(dir + "tmp.txt"); // deletes the tmp file
}

bool isTxt(string &fileName) // BUG: '.txtX', 'X' = any chars is allowed
{
    string dotTxt = ".txt";

    if (fileName.find(dotTxt) != string::npos)
        return true;
    else
        return false;
}

string inputUserName(ofstream &fout)
{
    string username = "";

    cout << "Input username/email : ";
    getline(cin >> ws, username);

    return username;
}

string inputPassword(ofstream &fout)
{
    string password = "";

    cout << "Input password : ";
    cin >> password;

    return password;
}

void inputFilename(string &fileName, int &i, int &count) // get filename
{
    cout << "[NOTICE] : Filename must end with '.txt'.\n\n";

    if (count > 1)
    {
        cout << "[" << i + 1 << "] Input container name :\n> ";
        getline(cin >> ws, fileName);
    }
    else
    {
        cout << "Input container name :\n> ";
        getline(cin >> ws, fileName);
    }
}

int how_many_to(const string &mode) // modes : add, update, delete
{
    int passCount;
    cout << "~ Password Vault ~\n\n";
    cout << "How many passwords to " << mode << "?\n> ";
    cin >> passCount;
    cin.clear();
    cin.ignore();

    return passCount;
}

void arg_update(string &fileName, string &mode) // mode: username, password, both
{
    ifstream fin;
    ofstream fout;
    string tag = "", data = "", oldData = "", newData = ""; // "tag"(Username: & Password:) - "data"(username & password)
    string tmp = "temporary.txt";
    string fName = ".\\files\\temporary.txt";

    decrypt(fileName);

    if (isTxt(fileName) == true) // <- checks if file ends w/ '.txt'. BUG: '.txtX', 'X' = any chars is alloweds
    {
        fin.open(dir + fileName, ios::in);
        fout.open(dir + tmp, ios::out);
    }
    else
    {
        cerr << "\nFilename must end with '.txt'.\n";
        system("pause");
        return;
    }

    if (fin.is_open() && fout.is_open())
    {
        system("cls");
        cout << "Enter old " << mode << " :\n> ";
        getline(cin >> ws, oldData);
        cout << "\nEnter new " << mode << " :\n> ";
        getline(cin >> ws, newData);

        while (fin >> tag >> data)
        {
            if (data == oldData) // replace old data with new data
                fout << tag << ' ' << newData << endl;

            else
                fout << tag << ' ' << data << endl;
        }
    }
    else
    {
        cerr << "Can't open file!\n";
        system("pause");
    }
    cerr << "\nSession finished!\n";
    system("pause");
    fin.close();
    fout.close();

    remove(dir + fileName);
    rename(dir + tmp, dir + fileName);
    encrypt(fileName);
}

void arg_update(string &fileName, string &mode, string &altMode) // overload of arg_update()
{
    ifstream fin;
    ofstream fout;
    string tag = "", data = "", newUser = "", newPass = ""; // "tag"(Username: & Password:) - "data"(username & password)
    string tmp = "temporary.txt";
    string fName = ".\\files\\temporary.txt";

    decrypt(fileName);

    if (isTxt(fileName) == true && fileName != keyContainer) // <- checks if file ends w/ '.txt'. BUG: '.txtX', 'X' = any chars is alloweds
    {
        fout.open(dir + tmp, ios::out);
    }
    else
    {
        cout << "\nFilename must end with '.txt'.\n";
        system("pause");
        return;
    }

    if (fout.is_open())
    {
        system("cls");
        cout << "~Password Vault~\n\n";

        cout << "Enter new " << mode << " :\n> ";
        getline(cin >> ws, newUser);

        cout << "\n-------------------------------------\n\n";

        cout << "Enter new " << altMode << " :\n> ";
        getline(cin >> ws, newPass);

        cout << endl;
        fout << "Username: " << newUser << "\nPassword: " << newPass << '\n'; // place username & password in a container
    }
    else
    {
        cerr << "Can't open file!\n";
        system("pause");
    }
    cerr << "\nSession finished!\n";
    system("pause");
    fout.close();

    remove(dir + fileName);
    rename(dir + tmp, dir + fileName);
    encrypt(fileName);
}

bool login()
{
    ifstream fin;
    string tmp, key;

    decrypt(keyContainer);

    cout << "Vault Key : ";
    cin >> key;
    fin.open(dir + keyContainer);
    fin >> tmp;

    if (key == tmp)
    {
        encrypt(keyContainer);
        return true;
    }
    else
    {
        encrypt(keyContainer);
        return false;
    }
}

void home() // notice
{
    system("cls");
    cout << "~ PASSWORD VAULT ~\n\n";
    cout << "[Your personal password keeper :D]\n\n";
    cout << "[NOTE: Please close another instance of this program (if there's any) before proceeding.]\n";
    system("pause");
}
