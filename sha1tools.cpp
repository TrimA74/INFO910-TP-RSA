//
// Created by antoine on 12/11/18.
//
#include <openssl/sha.h>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

void sha1(string plainText, unsigned char* hash){
    SHA1((const unsigned char*)plainText.c_str(), plainText.length() - 1, hash);
}

string sha1ToString(unsigned char* hash){
    std::ostringstream os;
    os.fill('0');
    os<<std::hex;
    for(const unsigned char * ptr=hash;ptr<hash+SHA_DIGEST_LENGTH;ptr++)
        os<<std::setw(2)<<(unsigned int)*ptr;
    return os.str();
}