//
// Created by trima on 12/11/18.
//
#include <iostream>
#include <fstream>
#include "gmphelper.cpp"

using namespace std;


int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage : ./verifie filename" << endl;
        return -1;
    }

    string pubFileString = argv[1];
    pubFileString += ".pub";

    string signeFileString = argv[1];
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
        string fullResult;
        char * buffer;
        char * hashed;
        while(getline(cin,line)){

            // todo set hashed with line

            while(getline(signeFile,line)) {
                mpz_set_str(block,line.c_str(),10);

                //On chiffre
                mpz_powm(block, block, b, n);

                mpz_export(result, NULL, 1, sizeof(char), 0, 0, block);
                fullResult+=result;

            }


            // todo on test si result == hashed

        }
        //cout << "# " << totalRbytes << " bytes read, " << nbBlocks << " blocs read." << endl;


    } else
        cout << "Unable to open file";


    return 0;
}

