/*Name: Luca Jontz
    Email: ldjontz@crimson.ua.edu
    Course Section: Fall 2023 CS 201
    Homework 1
    To Compile: g++ Homework1.cpp
    To execute: ./a.exe 
*/
#include <iostream>
#include <iterator>


using namespace std;

/*MaxHeapify(A, i){
    l=left(i)
    r=right(i)
    if l <= A.heap-size && A[l] > A[i]{
        largest = l
    }
    else largest = i
    if r <= A.heap-size && A[r] > A[largest]{
        largest = r
    }
    if largest != i{
        exchange A[i] with A[largest]
        MaxHeapify(A, largest)
    }
}*/

/*BuildMaxHeap(A, n){
    A.heap-size = n
    for i = n/2 downto 0{
        MaxHeapify(A, i)
    }
}*/



template <class RandomIt>
constexpr void heapsort(RandomIt first, RandomIt last){
    /*BuildMaxHeap(first, last)
    for i = last downto 1
        exchange first[0] with first[last]
        first.heap-size = first.heap-size - 1
        MaxHeapify(first, 0)*/
}

template <class RandomIt>
constexpr void quicksort(RandomIt first, RandomIt last){
    
}

int main(int argc, char** argv){

}