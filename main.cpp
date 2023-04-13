// main.cpp
#include <stdint.h>
#include "systemc.h"
using namespace sc_core;

#include "reduce.h"
#include "params.h"

// Currently this is used for testing SC_MODULEs.

int sc_main(int argc, char* argv[]) {
    sc_signal<int32_t> sig_a, sig_b, sig_c, sig_t;
    //sc_signal<int32_t> sum;
    //REDUCE32 do_reduce32("do_reduce32");
    //CADDQ do_caddq("do_caddq");
    //do_reduce32(sig_a, sig_t);
    //do_reduce32.a(sig_a);
    //do_reduce32.t(sig_t);
    //do_caddq(sig_b,sig_c);
    FREEZE do_freeze("do_freeze");
    MONT_REDUCE do_mont_reduce("do_mont_reduce");
    do_freeze(sig_a,sig_t);
    do_mont_reduce(sig_b,sig_c);

    //ADDER adder("adder");
    //adder(sig_a,sig_b,sum);

    int b = 6283009;
    sig_a = -6283009;
    sig_b = b;
    
    //int32_t a = 1 << 3;
    //cout << "a = " << a << endl;

    sc_start(1,SC_NS);
    cout << sig_t << endl;
    cout << sig_c << endl;
    cout << montgomery_reduce(b) << endl;
    //cout << "sum = " << sum << endl;

    return 0;
}