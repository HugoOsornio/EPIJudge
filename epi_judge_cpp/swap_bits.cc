#include "test_framework/generic_test.h"
long long SwapBits(long long x, int i, int j) 
{
   
  int bitAtI = (x >> i) & 1;
  int bitAtJ = (x >> j) & 1;

  if (bitAtI != bitAtJ)
  {
      x ^= (long long)1 << i;
      x ^= (long long)1 << j;
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "i", "j"};
  return GenericTestMain(args, "swap_bits.cc", "swap_bits.tsv", &SwapBits,
                         DefaultComparator{}, param_names);
}
