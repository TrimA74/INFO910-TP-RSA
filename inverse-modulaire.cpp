
#include <gmp.h>
#include <iostream>

using namespace std;

void inverseModulaire(mpz_t result, mpz_t a, mpz_t b)
{
    mpz_t r0, r1, r2, s0, s1, s2, q, qs1, tmp;

    mpz_init(r0);
    mpz_init(r1);
    mpz_init(r2);
    mpz_set_ui(r2,0);
    mpz_init(s0);
    mpz_init(s1);
    mpz_init(s2);
    mpz_init(q);
    mpz_init(qs1);
    mpz_init(tmp);
    mpz_set_ui(tmp,0);

    //r[0] = a
    mpz_set(r0, a);
    //r[1] = b
    mpz_set(r1, b);

    //s[0] = 1
    mpz_set_ui(s0, 1);
    //s[1] = 0
    mpz_set_ui(s1, 0);

    //q = r[0] / r1
    mpz_fdiv_qr(q, r2, r0, r1);

    while(mpz_cmp_ui(r2,0) > 0)//while(mpz_get_ui(r2) > 0)
    {
        mpz_mul(qs1, q, s1);
        mpz_sub(s2, s0, qs1);

        mpz_set(s0, s1);
        mpz_set(s1, s2);

        mpz_set(r0, r1);
        mpz_set(r1, r2);

        mpz_fdiv_qr(q, r2, r0, r1);
    }

    mpz_set(result, s1);

    //mpz_invert return a positive invert between 0 and abs(b)
    //So we increase result to result + b
    while(mpz_cmp_ui(result,0) < 0){
        mpz_add(result,result,b);
    }
}

int main( int argc, char ** argv )
{
	
	mpz_t a;
	mpz_t b;
	mpz_t gmpResult;
	mpz_t ownResult;
	mpz_init( a );
	mpz_init( b );
	mpz_init( gmpResult );
	gmp_scanf( "%Zd", a ); // Saisie clavier
	gmp_scanf( "%Zd", b );
	mpz_t result;
	mpz_init( ownResult );

	inverseModulaire( ownResult, a, b );

	mpz_invert(gmpResult,a,b);


	gmp_printf("inverseModulaire : %Zd inverseModulaire_GMP : %Zd\n",ownResult, gmpResult);
	if(mpz_cmp(gmpResult,ownResult) == 0)
    	cout << "work fine !" << endl;
	else
	    cout << "doesn't work !" << endl;

	// Libère la mémoire
	mpz_clear( a );
	mpz_clear( b );
	mpz_clear( ownResult );
	
}