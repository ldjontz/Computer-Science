/*
    Name: Luca Jontz
    Email: ldjontz@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Homework 3
    Instructions to Compile: g++ Homework3.cpp
    Instructions to execute: ./a.exe dbfile1.txt query.txt
*/
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]) {
	chrono::time_point<chrono::system_clock> totalstart, totalend, maptimes, maptimee, searchtimes, searchtimee;
	totalstart = chrono::system_clock::now(); //Start timing the entire program
	int i = 0;
	// check for correct command-line arguments
	if (argc != 3) {
	   std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
	   std::exit(-1);
	}

	std::string line, name;
	std::regex delim("/");
	std::ifstream dbfile(argv[1]);
	if (!dbfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[1] << std::endl;
	   std::exit(-1);
	}

	unordered_map<string, string> movies;
	unordered_map<string, string> actors;
	string moviename;
	int records = 0;
	maptimes = chrono::system_clock::now(); //start timing the time to create data structure
	while (std::getline(dbfile, line)) {
	   // parse each line for tokens delimited by "/"
	   auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
	   auto end = std::sregex_token_iterator();
	   moviename = *begin; //get the movie name of the line
	   ++begin;
	   movies[moviename] = *begin; //map the movie using the movie name as the key and the first actor in it as the value
	   if(actors.find(*begin) == actors.end()){ //execute if the actor does not already exist in the actors map
		actors[*begin] = moviename; //map the actor using the actor as the key and the first movie they appear in as the value
	   }
	   else{
		actors[*begin] += "\n";
		actors[*begin] += moviename; //add this movie to this actors list of appearances
	   }
	   ++begin; //go to the next actor
	   for (std::sregex_token_iterator word = begin; word != end; ++word) {
		movies[moviename] += "\n";
		movies[moviename] += *word; //add this actor to this movie
		if(actors.find(*word) == actors.end()){ //execute if the actor does not already exist in the actors map
			actors[*word] = moviename; //map the actor using the actor as the key and the first movie they appear in as the value
		}
		else{
			actors[*word] += "\n";
			actors[*word] += moviename; //add this movie to this actors list of appearances
		}
	   }
	   records++; //increment the number of records
	}
	maptimee = chrono::system_clock::now(); //end timing the time to create data structure
	chrono::duration<double> elapsed_seconds = maptimee - maptimes;
	std::cout << "Time taken to create data structure: " << elapsed_seconds.count() << endl;
	dbfile.close();
	ofstream outputfile("outputfile.txt");
	std::ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[2] << std::endl;
	   std::exit(-1);
	}

	searchtimes = chrono::system_clock::now(); //start timing the search
	while (std::getline(queryfile, name)) {
	   if(movies.find(name) == movies.end() && actors.find(name) == actors.end()){
		outputfile << name << " Not found" << endl;
	   }
	   else{
		if(movies.find(name) == movies.end()){ //check if this is a movie, if not execute
			outputfile << "Movies that \"" << name << "\" has appeared in:\n" << actors[name] << endl;
		}
		else{
			outputfile << "Actors in \"" << name << "\":\n" << movies[name] << endl;
		}
	   }
	}
	searchtimee = chrono::system_clock::now(); //end timing the search
	elapsed_seconds = searchtimee - searchtimes;
	std::cout << "Search time: " << elapsed_seconds.count() << endl;
	queryfile.close();
	std::cout << "Records: " << records << endl;
	totalend = chrono::system_clock::now(); //End time for program
	elapsed_seconds = totalend - totalstart;
	std::cout << "Total time taken: " << elapsed_seconds.count() << endl; //output the time taken
	return 0;
}
