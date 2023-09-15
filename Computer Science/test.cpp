#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Movie{
    private:
    string name;
    string year;
    vector<string> actors;
    public:
    void getMovie(string line);
    string printMovie();
    string getName();
    string getYear();
};

bool compareMovieName(Movie movie1, Movie movie2){
    string name1 = movie1.getName();
    string name2 = movie2.getName();
    string year1 = movie1.getYear();
    string year2 = movie2.getYear();
    if(name1.compare(name2) < 0){
        return true;
    }
    else if(name1.compare(name2) == 0){
        return (year1.compare(year2) < 0);
    }
    else{
        return false;
    }
}

bool compareMovieYear(Movie movie1, Movie movie2){
    string name1 = movie1.getName();
    string name2 = movie2.getName();
    string year1 = movie1.getYear();
    string year2 = movie2.getYear();
    if(year1.compare(year2) < 0){
        return true;
    }
    else if(year1.compare(year2) == 0){
        return (name1.compare(name2) < 0);
    }
    else{
        return false;
    }
}

void Movie::getMovie(string line){
    name = line.substr(0, line.find("("));
    string temp;
    year = line.substr(line.find("(") + 1, 4);
    line = line.substr(line.find("/") + 1);
    istringstream actornames(line);
    while(getline(actornames, temp, '/')){
        actors.push_back(temp);
    }
}

string Movie::printMovie(){
    string line = name + "(" + year + ")";
    for(string actor : actors){
        line += "/" + actor;
    }
    return line;
}

string Movie::getName(){
    return name;
}

string Movie::getYear(){
    return year;
}

vector<Movie> sortName(vector<Movie> movies){
    sort(movies.begin(), movies.end(), compareMovieName);
    return movies;
}

vector<Movie> sortYear(vector<Movie> movies){
    sort(movies.begin(), movies.end(), compareMovieYear);
    return movies;
}

int main(){
    string line = "Jokes My Folks Never Told Me (1978)/De La Croix, Raven/Drake, Marciee/Dutch, Deborah/Giroux, Jackie/Johnson, Sandy/Roberts, Mariwin";
    Movie movies;
    movies.getMovie(line);
    cout << movies.printMovie();
}