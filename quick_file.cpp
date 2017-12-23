#include "quick_file.h"

bool quick_file::load(const char * filename, vector<char> & indata) {
  fstream infile;
  infile.open(filename, ios::in | ios::binary);
  if (infile.is_open()==false) {
    return false;
  }
  infile.seekg(0, ios::end);
  unsigned long long siz = infile.tellg();
  if (siz==0) {
    indata.resize(0);
    infile.close();
    return true;
  }
  indata.resize(siz);
  infile.seekg(0, ios::beg);
  infile.read(&(indata[0]),siz);
  infile.close();
  return true;
}

bool quick_file::save(const char * filename, vector<char> & oudata) {
  fstream oufile;
  oufile.open(filename, ios::out | ios::binary | ios::trunc);
  if (oufile.is_open()==false) {
    return false;
  }
  unsigned long long siz = oudata.size();
  if (siz==0) {
    oufile.close();
    return true;
  }
  oufile.seekp(0, ios::beg);
  oufile.write(&(oudata[0]),siz);
  oufile.close();
  return true;
}
