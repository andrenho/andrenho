#include "util.h"

#include <sstream>

using namespace std;

vector<string>*
split(string text, char delimiter)
{
  vector<string>* v = new vector<string>();
  unsigned int n = 0;
  while((n = text.find(delimiter)) != string::npos)
  {
    string s = text.substr(0, n);
    v->push_back(s);
    text = text.substr(n+1);
  }
  v->push_back(text);
  return v;
}

string wrap(string text, unsigned int w)
{
  stringbuf n;
  unsigned int linew = 0;
  unsigned int pos = 0;
  for(string::iterator it = text.begin(); it < text.end(); it++)
  {
    unsigned int next_space = text.find(' ', pos) - pos;
    if((*it) == '\n')
      linew = 0;
    else if(next_space + pos != string::npos)
      if(next_space + linew > w)
      {
        n.sputc('\n');
        linew = 0;
      }
    n.sputc(*it);
    linew++;
    pos++;
  }
  return n.str();
}
