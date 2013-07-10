#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Debug : public ofstream
{
public:
	Debug();
	~Debug();

//	void debug(string s);
//	friend ostream& operator<<(ostream& outs, const Debug& debug);
//
//private:
//	ofstream file;
};

extern Debug debug;

#endif
