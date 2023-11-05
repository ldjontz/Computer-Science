// C++ program for the above approach 
 
#include <iostream>
#include <unordered_map>
using namespace std; 

// Driver Code 
int main(){
    unordered_map<string, string> umap;
    umap["test"] = "james";
    umap["test"] += "\nbond";
    cout << umap["test"];
}