#include "std_lib_facilities.h"

void fillVector(vector<int> &v, istream &ist, char terminator)
{
	int x;
	while(ist >> x)
		v.push_back(x);
	if(ist.bad())
		error("Some unusual error occurred, stream is in bad state.");
	if(ist.eof())
		return;
	if(ist.fail()) {
		ist.clear();	// clear stream state
		char c;
		ist >> c;
		if(c == terminator) {
			cout << "found terminator\n";
			return;
		}
		ist.unget();
		ist.clear(ios_base::failbit);	// set the state to fail
	}
}

int main()
{
	vector<int> v;
	fillVector(v, cin, ';');

	for(vector<int>::iterator it = v.begin(); it!=v.end(); ++it) {
		cout << *it << endl;
	}
}
