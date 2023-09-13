#include <iostream>

using namespace std;

class MyDynamicArray {
    private:
        int size, capacity, error;
        int *a;
    public:
        MyDynamicArray() {
           capacity = 2;
           size = 0;
           error = 0;
           a = new int[capacity];
        }
        MyDynamicArray(int s) {
            capacity = s;
            size = s;
            error = 0;
            a = new int[capacity];
        }
        int& operator[](int i){
            if(i >= size){
                cout << "Out of bounds reference : " << i << endl;
                return error;
            }
            return a[i];
        }
        void add(int v) {
            if(size == capacity){
                capacity *= 2;
                cout << "Doubling to : " << capacity << endl;
            }
            int *temp = new int[capacity];
            for(int i = 0; i < size; i++){
                temp[i] = a[i];
            }
            delete [] a;
            a = new int[capacity];
            for(int i = 0; i < size; i++){
                a[i] = temp[i];
            }
            delete [] temp;
            a[size] = v;
            size += 1;
        }
        void del() {
            if(size <= capacity / 4){
                capacity /= 2;
                cout << "Reducing to : " << capacity << endl;
            }
            int *temp = new int[capacity];
            size -= 1;
            for(int i = 0; i < size; i++){
                temp[i] = a[i];
            }
            delete [] a;
            a = new int[capacity];
            for(int i = 0; i < size; i++){
                a[i] = temp[i];
            }
            delete [] temp;
        }
        int length() {
            return size;
        }
        void clear() {
            delete [] a;
            capacity = 2;
            size = 0;
            a = new int[capacity];
        }
        ~MyDynamicArray(){
            cout << "In the destructor" << endl;
            delete []a;
        }
        MyDynamicArray& operator=(const MyDynamicArray& src){
            cout << "In the copy assignment operator" << endl;
            size = src.size;
            capacity = src.capacity;
            error = src.error;
            for(int i = 0; i < size; i++){
                a[i] = src.a[i];
            }
            return *this;
        }
        MyDynamicArray(const MyDynamicArray& src){
            cout << "In the copy constructor" << endl;
            a = new int[src.capacity];
            size = src.size;
            capacity = src.capacity;
            error = src.error;
            for(int i = 0; i < size; i++){
                a[i] = src.a[i];
            }
        }
};
