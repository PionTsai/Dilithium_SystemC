#ifndef POLY_H
#define POLY_H

#include <stdint.h>
//#include <iostream>
#include "systemc.h"
#include "reduce.h"
#include "params.h"

using namespace std;

typedef struct polynomial{
    int32_t coeffs[N];

    // Constructor
    inline bool operator == (const polynomial& x) const {
        return (x.coeffs == coeffs);
    }

    inline polynomial& operator = (const polynomial& x) {
        int i;
        for(i = 0;i < N;i++) {
            coeffs[i] = x.coeffs[i];
        }
      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const polynomial& v,
    const std::string& NAME) {
        int i;
        for(i = 0;i < N;i++) {
            sc_trace(tf, v.coeffs[i], NAME + ".coeffs[" + to_string(i) + "]");
        }
    }

    inline friend ostream& operator << ( ostream& os,  polynomial const & v ) {
        int i;
        os << "{ ";
        for(i = 0;i < N-1;i++) {
            os << v.coeffs[i] << ", ";
        }
        os << v.coeffs[N] << "}";
        return os;
    }
} poly;

SC_MODULE(POLY_REDUCE) {
    sc_fifo_in<poly> a;
    sc_fifo_out<poly> b;
    sc_fifo<int32_t> c, r_c;
    REDUCE32 r32;

    void poly_reduce();

    SC_CTOR(POLY_REDUCE): r32("reduce32"),
                          c("coeff"),
                          r_c("reduced_coeff") {
        SC_THREAD(poly_reduce);
        r32.in(c);
        r32.out(r_c);
    }
};

// Test module
SC_MODULE(POLY_READTEST) {
    sc_in<poly> a;
    sc_out<poly> b;

    void poly_read();

    SC_CTOR(POLY_READTEST) {SC_THREAD(poly_read);}
};

#endif