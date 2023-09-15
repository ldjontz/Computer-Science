/*
    Name: Luca Jontz
    Email: ldjontz@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Homework 0
    Instructions to Compile: g++ Homework0.cpp
    Instructions to execute: ./a.exe dbfile1.txt
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>

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

bool compareMovieName(Movie movie1, Movie movie2){ //Comparison function to sort movie by name
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

bool compareMovieYear(Movie movie1, Movie movie2){ //Comparison function to sort movie by year
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

void Movie::getMovie(string line){ //Take input line and get the movie's attributes
    name = line.substr(0, line.find("("));
    string temp;
    year = line.substr(line.find("(") + 1, 4);
    line = line.substr(line.find("/") + 1);
    istringstream actornames(line);
    while(getline(actornames, temp, '/')){
        actors.push_back(temp);
    }
}

string Movie::printMovie(){ //Take the movie's attributes and format them correctly to be printed
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

vector<Movie> sortName(vector<Movie> movies){ //Function to sort movies by name
    sort(movies.begin(), movies.end(), compareMovieName);
    return movies;
}

vector<Movie> sortYear(vector<Movie> movies){ //Function to sort movies by year
    sort(movies.begin(), movies.end(), compareMovieYear);
    return movies;
}




int main(int argc, char** argv){
    chrono::time_point<chrono::system_clock> totalstart, totalend;
    totalstart = chrono::system_clock::now(); //Start timing the entire program
    string filename = argv[1];
    ifstream file(filename);
    string line;
    vector<Movie> movies; //Create a vector to hold all the Movie objects
    int i = 0;
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now(); //Start time for creating the collection
    while(getline(file, line)){ //Get each movie from the file and pass it to getMovie, then add it to the vector of Movies
        Movie currmovie;
        currmovie.getMovie(line);
        movies.push_back(currmovie);
        i++;
    }
    end = chrono::system_clock::now(); //End time for creating the collection
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Time taken to create collection: " << elapsed_seconds.count() << endl;
    cout << i << " records" << endl;
    file.close();
    start = chrono::system_clock::now(); //Start time for sort based on movie name
    vector<Movie> names = sortName(movies);
    end = chrono::system_clock::now(); //End time for sort based on movie name
    elapsed_seconds = end - start;
    cout << "Time taken to sort by name: " << elapsed_seconds.count() << endl;
    filename = filename.substr(0, filename.find("."));
    ofstream namefile(filename + "ByName.txt");
    for(Movie currmovie : names){ //Loop through sorted movie vector by name and write them to the sorted by name file
        namefile << currmovie.printMovie() << endl;
    }
    namefile.close();
    start = chrono::system_clock::now(); //Start time for sort based on movie year
    vector<Movie> years = sortYear(movies);
    end = chrono::system_clock::now(); //End time for sort based on movie year
    elapsed_seconds = end - start;
    cout << "Time taken to sort by year: " << elapsed_seconds.count() << endl;
    ofstream yearfile(filename + "ByYear.txt");
    for(Movie currmovie : years){ //Loop through sorted movie vector by year and write them to the sorted by year file
        yearfile << currmovie.printMovie() << endl;
    }
    yearfile.close();
    totalend = chrono::system_clock::now(); //End time for the entire program
    elapsed_seconds = totalend - totalstart;
    cout << "Total time taken: " << elapsed_seconds.count() << endl;
}