#include "test_framework/generic_test.h"
#include "precomputedReverses.h"

unsigned long long swap(unsigned long long x, uint32_t i, uint32_t j)
{
    int bitAtI = (x >> i) & 1;
    int bitAtJ = (x >> j) & 1;

    if (bitAtI != bitAtJ)
    {
        x ^= (unsigned long long)1 << i;
        x ^= (unsigned long long)1 << j;
    }
    return x;
}

/*
unsigned long long ReverseBits(unsigned long long x) 
{
    for (uint32_t i = 0; i < 32; i++)
    {
        x = swap(x, i, 63 - i);
    }
    return x;
}
*/

unsigned long long ReverseBits(unsigned long long x)
{
    uint32_t cacheBits = 16;
    uint32_t cacheMask = 0xFFFF;

    unsigned long long firstQuarter = (x >> 3 * cacheBits) & cacheMask;
    firstQuarter = precomputedReverse[firstQuarter];

    unsigned long long secondQuarter = (x >> 2 * cacheBits) & cacheMask;
    secondQuarter = precomputedReverse[secondQuarter];
    secondQuarter <<= cacheBits;

    unsigned long long thirdQuarter = (x >> cacheBits) & cacheMask;
    thirdQuarter = precomputedReverse[thirdQuarter];
    thirdQuarter <<= cacheBits * 2;

    unsigned long long fourthQuarter = x & cacheMask;
    fourthQuarter = precomputedReverse[fourthQuarter];
    fourthQuarter <<= cacheBits * 3;

    return fourthQuarter | thirdQuarter | secondQuarter | firstQuarter;
}

// 10110100010001100100011010101011100100000000000000000000000
// 10110100010001100100011010101011100100000000000000000000000

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
