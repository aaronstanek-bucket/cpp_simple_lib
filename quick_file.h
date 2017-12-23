#ifndef __QUICK_FILE_INCLUDED__
#define __QUICK_FILE_INCLUDED__

#include <fstream>
#include <vector>

using namespace std;

namespace quick_file {

  bool load(const char * filename, vector<char> & indata);
  bool save(const char * filename, vector<char> & oudata);

}

#endif
