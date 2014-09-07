#include "std_lib_facilities.h"

void fields1() {
	cout << setw(10) << 1234 << endl
		 << setw(10) << 12345 << endl;
}

void fields2()
{
	cout << '|' << setw(4) << 'k' << '|' << endl;
}

int main() {
	// cout << 1234 << "\t" << hex << 1234 << "\t" << oct << 1234 << endl;
	// cout << showbase << dec;
	// cout << 1234 << "\t" << hex << 1234 << "\t" << oct << 1234 << endl;
	// cout << dec << noshowbase << "Enter in hex: ";
	// int num;
	// // cin >> hex >> num >> dec;
	// // cout << num << endl;

	// cin.unsetf(ios::dec);
	// cin.unsetf(ios::hex);
	// cin.unsetf(ios::oct);
	// cin >> num;
	// cout << num << endl;

	fields2();
	
}
