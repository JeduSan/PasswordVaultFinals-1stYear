#ifndef FINALS_H
#define FINALS_H

#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;

void addPass(string &fileName, ofstream &fout, int &count);
void listFiles();
void viewPass(string &fileName, ifstream &fin, ofstream &fout, int &count);
void updatePass(string &fileName, int &count);
void delPass(string &fileName, int &count);
void changeKey();

#endif // ! FINALS_H
