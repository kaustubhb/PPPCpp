#include "std_lib_facilities.h"

int main() {
	cout << 1234 << "\t" << hex << 1234 << "\t" << oct << 1234 << endl;
	cout << showbase << dec;
	cout << 1234 << "\t" << hex << 1234 << "\t" << oct << 1234 << endl;
	cout << dec << noshowbase << "Enter in hex: ";
	int num;
	// cin >> hex >> num >> dec;
	// cout << num << endl;

	cin.unsetf(ios::dec);
	cin.unsetf(ios::hex);
	cin.unsetf(ios::oct);
	cin >> num;
	cout << num << endl;
}
