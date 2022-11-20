#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>

using std::ofstream;
using std::string;

void decrypt(string &fileName);
void encrypt(string &fileName);
bool isTxt(string &fileName);
string inputUserName(ofstream &fout);
string inputPassword(ofstream &fout);
void inputFilename(string &fileName, int &i, int &count);
int how_many_to(const string &mode);
void arg_update(string &fileName, string &mode);
void arg_update(string &fileName, string &mode, string &altMode); // overload
bool login();
void home();

#endif // UTILS_H
