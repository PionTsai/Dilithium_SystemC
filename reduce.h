#ifndef REDUCE_H
#define REDUCE_H

#include <stdint.h>
#include "systemc.h"

using namespace std;
using namespace sc_core;

#define MONT -4186625 // 2^32 % Q
#define QINV 58728449 // q^(-1) mod 2^32

//int32_t montgomery_reduce(int64_t a);

/*************************************************
* Module name: MONT_REDUCE
*
* Description: The Montgomery reduce
*              For finite field element a with -2^{31}Q <= a <= Q*2^31,
*              compute r \equiv a*2^{-32} (mod Q) such that -Q < r < Q.
*
* Ports: sc_in<int32_t>   in: finite field element a
*        sc_out<int32_t> out: the output r
**************************************************/
SC_MODULE(MONT_REDUCE) {
    sc_in<int32_t>  in;
    sc_out<int32_t> out;

    void r32_mod_Q();

    SC_CTOR(MONT_REDUCE) {
        SC_METHOD(r32_mod_Q);
        sensitive << in;
    }
};

/*************************************************
* Module name: REDUCE32
*
* Description: For finite field element a with a <= 2^{31} - 2^{22} - 1,
*              compute r \equiv a (mod Q) such that -6283009 <= r <= 6283007.
*
* Ports: sc_in<int32_t>   in: finite field element a
*        sc_out<int32_t> out: the output r
**************************************************/
SC_MODULE(REDUCE32) {
    sc_fifo_in<int32_t>  in;
    sc_fifo_out<int32_t> out;

    void r_mod_Q();

    SC_CTOR(REDUCE32) {SC_THREAD(r_mod_Q);}
};

/*************************************************
* Module name: CADDQ
*
* Description: Add Q if input coefficient is negative.
*
* Ports: sc_in<int32_t>   in: finite field element a
*        sc_out<int32_t> out: the output a (or a + Q)
**************************************************/
SC_MODULE(CADDQ) {
    sc_fifo_in<int32_t>  in;
    sc_fifo_out<int32_t> out;

    void add_Q();

    SC_CTOR(CADDQ) {SC_THREAD(add_Q);}
};

/*************************************************
* Module name: FREEZE
*
* Description: For finite field element a, compute standard
*              representative r = a mod^+ Q.
*
* Ports: sc_in<int32_t>   in: finite field element a
*        sc_out<int32_t> out: the output r
**************************************************/
SC_MODULE(FREEZE) {
    sc_fifo_in<int32_t>  in;
    sc_fifo_out<int32_t> out;
    sc_fifo<int32_t> sig;
    REDUCE32 r32;
    CADDQ aq;

    SC_CTOR(FREEZE): in("freeze_in"),
                     out("freeze_out"),
                     sig("sig"),
                     r32("reduce32"),
                     aq("caddq") {
        r32.in(in);
        r32.out(sig);
        aq.in(sig);
        aq.out(out);
    }
};

/*
//Practice module
SC_MODULE (ADDER) {
    sc_in<int32_t> a,b;
    sc_out<int32_t> sum;

    void do_add();

    SC_CTOR(ADDER) {
        SC_METHOD(do_add);
        sensitive << a << b;
    } 
};
*/

#endif