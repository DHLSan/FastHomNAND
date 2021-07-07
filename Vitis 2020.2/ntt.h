

#include <stdint.h>
#include "ntt_constant.h"






extern uint64_t mod_mul(uint64_t x, uint64_t y, uint64_t p);
extern void ntt_CT(uint64_t x[], uint64_t modulus, int N);
extern  void intt_CT(uint64_t x[], uint64_t modulus, uint64_t y[], int N);
