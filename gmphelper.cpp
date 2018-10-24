//
// Created by antoine on 24/10/18.
//

#include "gmphelper.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

unsigned int generateSeed(){
    struct timeval tv;
    int val = (int) getpid() + 65536*(int) getppid();
    if ( gettimeofday( &tv, NULL ) == 0 )
        val += (int) (tv.tv_sec*1000000 + tv.tv_usec);
    return val;
}

void generateRandom(mpz_t result, mp_bitcnt_t nbBits){
    //On génère la graine
    unsigned int seed = generateSeed();
    //On génère l'état
    gmp_randstate_t state;

    //Initialisation du générateur
    gmp_randinit_default(state);
    gmp_randseed_ui(state, seed);

    //Calcul un random min et d'un random max
    mpz_init(result);
    mpz_urandomb(result, state, nbBits);
}
void generateRandom(mpz_t result, mpz_t minBitsZ, mpz_t maxBitsZ){
    //On convertit les mpz en mp_bitcnt_t
    mp_bitcnt_t minBits = mpz_get_ui(minBitsZ);
    mp_bitcnt_t maxBits = mpz_get_ui(maxBitsZ);

    mpz_t randomMinP, randomMaxP;
    generateRandom(randomMinP, minBits);
    generateRandom(randomMaxP, maxBits);

    //Calcul la somme entre min et max
    mpz_add(result,randomMinP, randomMaxP);
}