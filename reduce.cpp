// reduce.cpp
#include <stdint.h>
#include "reduce.h"
#include "params.h"

void MONT_REDUCE::r32_mod_Q() {
    int32_t t;

    t   = (int64_t)(int32_t)in*QINV;
    out = (in - (int64_t)t*Q) >> 32; 
}

void REDUCE32::r_mod_Q() {
    while(true) {
        int32_t a = in.read();
        out.write(a - ((a + (1 << 22)) >> 23)*Q);
    }
}

void CADDQ::add_Q() {
    while(true) {
        int32_t a = in.read();
        out.write(a + ((a >> 31) & Q));
    }
}

/*
void ADDER::do_add() {
    sum = b + a;
}
*/

/*
// To test the montgomery_reduce() function
int32_t montgomery_reduce(int64_t a) {
  int32_t t;

  t = (int64_t)(int32_t)a*QINV;
  t = (a - (int64_t)t*Q) >> 32;
  return t;
}
*/