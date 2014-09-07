#include "std_lib_facilities.h"

int main()
{
    ifstream ifs("input.pdf", ios_base::binary);
	if(!ifs) {
        cerr << "Could not read input file as binary" << endl;
        return 0;
    }

    vector<int> v;  // read input bytes

    int x;
    while(ifs.read(as_bytes(x), sizeof(x))) {
        v.push_back(x);
    }

    ofstream ofs("output.pdf", ios_base::binary);
    if(!ofs) {
        cerr << "Could not create output binary file" << endl;
        return 0;
    }

    for(int i: v) {
        ofs.write(as_bytes(i), sizeof(i));
    }
}