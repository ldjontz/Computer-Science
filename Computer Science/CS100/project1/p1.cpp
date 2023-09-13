#include <iostream>
#include <fstream>
#include <map>

using namespace std;


string decode(string message, map<char, char> key){
    string decodedMessage;
    for(char c : message){
        auto it = key.find(c);
        decodedMessage += (it != key.end() ? it->second : c);
    }
    return decodedMessage;
}

bool containsKeyword(string message, string keyWord){
    return message.find(keyWord) != string::npos;
}

bool updateKey(string ogmessage, string message, string keyWord, map<char, char> key){
    stack<pair<string, bool>> stateStack;
    stateStack.push(make_pair(message, false));
    while (!stateStack.empty()) {
        string message = stateStack.top().first;
        bool contains = stateStack.top().second;
        stateStack.pop();
        if (message.find(keyWord) == string::npos) {
            continue;
        }
        if (contains) {
            string alphas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            string tried;
            for (int i = 0; i < message.length(); i++) {
                if (isalpha(message[i])) {
                    if (ogmessage[i] == message[i]) {
                        contains = true;
                    }
                }
                if (contains) {
                    for (char c : alphas) {
                        if (tried.find(c) == string::npos) {
                            string decoded = message;
                            decoded[i] = c;
                            tried.push_back(c);
                            stateStack.push(make_pair(decoded, false));
                        }
                    }
                }
                tried.clear();
                contains = false;
            }
        } else {
            stateStack.push(make_pair(message, true));
        }
    }
    return false;
}
char missingChar(string word){
    string alphas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < 26; i++){
        if(word.find(alphas[i]) == string::npos){
            return alphas[i];
        }
    }
    return NULL;
}
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
    ifstream codeFile(fileTwo);
    string message;
    getline(codeFile, message);
    string decodedmessage = decode(message, key);
    updateKey(message, decodedmessage, keyWord, key);
    string alphas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<char, char>::iterator it = key.begin();
    key1 = "";
    key2 = "";
    while(it != key.end()){
        key2+= it->first;
        key1+= it->second;
    }
    key[missingChar(key2)] = missingChar(key1);
    decodedmessage = decode(message, key);
    cout << decodedmessage;
}