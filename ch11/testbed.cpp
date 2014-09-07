#include "std_lib_facilities.h"

int main() {
	ofstream of1("testfile");
	if(!of1)
		cout << "Error" << endl;
}
