#include "debug.h"


Debug debug;


Debug::Debug()
{
	open("stdout.txt", ios::out);
}


Debug::~Debug()
{
	close();
}
