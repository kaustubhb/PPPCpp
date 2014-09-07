#include "std_lib_facilities.h"

void add1()
{	
	ofstream os{"testfile"};
	os << "Hello ";
}

void add2()
{
	ofstream os{"testfile", ios_base::app};
	os << "World!";
}

int main()
{
	add1();
	add2();
}