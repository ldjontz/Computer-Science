#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char **argv){
    string fileOne = argv[1];
    string fileTwo = argv[2];
    string keyWord = argv[3];
    string key1;
    string key2;
    ifstream keyFile(fileOne);
    keyFile >> key1 >> key2;
    keyFile.close();
    int keylen = key1.length();
    map<char, char> key;
    for(int i = 0; i < keylen; i++){
        key[key2[i]] = key1[i];
    }
    
}