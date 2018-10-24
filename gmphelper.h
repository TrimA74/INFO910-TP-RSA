//
// Created by antoine on 24/10/18.
//

#ifndef TP3_INFO910_GMPHELPER_H
#define TP3_INFO910_GMPHELPER_H

#include <gmp.h>

unsigned int generateSeed();
void generateRandom(mpz_t result, mp_bitcnt_t nbBits);
void generateRandom(mpz_t result, mpz_t minBitsZ, mpz_t maxBitsZ);


#endif //TP3_INFO910_GMPHELPER_H
