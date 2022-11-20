// LIMITATION:
// <filesystem> is not supported on VScode (this program won't work on VScode's default library).
// - this program won't work well with files created externally.
// - this can't detect existing files, therefore adding a file/password with an existing name will overwrite the said file.
// - DO NOT OPEN THE PROGRAM TWICE AT ONCE. Doing so will make an error on the password file

// g++ *.cpp -o main -lstdc++fs
#include <iostream>
#include <fstream>
#include <direct.h> // mkdir()
#include "finals.h"
#include "utils.h"

using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

// NOTE : The default pass is 6969, unless it is changed.

int main()
{
    ofstream fout;
    ifstream fin;
    string fileName = "";
    const string mode_add = "add", mode_del = "delete", mode_up = "update", mode_view = "view";
    int count, menu;

    mkdir("files"); // folder for the files

    home(); // for reminder purpose

    system("cls");
    cout << "~ Password Vault ~\n\n";
    // for login
    if (login() == true)
        cout << "\nAccess granted :P\n\n";
    else // exit program when key is wrong
    {
        cout << "\n\nAccess denied...\n\n";
        return 1;
    }
    system("pause");

    do
    {
        system("cls");

        cout << "~ Password Vault ~\n\n";
        cout << "[1] Add Password(s)\n";
        cout << "[2] Update Password(s)\n";
        cout << "[3] View Password(s)\n";
        cout << "[4] List Password Containers\n";
        cout << "[5] Delete Password Container(s)\n";
        cout << "[6] Change Vault Key\n";
        cout << "[0] Quit\n\n";
        cout << "> ";
        cin >> menu;
        cin.clear();
        cin.ignore();

        if (menu == 1) // add password/s
        {
            system("cls");
            count = how_many_to(mode_add);

            system("cls");
            addPass(fileName, fout, count);
        }
        else if (menu == 2) // Update password/s
        {
            system("cls");
            count = how_many_to(mode_up);

            system("cls");
            updatePass(fileName, count);
        }
        else if (menu == 3) // View a password
        {
            system("cls");
            count = how_many_to(mode_view);

            system("cls");
            viewPass(fileName, fin, fout, count);
        }
        else if (menu == 4) // List all password container
        {
            system("cls");
            listFiles();
            system("pause");
        }
        else if (menu == 5) // Delete password container/s
        {
            system("cls");
            count = how_many_to(mode_del);

            system("cls");
            delPass(fileName, count);
        }
        else if (menu == 6)
        {
            system("cls");
            changeKey();
        }
        else if (menu == 0)
            system("cls");

    } while (menu != 0);

    return 0;
}
