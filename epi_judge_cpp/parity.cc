#include "test_framework/generic_test.h"
/*short Parity(unsigned long long x) {
    int parity = 0;
    while (x)
    {
        parity ^= (x & 1);
        x = x >> 1;
    }
  return parity;
}*/

/*
short Parity(unsigned long long x) {
    short result = 0;
    while (x)
    {
        result ^= 1;
        x &= (x - 1);
    }
    return result%2;
}
*/

short Parity(unsigned long long x) {
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
