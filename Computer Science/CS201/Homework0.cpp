#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Movie{
    private:
    string name;
    int year;
    vector<string> actors;
    public:
    void getMovie(string line);
    void printMovie();
};
int main(int argc, char** argv){
    string filename = argv[1];
    ifstream file(filename);
    string line;
    vector<Movie> movies;
    int i = 0;
    while(file >> line){
        Movie currmovie;
        currmovie.getMovie(line);
        movies.at(i) = currmovie;
        i++;
    }
    file.close();
}