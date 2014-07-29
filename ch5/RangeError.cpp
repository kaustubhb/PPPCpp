#include "std_lib_facilities.h"

int main()
{
  try {
    vector<int> vi;
    for(size_t i=0;i<5;++i)
      vi.push_back(i+1);
    for(size_t i=0;i<=vi.size();++i)
      cout << vi[i] << endl;
  }
  catch(out_of_range &error) {
    cerr << "Oops, out of range error!" << endl;
    keep_window_open();
    return 1;
  }
  catch(...) {
    cerr << "Exception, something went wrong!" << endl;
  }
}

