// poly.cpp
#include <stdint.h>
#include "poly.h"
#include "reduce.h"
#include "params.h"

void POLY_REDUCE::poly_reduce() {
    poly tmp;
    int i;

    while(true) {
        tmp = a.read();
        for(i = 0 ; i < N ; i++) {
            cout << "tmp[" << i << "] = " << tmp.coeffs[i] << endl;
            c.write(tmp.coeffs[i]);
            tmp.coeffs[i] = r_c.read();
        }
        b.write(tmp);
    }
}

void POLY_READTEST::poly_read() {
    poly tmp;
    int i;

    while(true) {
        tmp = a.read();
        for(i = 0 ; i < N ; i++) {
            cout << "tmp[" << i << "] = " << tmp.coeffs[i] << endl;
        }
        b.write(tmp);
    }
}