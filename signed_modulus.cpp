#include "signed_modulus.h"

long long signed_modulus(long long a, long long b) {
  return ((a%b) + b) % b;
}

// (a%b) gives a number between -b and b
// (a%b) + b gives a number between 0 and 2b (for positive b) (2b and 0 for negative b)
// ((a%b) + b) % b gives a number between 0 and b (b and 0)
