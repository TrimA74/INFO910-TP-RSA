//
// Created by antoine on 23/10/18.
//
#include <iostream>
#include <fstream>
#include "gmphelper.cpp"

using namespace std;


int main(int argc, char** argv){
    if(argc != 3){
        cout << "Usage : ./gencle t output"<<endl;
        cout << "Example : ./gencle keys will generate keys.priv and keys.pub"<<endl;
        return -1;
    }

    string output = argv[2];

    mpz_t p, q, n;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);

    //On lit le t
    mpz_t t;
    mpz_init(t);
    mpz_set_str(t,argv[1],10);

    gmp_printf("# generating RSA keys for bloc size %Zd bits\n", t);

    mpz_t min, max, tmp, tmp2;
    mpz_init(min);
    mpz_init(max);
    mpz_init(tmp);
    mpz_init(tmp2);
    mpz_set_ui(tmp2,0);


    mpz_set_ui(tmp,2);
    mpz_fdiv_qr( min,tmp2, t, tmp );

    mpz_set_ui(tmp,16);
    mpz_add( max, min, tmp );
    //ici, min = t/2 et max = (t/2 + 16)

    //Generate p and q
    generateRandom(p,min,max);
    generateRandom(q,min,max);
    //gmpHelper.generateRandom(p,min,max);
    //gmpHelper.generateRandom(q,min,max);

    //n = p*q
    mpz_mul(n,p,q);

    cout << "# p,q pair generated. public n is " << endl;
    gmp_printf("%Zd\n", n);

    //Generate a and b
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    //Decrement p and q
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
    //tmp = p*q

    mpz_mul(tmp,p,q);
    mpz_set_ui(b,2);
    mpz_pow_ui(b, b, 16);
    mpz_add_ui(b,b,1);
    //b = 2^16 + 1

    mpz_invert(a,b,tmp);

    //Check
    mpz_mul(tmp2,a,b);
    mpz_t one, modN;
    mpz_init(one);
    mpz_set_ui(one,1);
    mpz_init(modN);
    mpz_mod(modN,one,tmp);
    //modN = 1 mod phi(n)
    //tmp2 = a*b
    cout << "# check a*b=1 mod phi(n), a*b=1" << endl;
    cout << "check a*b=1 mod phi(n) =" << mpz_cmp(tmp2,tmp) << endl;
    cout << "check a*b=1 =" << mpz_cmp_ui(tmp2,1) << endl;
    if(mpz_cmp(tmp2,tmp) == 1 && mpz_cmp_ui(tmp2,1) == 1){
        //Write t n p q a b in file.priv
        ofstream myfile;
        myfile.open (output + ".priv", ios::out | ios::trunc);
        if(myfile.is_open()) {
            myfile << mpz_get_str(NULL, 10, t) << "\n";
            myfile << mpz_get_str(NULL, 10, n) << "\n";
            myfile << mpz_get_str(NULL, 10, p) << "\n";
            myfile << mpz_get_str(NULL, 10, q) << "\n";
            myfile << mpz_get_str(NULL, 10, a) << "\n";
            myfile << mpz_get_str(NULL, 10, b) << "\n";
            myfile << "# Public/private RSA Keys : t n p q a b\n";
            myfile.close();
        }

        //Write n, b, t in file.pub
        ofstream myfile2;
        myfile2.open (output + ".pub", ios::out | ios::trunc);
        if(myfile2.is_open()) {
            myfile2 << mpz_get_str(NULL, 10, n) << "\n";
            myfile2 << mpz_get_str(NULL, 10, b) << "\n";
            myfile2 << mpz_get_str(NULL, 10, t) << "\n";
            myfile2 << "# Public/private RSA Keys : n, b, t\n";
            myfile2.close();
        }
        cout << "# OK : key pairs (t n p q a b) stored in " << output << ".priv." << endl;
        cout << "# OK : key pairs (t n b) stored in " << output << ".pub." << endl;
    }

    //TODO clear variables
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(min);
    mpz_clear(max);
    mpz_clear(tmp);
    mpz_clear(tmp2);
    mpz_clear(one);
    mpz_clear(modN);
    return 0;
}