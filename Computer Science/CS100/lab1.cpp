#include <iostream>
#include <cstring>
#include <fstream>

// Include any necessary libraries here.

using namespace std;

int main() {

   string fileName;
   cin >> fileName;
   ifstream file;
   file.open(fileName);
   string line;
   int index;
   while(!file.eof()){
      getline(file, line);
      line.replace(line.find("_"), 10, "_info.txt");
      cout << line << endl;
   }

   return 0;
}
