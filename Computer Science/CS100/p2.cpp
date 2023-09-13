#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

bool findInt(vector<int> nums, int val){
    int count = 0;
    int size = nums.size();
    for(int i = 0; i < size; i++){
        if(val == nums.at(i)){
            count ++;
        }
    }
    if(count > 0){
        return true;
    }
    else{
        return false;
    }
}

bool findString(vector<string> strings, string val){
    int count = 0;
    int size = strings.size();
    for(int i = 0; i < size; i++){
        if(val == strings.at(i)){
            count ++;
        }
    }
    if(count > 0){
        return true;
    }
    else{
        return false;
    }
}

void Merge(int numbers[], int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] < numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
}

int Partition(string strings[], int i, int k) {
   int l;
   int h;
   int midpoint;
   string pivot;
   string temp;
   bool done;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = strings[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (strings[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < strings[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = strings[l];
         strings[l] = strings[h];
         strings[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort(string strings[], int i, int k) {
   int j;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(strings, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort(strings, i, j);
   Quicksort(strings, j + 1, k);
}

int main(int argc, char *argv[]){
    string arg1 = argv[1];
    string filename = argv[2];
    ifstream file1(filename);
    filename = argv[3];
    ifstream file2(filename);
    if(arg1[0] == 'i'){
        int val;
        vector<int> filenums;
        while(file1 >> val){
            filenums.push_back(val);
        }
        vector<int> filenums2;
        while(file2 >> val){
            filenums2.push_back(val);
        }
        vector<int> nums;
        int size1 = filenums.size();
        int size2 = filenums2.size();
        for(int i = 0; i < size1; i++){
            for(int j = 0; j < size2; j++){
                bool exists = findInt(nums, filenums2.at(j));
                int test = filenums.at(i) - filenums2.at(j);
                if(test == 0 && !exists){
                    nums.push_back(filenums2.at(j));
                }
            }
        }
        int numarray[nums.size()];
        int size = nums.size();
        for(int i = 0; i < size; i++){
            numarray[i] = nums.at(i);
        }
        MergeSort(numarray, 0, nums.size() - 1);
        for(int i = 0; i < size; i++){
            cout << numarray[i] << endl;
        }
    }
    else if(arg1[0] == 's'){
        string val;
        vector<string> filestrings;
        while(file1 >> val){
            filestrings.push_back(val);
        }
        vector<string> filestrings2;
        while(file2 >> val){
            filestrings2.push_back(val);
        }
        vector<string> strings;
        int size1 = filestrings.size();
        int size2 = filestrings2.size();
        for(int i = 0; i < size1; i++){
            for(int j = 0; j < size2; j++){
                bool exists = findString(strings, filestrings2.at(j));
                if(filestrings.at(i) == filestrings2.at(j) && !exists){
                    strings.push_back(filestrings2.at(j));
                }
            }
        }
        string stringarray[strings.size()];
        int size = strings.size();
        for(int i = 0; i < size; i++){
            stringarray[i] = strings.at(i);
        }
        Quicksort(stringarray, 0, strings.size() - 1);
        for(int i = 0; i < size; i++){
            cout << stringarray[i] << endl;
        }
    }
}