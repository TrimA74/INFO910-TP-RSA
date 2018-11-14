//
// Created by antoine on 07/11/18.
//
#include <iostream>
#include <fstream>
#include "gmphelper.cpp"

using namespace std;


int main(int argc, char** argv){
    if(argc != 2){
        cout << "Usage : ./dechiffre filename"<<endl;
        return -1;
    }

    string output = argv[1];
    output += ".priv";

    mpz_t n, a, block;
    mpz_init(n);
    mpz_init(a);
    mpz_init(block);
    unsigned int t = 0;

    string line;
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
        while(getline(cin,line))
        {
            mpz_set_str(block,line.c_str(),10);
            //On dechiffre
            mpz_powm(block,block,a,n);

            //On réinitialise le tableau à 0 pour éviter que si l'export ne rempli pas tout le tableau,
            //on se retrouve avec des valeurs indésirables
            for(int i=0; i<t; i++)
                result[i] = 0;

            mpz_export(result, NULL, 1, sizeof(char), 0, 0, block);
            for(int i=0; i<t; i++)
                if((int)result[i] != 0)
                    cout << result[i];
        }

    }else
        cout << "Unable to open file";

    return 0;
}

