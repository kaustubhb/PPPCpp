#include "std_lib_facilities.h"

void displayNums()
{
	cout << "\t" << 1.0 << endl
	     << "\t" << 1.23 << endl
		 << "\t" << 123.456 << endl
		 << "\t" << 1234.5678 << endl
		 << "\t" << 12345678.912 << endl;
}

int main() {
	// cout << "Default:" << endl;
	// displayNums();
 //    cout << endl;

 //    cout << "Fixed:" << endl << fixed;
 //    displayNums();
 //    cout << endl;

 //    cout.unsetf(ios_base::floatfield);

 //    cout << "Scientific:" << endl << scientific;
 //    displayNums();
 //    cout << endl;

    cout << "Default:" << setprecision(3) << endl;
    displayNums();
    cout << endl;

    cout << "Fixed:" << endl << fixed;
    displayNums();
    cout << endl;

    cout.unsetf(ios_base::floatfield);

    cout << "Scientific:" << endl << scientific;
    displayNums();
    cout << endl;

    cout << std::bitset<32>(cout.flags()) << endl;
}
