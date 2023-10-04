/*Name: Luca Jontz
    Email: ldjontz@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Homework 1
    To Compile: g++ Homework1.cpp
    To execute: ./a.exe 
*/
#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

int left(int i){
    return (2*i + 1);
}

int right(int i){
    return (2*i + 2);
}

template <class RandomIt>
constexpr void MaxHeapify(RandomIt first, int i, int size){
    int l = left(i); //obtain index of i's left child
    int r = right(i); //obtain index of i's right child
    int largest = i;
    if (l <= size &&  first[i] < first[l]){ //execute if index is inbounds and lchild is greater than i value
        largest = l; //assign largest with index of lchild
    }
    if (r <= size && first[largest] < first[r]){ //execute if index is inbounds and rchild is greater than largestvalue
        largest = r; //assign largest with index of rchild
    }
    if (largest != i){ //execute if largest is not assigned to index i, (either lchild index or rchild index)
        iter_swap(first + i, first + largest);//swap iindex and largest values
        MaxHeapify(first, largest, size);
    }
}

template <class RandomIt>
constexpr void BuildMaxHeap(RandomIt first, int n){
    for (int i = (n/2) - 1; i >= 0; i--){
        MaxHeapify(first, i, n);
    }
}



template <class RandomIt>
constexpr void heapsort(RandomIt first, RandomIt last){
    int n = last - first - 1;
    int size = last - first;
    BuildMaxHeap(first, size); //Move largest element to the front
    for (int i = n; i > 0; i--){
        iter_swap(first, first + i); // Move largest element to the back
        n--; //Decrease the size of the array that needs to be sorted
        MaxHeapify(first, 0, n); //Move the new largest element to the front
    }
}

template <class RandomIt>
constexpr RandomIt partition(RandomIt first, RandomIt last){
    RandomIt pivot = first + (last - first) / 2; //Obtain middle pivot
    RandomIt i = first - 1;
    iter_swap(pivot, last - 1); //Move pivot the back
    for(RandomIt it = first; it < last - 1; it++){
        if(*it <= *(last - 1)){ //Execute if element is smaller than pivot value
            i++; //Increment index to place element
            iter_swap(i, it); //Place element at that index
        }
    }
    iter_swap(i + 1, last - 1); //Move pivot to correct position
    return i + 1; //return pivot index
}

template <class RandomIt>
constexpr void quicksort(RandomIt first, RandomIt last){
    if(first < last){
        RandomIt pivot = partition(first, last); //Obtain pivot
        quicksort(first, pivot); //Recursively sort
        quicksort(pivot + 1, last); //Recursively sort
    }
}

template< class RandomIt >

void print(RandomIt start, RandomIt end) {
	while (start != end) {
		std::cout << *start << " ";
		++start;
	}
	std::cout << std::endl;
}


int main(int argc, char *argv[]) {
	std::chrono::duration<double> timetaken[3][3];
	std::cout << "Problem Size\tTime Taken (seconds)" << std::endl;
	std::cout << "\t\tCase 1\tCase 2\tCase 3" << std::endl;
	for (int size = 10; size <= 100000000; size *= 10) {
	
		int *a = new int[size];

		// repeat each case for three times 
		for (int i = 0; i < 3; i++) {
			std::generate(a, a+size, std::rand);

			/* Case 1: sorting random values */
			auto starttime = std::chrono::steady_clock::now();
			std::sort(a, a+size);
			auto endtime = std::chrono::steady_clock::now();
			timetaken[i][0] = endtime - starttime;

			/* Case 2: sorting data that is already sorted */
			starttime = std::chrono::steady_clock::now();
			std::sort(a, a+size);
			endtime = std::chrono::steady_clock::now();
			timetaken[i][1] = endtime - starttime;

			/* Case 3: sorting data that is in reverse sorted order */
			std::reverse(a, a+size);
			starttime = std::chrono::steady_clock::now();
			std::sort(a, a+size);
			endtime = std::chrono::steady_clock::now();
			timetaken[i][2] = endtime - starttime;
		}

		// print the average time of three runs
		std::cout << size << "\t\t";
		std::cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count())/3.0 << "\t";
		std::cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count())/3.0 << "\t";
		std::cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count())/3.0 << std::endl;

		delete[] a;
	}

	return 0;
}