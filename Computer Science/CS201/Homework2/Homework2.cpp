#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <map>
#include <chrono>


using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
}

void mapsort(map<string, int> &map){
    vector<pair<string, int>> values;
    for(auto& it : map){
        values.push_back(it);
    }
    sort(values.begin(), values.end(), cmp);
    for(auto& it : values){
        cout << it.first << ": " << it.second << endl;
    }
}

int main(int argc, char** argv) {
   chrono::time_point<chrono::system_clock> start, end;
   start = chrono::system_clock::now(); //Start timing the entire program
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
   mapsort(tokens);
   end = chrono::system_clock::now(); //End time for program
   chrono::duration<double> elapsed_seconds = end - start;
   cout << "Time taken: " << elapsed_seconds.count() << endl;
}
