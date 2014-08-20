#include "std_lib_facilities.h"


// repeatedly ask for an integer in range [a,b) until an acceptable value is entered
void readInt(int a, int b, istream &cin)
{
	int i;
	while(true) {
		cin >> i;

		if(cin.good()) {
			if(i >= a && i < b) {
				cout << "Success:	" << i << endl;
				return;
			}

			else {
				cout << "Integer not in range. Please try again" << endl;
			}
		}

		else if(cin.bad()) {
			error("cin is in bad state");
		}

		else if(cin.eof()) {
			cout << "No more input" << endl;
			return;
		}
		else {	// cin.fail()
			cout << "Sorry, that wasn't a number. Try again" << endl;
			cin.clear();
			char c;
			while(cin >> c && !isdigit(c))
				;
			cin.unget();	// returns the last read character back to stream
		}
	}

}

int main()
{
	ifstream in("./Makefile");
	in.exceptions(in.exceptions() | ios_base::badbit);
	readInt(10,20, in);
}