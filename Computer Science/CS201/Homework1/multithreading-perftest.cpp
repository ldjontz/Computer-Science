#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include <mutex>
// input your file up here

std::mutex mtx; // Mutex for preventing race conditions, stopping outputs until the order is ready

void printHeaders() {
    std::cout << "Problem Size\tTime Taken (seconds)" << std::endl;
    std::cout << "\t\tCase 1\tCase 2\tCase 3" << std::endl;
}

void printResults(int size, std::chrono::duration<double> (&timetaken)[3][3]) {
    std::cout << size << "\t\t";
    std::cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count()) / 3.0 << "\t";
    std::cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count()) / 3.0 << "\t";
    std::cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count()) / 3.0 << std::endl;
}


typedef void (*SortFunctionType)(int*, int*);

void testSort(int size, int i, std::chrono::duration<double> (&timetaken)[3][3], SortFunctionType sortFunction) {
    int *a = new int[size];
    std::generate(a, a + size, std::rand);

    /* Case 1: sorting random values */
    auto starttime = std::chrono::steady_clock::now();
    sortFunction(a, a + size);
    auto endtime = std::chrono::steady_clock::now();
    mtx.lock();
    timetaken[i][0] = endtime - starttime;
    mtx.unlock();

    /* Case 2: sorting data that is already sorted */
    starttime = std::chrono::steady_clock::now();
    sortFunction(a, a + size);
    endtime = std::chrono::steady_clock::now();
    mtx.lock();
    timetaken[i][1] = endtime - starttime;
    mtx.unlock();

    /* Case 3: sorting data that is in reverse sorted order */
    std::reverse(a, a + size);
    starttime = std::chrono::steady_clock::now();
    sortFunction(a, a + size);
    endtime = std::chrono::steady_clock::now();
    mtx.lock();
    timetaken[i][2] = endtime - starttime;
    mtx.unlock();

    delete[] a;
}

int main(int argc, char *argv[]) {
    std::chrono::duration<double> timetaken[3][3];

    std::cout << "Quick Sort: " << std::endl;
    printHeaders();

    for (int size = 10; size <= 100000000; size *= 10) {
        std::vector<std::thread> threads;
        for (int i = 0; i < 3; i++) {
            // Change the function here
            threads.push_back(std::thread(testSort, size, i, std::ref(timetaken), static_cast<SortFunctionType>(quicksort)));
        }

        for (auto& th : threads) {
            th.join();
        }
        
        printResults(size, timetaken);
    }

    std::cout << "Heap Sort: " << std::endl;
    printHeaders();

    for (int size = 10; size <= 100000000; size *= 10) {
        std::vector<std::thread> threads;
        for (int i = 0; i < 3; i++) {
            // Change the function here
            threads.push_back(std::thread(testSort, size, i, std::ref(timetaken), static_cast<SortFunctionType>(heapsort)));
        }

        for (auto& th : threads) {
            th.join();
        }
        
        printResults(size, timetaken);
    }

    return 0;
}


