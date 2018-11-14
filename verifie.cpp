//
// Created by trima on 12/11/18.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include "gmphelper.cpp"
#include "sha1tools.cpp"

using namespace std;


int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage : cat message.txt | ./verifie filenameKeys filenameBlocks" << endl;
        return -1;
    }

    string pubFileString = argv[1];
    pubFileString += ".pub";

    string signeFileString = argv[2];
    signeFileString += ".signe";


    unsigned int t;
    mpz_t n, b, block;
    mpz_init(n);
    mpz_init(b);
    mpz_init(block);

    string line;
    ifstream pubFile(pubFileString);
    ifstream signeFile(signeFileString);


    if (pubFile.is_open()) {
        getline(pubFile, line);
        mpz_set_str(n, line.c_str(), 10);
        getline(pubFile, line);
        mpz_set_str(b, line.c_str(), 10);
        getline(pubFile, line);
        t = atoi(line.c_str()) / 8;
        pubFile.close();

        char result[t];
        string hashedSigned;

        //On récupère le message déchiffré
        string plainText = "";
        while(getline(cin,line)){
            plainText += line + "\n";
        }

        //On hache le message déchiffré
        unsigned char hash[SHA_DIGEST_LENGTH];
        sha1(plainText, hash);

        while(getline(signeFile,line)) {
            mpz_set_str(block,line.c_str(),10);

            //On chiffre
            mpz_powm(block, block, b, n);

            //On réinitialise le tableau à 0 pour éviter que si l'export ne rempli pas tout le tableau,
            //on se retrouve avec des valeurs indésirables
            for(int i=0; i<t; i++)
                result[i] = 0;

            mpz_export(result, NULL, 1, sizeof(char), 0, 0, block);
            for(int i=0; i<t; i++)
                if((int)result[i] != 0)
                    hashedSigned+=result[i];

        }

        if(strcmp(hashedSigned.c_str(),sha1ToString(hash).c_str()) == 0)
            cout << "Verified !" << endl;
        else
            cout << "Not verified !" <<endl;

    } else
        cout << "Unable to open file";


    return 0;
}

