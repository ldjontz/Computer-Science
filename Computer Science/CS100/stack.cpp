#include <vector>
#include <iostream>

using namespace std;

bool exists(char array[], char c){
    for(int i = 0; i < 4; i++){
        if(c == array[i]) return true;
    }
    return false;
}
bool match(char array1[], char c1, char array2[], char c2){
    int count1 = 0;
    int count2 = 0;
    for(int i = 0; i < 4; i++){
        if(c1 == array1[i]) break;
        count1++;
    }
    for(int i = 0; i < 4; i++){
        if(c2 == array2[i]) break;
        count2++;
    }
    if (count1 == count2) return true;
    return false;
}
class Stack {
    private:
        vector<char> v;
    public:
        void push(char c){
            v.push_back(c);
        }
        char pop(){
            char c = v.back();
            v.pop_back();
            return c;
        }
        char peak(){
            return v.back();
        }
        bool isEmpty(){
            return v.empty();
        }
        int size(){
            return v.size();
        }
        void print(ostream &os){
            int size = v.size();
            for(int i = 0; i < size; i++){
                cout << v.at(i) << " ";
            }
        }
        bool contains(char c){
            int size = v.size();
            for(int i = 0; i < size; i++){
                if(v.at(i) == c) return true;
            }
            return false;
        }
};
int main(int argc, char **argv){
    string command = argv[1];
    Stack myStack;
    char openers[4] = {'(', '{', '[', '<'};
    char closers[4] = {')', '}', ']', '>'};
    int length = command.length();
    for(int i = 0; i < length; i++){
        cout << "Stack: ";
        myStack.print(cout);
        cout << endl;
        cout << "Character: " << command[i] << endl;
        bool opener = exists(openers, command[i]);
        if(opener){
            cout << "Push" << endl;
            myStack.push(command[i]);
            continue;
        }
        bool closer = exists(closers, command[i]);
        if(closer){
            bool matching = match(openers, myStack.peak(), closers, command[i]);
            if(!matching){
                if(myStack.isEmpty()) cout <<"Error: unmatched right symbol " << command[i] << endl;
                else cout << "Error: mismatched pair " << myStack.peak() << " and " << command[i] <<endl;
                return 0;
            }
            cout << "Matching " << myStack.pop() << " and " << command[i] << endl;
            cout << "Pop" << endl;
            continue;
        }
        else{
            cout << "Error: invalid character " << command[i] << endl;
            return 0;
        }
    }
    cout << "Stack: ";
    myStack.print(cout);
    cout << endl;
    cout << "Reached end of string" << endl;
    if(!myStack.isEmpty()){
        cout << "Error: unmatched left symbol " << myStack.peak() << endl;
    }
    else cout << "String is properly balanced" << endl;
}