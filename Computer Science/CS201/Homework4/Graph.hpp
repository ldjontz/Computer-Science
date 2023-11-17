/*
    Name: Luca Jontz
    Email: ldjontz@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Homework 4
    Instructions to Compile: g++ -Wall -std=c++20 GraphDemo.cpp
    Instructions to execute: ./a.exe input1.txt
*/
#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>
#define INFINITY std::numeric_limits<int>::infinity();

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;
                    vertices[i].distance = INFINITY;
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		for(int i = 0; i < _V; i++){
			vertices[i].visited = false;
			vertices[i].distance = INFINITY;
			vertices[i].previous = -1;
		}
		vertices[s].visited = true;
		vertices[s].distance = 0;
		vertices[s].previous = -1;
		std::queue<int> Q;
		Q.push(s);
		while(!Q.empty()){
			int u = Q.front();
			Q.pop();
			for(int i : vertices[u].adj){
				if(vertices[i].visited == false){
					vertices[i].visited = true;
					vertices[i].distance = vertices[u].distance + 1;
					vertices[i].previous = u;
					Q.push(i);
				}
			}
		}

	}

	void dfs() {
		for(int i = 0; i < _V; i++){
			vertices[i].visited = false;
			vertices[i].previous = -1;
		}
		for(int i = 0; i < _V; i++){
			if(!vertices[i].visited){
				dfs_visit(i);
			}
		}
	}

	void dfs_visit(int u) {
		int time = 1;
		vertices[u].distance = time;
		vertices[u].visited = true;
		for(int v : vertices[u].adj){
			if(!vertices[v].visited){
				vertices[v].previous = u;
				dfs_visit(v);
			}
		}
		time++;
		vertices[u].finish = time;
		std::cout << u << " ";
	}

	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
};

#endif
