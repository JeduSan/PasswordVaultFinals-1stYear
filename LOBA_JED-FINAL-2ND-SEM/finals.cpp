// Contains the 'merged' function
#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem> // directory_iterator()
#include "finals.h"
#include "utils.h"

namespace fs = std::experimental::filesystem;

using fs::directory_iterator;
using fs::remove;
using fs::rename;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

const string dir = ".\\files\\";
string keyContainer = "zDO_NOT_DELETE.txt";

void addPass(string &fileName, ofstream &fout, int &count)
{
    ifstream fin;

    for (int i = 0; i < count; i++)
    {
        system("cls");
        cout << "[NOTICE] : Only one set of username & password per container is allowed.\n";

        inputFilename(fileName, i, count);
        // fileName != keyContainer to prevent user from accessing the password container
        if (isTxt(fileName) == true && fileName != keyContainer) // <- checks if file ends w/ '.txt'.
            fout.open(dir + fileName);                           // <- puts file in 'files' folder
        else
        {
            cerr << "\nError Creating File, Please Try Again!\n";
            system("pause");
            continue;
        }

        if (fout.is_open())
        {
            cout << endl;
            fout << "Username: " << inputUserName(fout) << "\nPassword: " << inputPassword(fout) << '\n'; // place username & password in a container
            cout << "\nAdded successfully!\n";
            system("pause");
        }
        else
        {
            cerr << "\nCan't open file.\n";
            system("pause");
        }

        fout.close();
        encrypt(fileName); // encrypts file
    }
}

void listFiles()
{
    cout << "~ Files Available : \n\n";
    for (auto &files : directory_iterator(dir)) // iterate on available files on 'data' folder
        cout << "* " << files << endl;
    cout << endl;
}

void viewPass(string &fileName, ifstream &fin, ofstream &fout, int &count) // view a password
{
    string content = "";

    for (int i = 0; i < count; i++)
    {
        inputFilename(fileName, i, count);
        if (isTxt(fileName) == true && fileName != keyContainer) // <- checks if file ends w/ '.txt'. BUG: '.txtX', 'X' = any chars is alloweds
        {
            decrypt(fileName);
            fin.open(dir + fileName);
        }

        else
        {
            cout << "\nError Accessing File, Please Try Again!\n\n";
            system("pause");
            continue;
        }

        cout << endl;
        if (fin.is_open())
        {
            while (!fin.eof())
            {
                getline(fin, content);

                cout << content << endl;
            }
        }
        else
            cerr << "Can't find file!\n\n";

        system("pause");
        fin.close();

        encrypt(fileName); // encrypt the file again
    }
}

void updatePass(string &fileName, int &count)
{
    string mode, altMode; // altMode - for both option
    short update;

    for (int i = 0; i < count; i++)
    {
        inputFilename(fileName, i, count);

        system("cls");
        cout << "[1] Username\t[2] Password\t[3] Both\n\n";
        cout << "Which to update?\n> ";
        cin >> update;
        cin.clear();
        cin.ignore();

        if (update == 1)
        {
            mode = "username";
            arg_update(fileName, mode);
        }
        else if (update == 2)
        {
            mode = "password";
            arg_update(fileName, mode);
        }
        else if (update == 3)
        {
            mode = "username";
            altMode = "password";
            arg_update(fileName, mode, altMode);
        }
        else
        {
            cerr << "\nInvalid Input!\n";
            system("pause");
        }
    }
}

void delPass(string &fileName, int &count)
{
    for (int i = 0; i < count; i++)
    {
        system("cls");
        inputFilename(fileName, i, count);
        if (isTxt(fileName) == true && fileName != keyContainer) // <- checks if file ends w/ '.txt'. BUG: '.txtX', 'X' = any chars is alloweds
        {
            if (remove(dir + fileName) == 1)
                cout << "\nFile successfully removed!\n";
            else
                cerr << "\nDeletion failed!\n";
            system("pause");
        }
        else
        {
            cerr << "\nError Accessing File, Please Try Again!\n\n";
            system("pause");
            continue;
        }
    }
}

void changeKey()
{
    string key;
    ofstream fout;

    cout << "~ Password Vault ~\n\n";
    // for login
    if (login() == true)
        cout << "\nAccess granted :P\n\n";

    else // exit program when key is wrong
    {
        cerr << "\nIncorrect Password!\n";
        system("pause");
        return;
    }
    system("pause");

    fout.open(dir + keyContainer);

    if (fout.is_open())
    {
        system("cls");
        cout << "~ Password Vault ~\n\n";
        cout << "Input new vault key :\n> ";
        cin >> key;

        fout << key;
        cout << "\nChange Success!\n";
        ;
    }
    else
        cerr << "Can't open file!\n";

    system("pause");
    fout.close();
    encrypt(keyContainer);
}
