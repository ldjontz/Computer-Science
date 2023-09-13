#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

// Store the return of this function as an unsigned long!
unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}

int h2(string key, int a){
   return a - (djb2(key) % a);
}

bool contains(list<int> nums, int num){
   for(int i : nums){
      if(num == i) return true;
   }
   return false;
}

void printlist(list<int> nums, ostream &os){
   int size = nums.size();
   if(size == 1){
      auto it = nums.begin();
      os << *it;
      return;
   }
   auto last = nums.begin();
   for(auto it = nums.begin(); it!= prev(nums.end()); it++){
      os << *it <<",";
      last = it;
   }
   last++;
   os << *last;
}

class HashTable{
   private:
   int size, collisions, words;
   list<int> *linetable;
   list<string> *wordtable;
   public:
   HashTable(int n);
   bool insert(string word, int line, int key);
   bool search(ostream &os, string word, int key);
   int getWords();
   int getCollisions();
};

HashTable::HashTable(int n){
   this->size = n;
   linetable = new list<int>[size];
   wordtable = new list<string>[size];
   collisions = 0;
   words = 0;
}

bool HashTable::insert(string word, int line, int key){
   if(wordtable[key].empty()){
      wordtable[key].push_back(word);
      this->words++;
      linetable[key].push_back(line);
      return true;
      }
   else if(wordtable[key].front() == word){
      if(!contains(linetable[key], line)){
         linetable[key].push_back(line);
      }
      return true;
   }
   else{
      collisions++;
      return false;
   }
}



bool HashTable::search(ostream &os, string word, int key){
   if(wordtable[key].front() == word){
      os << word << " appears on lines [";
      printlist(linetable[key], os);
      os <<"]" << endl;
      return true;
   }
   if(wordtable[key].empty()){
      os << word << " appears on lines []" << endl;
      return true;
   }
   return false;
}
int HashTable::getWords(){
   return words;
}

int HashTable::getCollisions(){
   return collisions;
}

int main(int argc, char** argv) {
   string inputF = argv[1];
   string queryF = argv[2];
   string collision = argv[4];
   int a = 0;
   int size = atoi(argv[3]);
   if(argc == 6){
      a = atoi(argv[5]);
   }
   ifstream inputFile(inputF);
   string line;
   int linenumber = 1;
   int totalwords = 0;
   HashTable Hash(size);
   while(getline(inputFile, line)){
      vector<string> words;
      string word;
      for(char c : line){
         if(isalpha(c)){
            c = (char)tolower(c);
            word += c;
         }
         else if(!word.empty()){
            words.push_back(word);
            totalwords++;
            word.clear();
         }
      }
      if(!word.empty()){
         words.push_back(word);
         totalwords++;
      }
      int key = 0;
      for(string insertword : words){

         if(collision == "lp"){
            for(int i = 0; i < size; i++){
               key = (djb2(insertword) + i) % size;
               if(Hash.insert(insertword, linenumber, key)) break;
            }
         }
      
         if(collision == "qp"){
            for(int i = 0; i < size; i++){
               key = (djb2(insertword) + i*i) % size;
               if(Hash.insert(insertword, linenumber, key)) break;
            }
         }

         if(collision == "dh"){
            for(int i = 0; i < size; i++){
               key = (djb2(insertword) + i*h2(insertword, a)) % size;
               if(Hash.insert(insertword, linenumber, key)) break;
            }
         }
      }
      words.clear();
      linenumber++;
   }
   inputFile.close();
   cout << "The number of words found in the file was " << totalwords << endl;
   cout << "The number of unique words found in the file was " << Hash.getWords() << endl;
   cout << "The number of collisions was " << Hash.getCollisions() << endl;
   ifstream queryFile(queryF);
   string word;
   int key = 0;
   int searches = 0;
   while(queryFile >> word){
      cout << endl;
      searches = 0;
      if(collision == "lp"){
         for(int i = 0; i < size; i++){
            key = (djb2(word) + i) % size;
            if(Hash.search(cout, word, key)) break;
            searches++;
         }
      }
      if(collision == "qp"){
         for(int i = 0; i < size; i++){
            key = (djb2(word) + i*i) % size;
            if(Hash.search(cout, word, key)) break;
            searches++;
         }
      }
      if(collision == "dh"){
         for(int i = 0; i < size; i++){
            key = (djb2(word) + i*h2(word, a)) % size;
            if(Hash.search(cout, word, key)) break;
            searches++;
         }
      }
      cout << "The search had " << searches << " collisions" << endl;
   }
   queryFile.close();
   return 0;
}
