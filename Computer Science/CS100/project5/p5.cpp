#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class node{
public:
    node *leftChild;
    node *rightChild;
    int value;
};

class HuffmanTree{
public:    
    node *root;
    node *buildTree(vector<int> levelorder, vector<int> inorder);
};


node *HuffmanTree::buildTree(vector<int> levelorder, vector<int> inorder){
    int size = levelorder.size();
    node *currnode = new node;
    if(size == 1){
        currnode->value = levelorder.at(0);
        currnode->leftChild = nullptr;
        currnode->rightChild = nullptr;
        return currnode;
    }
    if(size == 0){
        return nullptr;
    }
    int root = levelorder.at(0);
    int index = 0;
    currnode->value = root;
    vector<int> leftlevel, leftorder, rightlevel, rightorder;
    for(index = 0; index < size; index++){
        if(inorder.at(index) == root) break;
        leftorder.push_back(inorder.at(index));
    }
    index++;
    for(index; index < size; index++){
        rightorder.push_back(inorder.at(index));
    }
    for(index = 0; index < size; index++){
        if(count(leftorder.begin(), leftorder.end(), levelorder.at(index))){
            leftlevel.push_back(levelorder.at(index));
        }
    }
    for(index = 0; index < size; index++){
        if(count(rightorder.begin(), rightorder.end(), levelorder.at(index))){
            rightlevel.push_back(levelorder.at(index));
        }
    }
    currnode->leftChild = buildTree(leftlevel, leftorder);
    currnode->rightChild = buildTree(rightlevel, rightorder);
    return currnode;
}

int main(int argc, char** argv){
    string inorderf = argv[1];
    string levelorderf = argv[2];
    string encodedf = argv[3];
    ifstream inFile(inorderf);
    ifstream levelFile(levelorderf);
    ifstream encodeFile(encodedf);
    int value = 0;
    vector<int> levelorder;
    vector<int> inorder;
    while(inFile >> value){
        inorder.push_back(value);
    }
    while(levelFile >> value){
        levelorder.push_back(value);
    }
    inFile.close();
    levelFile.close();
    HuffmanTree tree;
    tree.root = tree.buildTree(levelorder, inorder);
    node *currnode = new node;
    currnode = tree.root;
    string line;
    string decode;
    while(getline(encodeFile, line)){
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        for(char c : line){
            int direction = int(c) - 48;
            if(direction == 0) currnode = currnode->leftChild;
            if(direction == 1) currnode = currnode->rightChild;
            if(currnode->leftChild == nullptr && currnode->rightChild == nullptr){
                decode += char(currnode->value);
                currnode = tree.root;
            }
        }
    }
    cout << decode;
}