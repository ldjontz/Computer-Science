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
    BuildMaxHeap(first, size);
    for (int i = n; i > 0; i--){
        iter_swap(first, first + i);
        n--;
        MaxHeapify(first, 0, n);
    }
}

/*template <class RandomIt>
constexpr int partition(RandomIt first, RandomIt last){
    auto pivot = *last;
}

template <class RandomIt>
constexpr void quicksort(RandomIt first, RandomIt last){
    RandomIt it = first;
    if(0 < last - first){
        int pivot = partition(first, last);
        advance(it, pivot - 1);
        quicksort(first, it);
        advance(it, 2);
        quicksort(it, last);
    }
}
*/
template< class RandomIt >
void print(RandomIt start, RandomIt end) {
	while (start != end) {
		std::cout << *start << " ";
		++start;
	}
	std::cout << std::endl;
}


int main(int argc, char *argv[]) {
	int a0[] = {56, 23, 11, 64, 43};
	std::array<int, 5> a1 = {5, 4, 3, 2, 1};
	std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
	std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

	heapsort(a0, a0+5);
	print(a0, a0+5);

	heapsort(&a0[0], &a0[5]);
	print(&a0[0], &a0[5]);

	heapsort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	heapsort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	heapsort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	heapsort(v.begin(), v.end());
	print(v.begin(), v.end());

	return 0;
}