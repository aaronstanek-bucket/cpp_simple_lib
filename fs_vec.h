#ifndef __FS_VEC_INCLUDED__
#define __FS_VEC_INCLUDED__

#include <cstdlib>

using namespace std;

template <class T> class fs_vec{
  private:
    T * data;
  public:
    fs_vec();
    ~fs_vec();
    void setup(unsigned long long siz);
    void clear();
    bool is_def();
    T * at(unsigned long long index);
};

//template functions

template <class T> fs_vec<T>::fs_vec() {
  data = NULL;
}

template <class T> fs_vec<T>::~fs_vec() {
  clear();
}

template <class T> void fs_vec<T>::setup(unsigned long long siz) {
  clear();
  data = new T[siz];
}

template <class T> void fs_vec<T>::clear() {
  if (data!=NULL) {
    delete[] data;
    data = NULL;
  }
}

template <class T> bool fs_vec<T>::is_def() {
  if (data==NULL) {
    return false;
  }
  return true;
}

template <class T> T * fs_vec<T>::at(unsigned long long index) {
  return data+index;
}

#endif
