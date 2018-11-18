//
// Created by antoine on 07/11/18.
//
#include <iostream>
#include <openssl/sha.h>
#include <fstream>
#include <gmp.h>
#include "sha1tools.cpp"

using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Usage : cat plainText.txt | ./signe filenameKeys"<<endl;
        return -1;
    }

    string filename = argv[1];

    //Lire le clair sur l'entrée standard
    string line;
    string plainText = "";
    while(getline(cin,line)){
        plainText += line + "\n";
    }

    //On hache le texte en SHA1
    unsigned char hash[SHA_DIGEST_LENGTH];
    sha1(plainText,hash);
    string hashedString = sha1ToString(hash);

    mpz_t n, a, block;
    mpz_init(n);
    mpz_init(a);
    mpz_init(block);
    unsigned int t = 0;

    ifstream myfile (filename + ".priv");
    ofstream fileSigned ("message.signe");
    if (myfile.is_open() && fileSigned.is_open())
    {
        getline (myfile,line);
        t = atoi(line.c_str()) / 8;
        getline (myfile,line);
        mpz_set_str(n,line.c_str(),10);
        getline (myfile,line);
        getline (myfile,line);
        getline (myfile,line);
        mpz_set_str(a,line.c_str(),10);
        myfile.close();

        char blockString[t];
        for(int i=0; i<hashedString.length(); i += t){
            mpz_import(block, t, 1, sizeof(char), 0, 0, hashedString.substr(i,t).c_str());

            mpz_powm(block,block,a,n);

            mpz_get_str(blockString,10,block);
            fileSigned << blockString << endl;

        }
        fileSigned.close();
    }else
        cout << "Unable to open file";

    return 0;
}