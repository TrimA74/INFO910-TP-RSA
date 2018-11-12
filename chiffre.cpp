//
// Created by antoine on 23/10/18.
//
#include <iostream>
#include <fstream>
#include "gmphelper.cpp"

using namespace std;


int main(int argc, char** argv){
    if(argc != 2){
        cout << "Usage : ./chiffre filename"<<endl;
        return -1;
    }

    string output = argv[1];
    output += ".pub";

    unsigned int t;
    mpz_t n, b, block;
    mpz_init(n);
    mpz_init(b);
    mpz_init(block);

    string line;
    ifstream myfile (output);
    FILE *fileChiffre;
    fileChiffre = fopen("message.chiffre", "wt");

    if (myfile.is_open() && fileChiffre != NULL)
    {
        getline (myfile,line);
        mpz_set_str(n,line.c_str(),10);
        getline (myfile,line);
        mpz_set_str(b,line.c_str(),10);
        getline (myfile,line);
        t = atoi(line.c_str()) / 8;
        myfile.close();

        char* buffer = new char[ t ];
        size_t rbytes;
        size_t totalRbytes=0;
        int nbBlocks =0;
        while(rbytes = fread(buffer, sizeof(char), t, stdin))
        {
            mpz_import(block, rbytes, 1, sizeof(buffer[0]), 0, 0, buffer);
            totalRbytes += rbytes;
            //On chiffre
            mpz_powm(block,block,b,n);
            gmp_printf("%Zd\n", block);
            //Ecrit le bloc chiffre dans un fichier
            gmp_fprintf(fileChiffre, "%Zd\n", block);
            nbBlocks++;
        }
        fclose(fileChiffre);
        cout << "# " << totalRbytes << " bytes read, " << nbBlocks << " blocs read." << endl;


    }else
        cout << "Unable to open file";




    return 0;
}