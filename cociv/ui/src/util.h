#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

using namespace std;

vector<string>* split(string text, char delimiter=' ');
string wrap(string text, unsigned int w);

#endif
