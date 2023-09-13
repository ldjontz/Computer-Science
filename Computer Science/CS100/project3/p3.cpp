#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

void Person::Print(ostream &os){
    os << first << " " << last << ": height=" << height << ", weight=" << weight << endl;
}

Person PersonList::compare(Person person1, Person person2){
    if(person1.weight == person2.weight){
        if(person1.height > person2.height){
            return person1;
        }
        else if(person2.height > person1.height){
            return person2;
        }
    }
    if(person1.height == person2.height){
        if(person1.weight > person2.weight){
            return person2;
        }
        else if(person2.weight > person1.weight){
            return person1;
        }
    }
    return person2;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person *current = headHeightList;
    for(int i = 0; i < size; i++){
        current->Print(os);
        current = current->nextHeight;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person *current = headWeightList;
    for(int i = 0; i < size; i++){
        current->Print(os);
        current = current->nextWeight;
    }
}

bool PersonList::exists(string first, string last)
{
    Person *current = headHeightList;
    while(current != nullptr){
        if(first == current->first && last == current->last){
            return true;
        }
        current = current->nextHeight;
    }
    current = headWeightList;
    while(current != nullptr){
        if(first == current->first && last == current->last){
            return true;
        }
        current = current->nextWeight;
    }
    return false;
}

int PersonList::getHeight(string first, string last) {
    if(!exists(first, last)){
        return -1;
    }
    Person *current = headHeightList;
    while(current != nullptr){
        if(current->first == first && current->last == last){
            break;
        }
        current = current->nextHeight;
    }
    return current->height;
}

int PersonList::getWeight(string first, string last) {
    if(!exists(first, last)){
        return -1;
    }
    Person *current = headWeightList;
    while(current != nullptr){
        if(current->first == first && current->last == last){
            break;
        }
        current = current->nextWeight;
    }
    return current->weight;
}

bool PersonList::add(string first, string last, int height, int weight)
{
    if (this->exists(first, last))
    {
        return false;
    }
    Person *p = new Person(first, last, height, weight);
    size++;
	// add it to "headHeightList"
    if(headHeightList == nullptr){
        headHeightList = p;
        headWeightList = p;
        p->nextHeight = nullptr;
        p->nextWeight = nullptr;
        return true;
    }
	bool added = false;
    if(p->height > headHeightList->height){
        p->nextHeight = headHeightList;
        headHeightList = p;
        added = true;
    }
    if(!added){
        if(p->height == headHeightList->height){
            Person check = compare(*p, *headHeightList);
            if(check.first == headHeightList->first && check.last == headHeightList->last){
                p->nextHeight = headHeightList->nextHeight;
                headHeightList->nextHeight = p;
                added = true;
            }
            else{
                p->nextHeight = headHeightList;
                headHeightList = p;
                added = true;
            }
        }
    }
    Person *previous = headHeightList;
    Person *current = headHeightList->nextHeight;
    if(!added){
        while(current != nullptr){
            if(p->height > current->height){
                previous->nextHeight = p;
                p->nextHeight = current;
                break;
            }
            else if(p->height == current->height){
                Person check = compare(*p, *current);
                if(check.first == current->first && check.last == current->last){
                    p->nextHeight = current->nextHeight;
                    current->nextHeight = p;
                    break;
                }
                else{
                    previous->nextHeight = p;
                    p->nextHeight = current;
                    break;
                }
            }
            previous = current;
            current = current->nextHeight;
        }
        if(current == nullptr){
            previous->nextHeight = p;
            p->nextHeight = nullptr;
        }
    }
    added = false;
	// add it to "headWeightList"
	if(p->weight < headWeightList->weight){
        p->nextWeight = headWeightList;
        headWeightList = p;
        added = true;
    }
    if(!added){
        if(p->weight == headWeightList->weight){
            Person check = compare(*p, *headWeightList);
            if(check.first == headWeightList->first && check.last == headWeightList->last){
                p->nextWeight = headWeightList->nextWeight;
                headWeightList->nextWeight = p;
                added = true;
            }
            else{
                p->nextWeight = headWeightList;
                headWeightList = p;
                added = true;
            }
        }
    }
    previous = headWeightList;
    current = headWeightList->nextWeight;
    if(!added){
        while(current != nullptr){
            if(p->weight < current->weight){
                previous->nextWeight = p;
                p->nextWeight = current;
                break;
            }
            else if(p->weight == current->weight){
                Person check = compare(*p, *current);
                if(check.first == current->first && check.last == current->last){
                    p->nextWeight = current->nextWeight;
                    current->nextWeight = p;
                    break;
                }
                else{
                    previous->nextWeight = p;
                    p->nextWeight = current;
                    break;
                }
            }
            previous = current;
            current = current->nextWeight;
        }
        if(current == nullptr){
            previous->nextWeight = p;
            p->nextWeight = nullptr;
        }
    }
	return true;
}

bool PersonList::remove(string first, string last)
{
    if(!exists(first, last)) return false;
    if(size == 1){
        delete headHeightList;
        size--;
        headHeightList = nullptr;
        headWeightList = nullptr;
        return true;
    }
    if(headHeightList->first == first && headHeightList->last == last){
        Person *temp = headHeightList->nextHeight;
        headHeightList = temp;
    }
    else{
        Person *previous = headHeightList;
        Person *current = headHeightList->nextHeight;
        while(current != nullptr){
            if(current->first == first && current->last == last){
                previous->nextHeight = current->nextHeight;
                break;
            }
            previous = current;
            current = current->nextHeight;
        }
    }
    if(headWeightList->first == first && headWeightList->last == last){
        Person *temp = headWeightList->nextWeight;
        delete headWeightList;
        headWeightList = temp;
        size--;
        return true;
    }
    else{
        Person *previous = headWeightList;
        Person *current = headWeightList->nextWeight;
        while(current != nullptr){
            if(current->first == first && current->last == last){
                previous->nextWeight = current->nextWeight;
                delete current;
                size--;
                return true;
            }
            previous = current;
            current = current->nextWeight;
        }
    }
    return true;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    if(!exists(first, last)) return false;
    Person *current = headHeightList;
    for(int i = 0; i < size; i++){
        if(current->first == first && current->last == last){
            current->first = newFirst;
            current->last = newLast;
            return true;
        }
        current = current->nextHeight;
    }
    return true;
}

bool PersonList::updateHeight(string first, string last, int height)
{
    if(!exists(first, last)) return false;
    int weight;
    Person *current = headHeightList;
    for(int i = 0; i < size; i++){
        if(current->first == first && current->last == last){
            weight = current->weight;
        }
        current = current->nextHeight;
    }
    remove(first, last);
    add(first, last, height, weight);
    return true;
}

void PersonList::deepCopy(const PersonList &src){
    for(Person *current = src.headHeightList; current != nullptr; current = current->nextHeight){
        add(current->first, current->last, current->height, current->weight);
    } 
}

void PersonList::clear(){
    while(headHeightList != nullptr){
        remove(headHeightList->first, headHeightList->last);
    }
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    if(!exists(first, last)) return false;
    int height;
    Person *current = headWeightList;
    for(int i = 0; i < size; i++){
        if(current->first == first && current->last == last){
            height = current->height;
        }
        current = current->nextWeight;
    }
    remove(first, last);
    add(first, last, height, weight);
    return true;
}

PersonList::~PersonList()
{
    clear();
}

PersonList::PersonList(const PersonList &src)
{
    headHeightList = nullptr;
    headWeightList = nullptr;
    deepCopy(src);
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    if(this != &src){
        clear();
        deepCopy(src);
    }
    return *this;
}
