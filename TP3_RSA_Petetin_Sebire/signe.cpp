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
        cout << "Usage : cat plainText.txt | ./signe filename"<<endl;
        return -1;
    }

    string output = argv[1];
    output += ".priv";

    //Lire le clair sur l'entrée standard
    string line;
    string plainText = "";
    while(getline(cin,line)){
        plainText += line + "\n";
    }

    cout << plainText <<endl;
    //On hache le texte en SHA1
    unsigned char hash[SHA_DIGEST_LENGTH];
    sha1(plainText,hash);
    string hashedString = sha1ToString(hash);

    mpz_t n, a, block;
    mpz_init(n);
    mpz_init(a);
    mpz_init(block);
    unsigned int t = 0;

    ifstream myfile (output);
    if (myfile.is_open())
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


        char result[t];
        size_t rbytes;
        char* buffer = new char[ t ];
        for(int i=0; i<hashedString.length(); i += t){

        }
    }
    /*
        while(rbytes = fread(buffer, sizeof(char), t, sha1ToString(hash))) {
            mpz_import(block, rbytes, 1, sizeof(buffer[0]), 0, 0, buffer);
        }*/
        /*
        while(getline(cin,line))
        {
            mpz_set_str(block,line.c_str(),10);
            //On dechiffre
            mpz_powm(block,block,a,n);

            //On met le block dans le fichier

        }*/
/*
    }else
        cout << "Unable to open file";
*/
    cout << sha1ToString(hash) <<endl;
    return 0;
}