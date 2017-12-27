#ifndef __SET_INCLUDED__
#define __SET_INCLUDED__

#include <cstdlib>
#include "fs_vec.h"

using namespace std;

namespace set {

  template <class T> class element {
    public:
      element<T> * nex;
      T value;
      element();
  };

  template <class T> class root {
    public:
      element<T> * poi;
      root();
      ~root();
      bool has(T & v);
      bool add(T & v);
      bool rm(T & v);
  };

  template <class T> class set {
    private:
      fs_vec< root<T> > data;
      unsigned long long data_size;
      unsigned long long count;
      unsigned long long (*hash_function)(T&);
      void resize(unsigned long long new_size);
      bool insert(T & v);
      bool remove(T & v);
    public:
      set();
      set(unsigned long long (*hf)(T&));
      // don't need to write destructor
      void rehash(unsigned long long (*hf)(T&));
      bool has(T & v);
      void add(T & v);
      void rm(T & v);
  };

}

// template functions

template <class T> set::element<T>::element() {
  nex = NULL;
}

template <class T> set::root<T>::root() {
  poi = NULL;
}

template <class T> set::root<T>::~root() {
  element<T> * q = poi;
  element<T> * w;
  while (q!=NULL) {
    w = q->nex;
    delete q;
    q = w;
  }
}

template <class T> bool set::root<T>::has(T & v) {
  element<T> * q = poi;
  while (true) {
    if (q==NULL) {
      return false;
    }
    if (q->value==v) {
      return true;
    }
    q = q->nex;
  }
}

template <class T> bool set::root<T>::add(T & v) {
  element<T> * q = poi;
  element<T> ** r = &poi;
  while (true) {
    if (q==NULL) {
      q = new element<T>;
      (q->value) = v;
      (*r) = q;
      return true;
    }
    if (q->value==v) {
      return false;
    }
    r = &(q->nex);
    q = (*r);
  }
}

template <class T> bool set::root<T>::rm(T & v) {
  element<T> * q = poi;
  element<T> ** r = &poi;
  while (true) {
    if (q==NULL) {
      return false;
    }
    if (q->value==v) {
      (*r) = (q->nex);
      delete q;
      return true;
    }
    r = &(q->nex);
    q = (*r);
  }
}

template <class T> set::set<T>::set() {
  data.setup(5);
  data_size = 5;
  count = 0;
}

template <class T> set::set<T>::set(unsigned long long (*hf)(T&)) {
  data.setup(5);
  data_size = 5;
  count = 0;
  hash_function = hf;
}

template <class T> bool set::set<T>::has(T & v) {
  unsigned long long spot = hash_function(v) % data_size;
  return (data.at(spot))->has(v);
}

template <class T> void set::set<T>::resize(unsigned long long new_size) {
  set<T> tiny;
  tiny.data.setup(new_size);
  tiny.data_size = new_size;
  tiny.hash_function = hash_function;
  element<T> * q;
  for (unsigned long long r=0;r<data_size;r++) {
    q = (data.at(r))->poi;
    while (q!=NULL) {
      tiny.insert(q->value);
      q = q->nex;
    }
  }
  tiny.data.move_to(data);
  data_size = new_size;
}

template <class T> void set::set<T>::rehash(unsigned long long (*hf)(T&)) {
  hash_function = hf;
  if (count!=0) {
    resize(data_size);
  }
}

template <class T> bool set::set<T>::insert(T & v) {
  unsigned long long spot = hash_function(v) % data_size;
  return (data.at(spot))->add(v);
}

template <class T> bool set::set<T>::remove(T & v) {
  unsigned long long spot = hash_function(v) % data_size;
  return (data.at(spot))->rm(v);
}

template <class T> void set::set<T>::add(T & v) {
  if (insert(v)) {
    count += 1;
    if (count>=(data_size*2)/3) {
      resize((data_size*2)-1);
    }
  }
}

template <class T> void set::set<T>::rm(T & v) {
  if (remove(v)) {
    count -= 1;
    if (count<=data_size/4) {
      if (data_size>6) {
        resize((data_size+1)/2);
      }
    }
  }
}

#endif
