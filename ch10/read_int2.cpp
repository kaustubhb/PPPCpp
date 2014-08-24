#include "std_lib_facilities.h"

void skip_to_int() {
	char c;
	if(cin.eof()) {
		error("Sorry, no input");
	}	
	if(cin.fail()) {
		cin.clear();
		while((cin >> c) && !isdigit(c))
			;
		if(!cin)
			error("No input");
		cin.unget();
	}
}

int get_int() {
	int n;
	while(true) {
		if(cin >> n)
			return n;
		cout << "Sorry, that was not a number, please try again." << endl;
		skip_to_int();
	}
}

int get_int(int low, int high) {	// range of values
	int n;
	cout << "Enter an integer in range [" << low << ", " << high << "]" << endl;
	while(true) {
		n = get_int();
		if(n >= low && n <= high)
			return n;
		cout << "Sorry, that was not in range, Please try again" << endl;
	}
}

int main() {
	cout << get_int(10,20) << endl;
}