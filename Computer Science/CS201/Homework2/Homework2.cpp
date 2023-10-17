#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char** argv) {
   string text;
   map<string, int> tokens;
   const regex delim("\\s+");
   string filename = argv[1];
   ifstream inputFile(filename);
   map<string, int>::iterator it = tokens.begin(); 

   while (inputFile >> text) {
      auto begin = sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = sregex_token_iterator();
      for (sregex_token_iterator word = begin; word != end; word++) {
         it = tokens.find(*word);
         if(it == tokens.end()){
            tokens[*word] = 1;
         }
         else{
            tokens[*word]++;
         }
      }
   }

   for(const auto & str : tokens)
      cout << str << endl;

   return 0;
}
