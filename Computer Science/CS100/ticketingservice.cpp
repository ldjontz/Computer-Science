#include <queue>
#include <iostream>

using namespace std;

int main () {
   string personName = "";
   int counter = 0;
   int youPosition;

   queue<string> peopleInQueue;

   getline(cin, personName);
   bool first = false;
   if(personName == "You") first = true;
   while (personName != "-1") {
      // TODO: Add personName to peopleInQueue
      //       determine position of "You" (youPosition)
      peopleInQueue.push(personName);  
      getline(cin, personName);
      if(personName == "You"){
        youPosition = peopleInQueue.size() + 1;
      }
   }
    if(first) youPosition = 1;
   cout << "Welcome to the ticketing service... " << endl;
   cout << "You are number " << youPosition << " in the queue." << endl;

   // TODO: In a loop, remove head person from peopleInQueue,
   //       output their name and that they have purchased a ticket,
   //       then output your position in the queue. When you are at
   //       the head, output that you can purchase your ticket.
   while(youPosition > 1){
        cout << peopleInQueue.front() << " has purchased a ticket." << endl;
        youPosition--;
        cout << "You are now number " << youPosition << endl;
        peopleInQueue.pop();
   } 
    cout << "You can now purchase your ticket!" << endl;

   return 0;
}