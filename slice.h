#ifndef __SLICE_INCLUDED__
#define __SLICE_INCLUDED__

#include <iostream>

using namespace std;

// A needs to have .size() and [] access
// B needs to have .resize() and [] assignment

template <class A, class B> void slice(A & inp, B & oup, long long start, long long end, long long iter) {
  // first do some safety stuff
  long long a_size = inp.size();
  if ((a_size==0) || (iter==0)) {
    oup.resize(0);
    return;
  }
  if (start>=a_size) {
    start = a_size-1;
  }
  else if (start<0) {
    start = start+a_size;
    if (start<0) {
      start = 0;
    }
  }
  if (end>=a_size) {
    end = a_size-1;
  }
  else if (end<0) {
    end = end+a_size;
    if (end<0) {
      end = 0;
    }
  }
  // now find how much space to allocate
  long long diff = end-start;
  // if iter and diff have different signs, we are done
  if (iter>0) {
    if (diff<0) {
      oup.resize(0);
      return;
    }
  }
  else {
    if (diff>0) {
      oup.resize(0);
      return;
    }
  }
  // variables may be reused ahead (sorry)
  // if the signs are good, then we can find how much space to allocate
  a_size = (diff/iter) + 1; // a_size is now the number of elements in the output slice
  oup.resize(a_size);
  // end will now be used as an iterator (to index values of oup)
  // start will be used to index values of inp
  for (end=0;end<a_size;end++) {
    oup[end] = inp[start];
    start += iter;
  }
}

#endif
