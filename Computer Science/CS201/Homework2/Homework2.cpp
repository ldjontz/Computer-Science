/*
    Name: Luca Jontz
    Email: ldjontz@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Homework 2
    Instructions to Compile: g++ Homework2.cpp
    Instructions to execute: ./a.exe input1.txt
*/
#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <map>
#include <chrono>


using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b){
    if(a.second == b.second){ //if same number of occurences
        return a.first < b.first; //return in alphabetical order
    }
    return a.second < b.second; //return by number of occurences
}

void mapsort(map<string, int> &map){
    vector<pair<string, int>> values;
    for(auto& it : map){ //convert map to vector of pairs
        values.push_back(it);
    }
    sort(values.begin(), values.end(), cmp); //sort the vector of pairs
    for(auto& it : values){ //output the vector of pairs
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
   int wordcount = 0;
   while (inputFile >> text) {
      auto begin = sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = sregex_token_iterator();
      for (sregex_token_iterator word = begin; word != end; word++) { //parse through the file and add unique words to the map, if not unique increment the number of occurences
         it = tokens.find(*word);
         if(it == tokens.end()){
            tokens[*word] = 1;
         }
         else{
            tokens[*word]++;
         }
        wordcount++; 
      }
   }
   mapsort(tokens); //sort the map
   end = chrono::system_clock::now(); //End time for program
   chrono::duration<double> elapsed_seconds = end - start;
   cout << "Number of words: " << wordcount << endl;
   cout << "Time taken: " << elapsed_seconds.count() << endl; //output the time taken
}
