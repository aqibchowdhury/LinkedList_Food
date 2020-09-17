#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food information
struct Food
{
    string foodName;
    int id;
    double price;
    struct Food* next;
};

//class LinkedList will contains a linked list of foods
class LinkedList
{
private:
    struct Food* head;

public:
    LinkedList();
    ~LinkedList();
    bool isFound(int foodId);
    bool add(string foodName, int foodId, double foodPrice);
    bool removeById(int foodId);
    bool removeByName(string foodName);
    bool changeFoodName(int foodId, string newFoodName);
    bool changeFoodPrice(int foodId, double newPrice);
    void printFoodList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int foodCount = 0;
    Food* next;
    //search through the list and delete each item. Count total items deleted
    while (head != NULL) {
        next = head;
        head = head->next;
        delete(next);
        foodCount++;
    }

    cout << "The number of deleted food items is: " << foodCount << "\n";
}

//A function to identify whether the parameterized food is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::isFound(int foodId)
{
    //return false if the list is empty
    if (head == NULL) {
        return false;
    }
    else {
        Food* next = head;
        //loop to search through the list until node is equal to the food list. return true when food is found
        while (next != NULL) {
            if (next->id != foodId) {
                next = next->next;
            }
            else
            {   
                return true;
            }
        }
        return false;
    }
}

//Creates a new node and inserts it into the list at the right place.
//It maintains an alphabetical ordering of foods by their names. Each
//food item has a unique id, if two food items have exactly the same name,
//then insert it into the list in the increasing order of their IDs.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::add(string foodName, int foodId, double foodPrice)
{
    //----
    //----
    Food* food = new Food;
    food->foodName = foodName;
    food->id = foodId;
    food->price = foodPrice;
    food->next = NULL;
    //First test case to add food if the list is empty
    if (head == NULL) {
        head = food;
        return true;
    }
    //If the list is not empty then compare the food input to the head 
    else {
        Food* curr = head->next;
        Food* prev = head;
        //compare food to head
        if (food->foodName.compare(head->foodName) < 0) {
            food->next = head;
            head = food;
            return true;
        }
        //if food and head have the same name then compare id and place in list accordingly
        else if (food->foodName.compare(head->foodName) == 0) {
            if (food->id == head->id) {
                cout << "Duplicated food item. Not added.\n";
                return false;
            }
            else if (food->id < head->id) {
                food->next = head;
                head = food;
                return true;
            }
        }
        //Loop to search through the list if there is more than 1 item to place food in the middle of the list
        while (curr != NULL) {
                //Compare food to current pointer placed after head
                if(food->foodName.compare(curr->foodName) < 0) {
                            prev->next = food;
                            food->next = curr;
                            return true;
                }
                //if food and current have the same name then compare id and place in list accordingly
                else if (food->foodName.compare(curr->foodName) == 0) {
                    //search for duplicate items (same name and id). return false if duplicate item is found.
                    if (food->id == curr->id) {
                        cout << "Duplicated food item. Not added.\n";
                        return false;
                    }
                    //organize foods accordingly by id
                    else if (food->id < curr->id) {
                        prev->next = food;
                        food->next = curr;
                        return true;
                    }
                }
                //shift to next node
                curr = curr->next;
                prev = prev->next;
            }
        prev->next = food;
        return true;
    }
}



//Removes the given food by Id from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int foodId)
{
    //return false if list is empty
    if (head == NULL) {
        return false;
    }
    //if the head node is equal to foodId, remove node
    else if (head->id == foodId)
    {
        Food* next = head;
        head = head->next;
        delete(next);
        return true;
    }
    //search through the list to find foodId until end of list is reached
    else {
        Food* curr = head;
        Food* prev = NULL;
        while (curr != NULL) {
            //delete node if current points to node with same foodId
            if (curr->id == foodId) {
                prev->next = curr->next;
                delete(curr);
                return true;
            }
            //shift pointers
            prev = curr;
            curr = curr->next;
        }
        return false;

    }
}

//Removes the given food by name from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all foods with
//the parameterized name should be removed from the list.
bool LinkedList::removeByName(string foodName)
{
    //return false if list is empty
    if (head == NULL) {
        return false;
    }
    else {
        Food* curr = head->next;
        Food* prev = head;
        bool flag = false;
        //loop to search through list until the end is reached
        while (curr != NULL) {
            //shift head if head is equal to foodName
            if (head->foodName == foodName) {
                head = head->next;
                flag = true;
            }
            //store location of previous node and bridge gap to next node not equal to foodName
            else if (curr->foodName == foodName) {
                prev->next = curr->next;
                curr = curr->next;
                flag = true;
            }
            //shift pointer to next node
            else {
                prev = prev->next;
                curr = curr->next;
            }
        }
        //print statement if name is not found
        if (flag == false) {
            cout << "No such food name found.\n";
        }
        return flag;
    }
}


//Modifies the name of the given Food item. Return true if it modifies successfully and
//false otherwise. Note: after changing a food name, the linked list must still be
//in alphabetical order of foods name
bool LinkedList::changeFoodName(int oldFoodId, string newFoodName)
{
    //return false if list is empty
    if (head == NULL) {
        return false;
    }
    else {
        Food* next = head;
        Food* prev = head;
        //loop to search through list until end is reached
        while (next != NULL) {
            //loop to continue shifting through nodes until node id equals oldFoodId
            if (next->id != oldFoodId) {
                prev = next;
                next = next->next;
            }
            //move head pointer to appropriate place in the list according to alphabetical order
            else if (next == head) {
                head = head->next;
                add(newFoodName, oldFoodId, next->price);
                return true;
            }
            //move pointer to appropriate place in the list according to alphabetical order
            else {
                next->foodName = newFoodName;
                prev->next = next->next;
                double price = next->price;
                add(newFoodName, oldFoodId, price);
                return true;
            }
        }
        return false;
    }
}

//Modifies the price of the given food item. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::changeFoodPrice(int foodId, double newPrice)
{
    //return false if list is empty
    if (head == NULL) {
        return false;
    }
    else {
        Food* next = head;
        //search through list until end of list is reached
        while (next != NULL) {
            //continue to move through list until food id match
            if (next->id != foodId) {
                next = next->next;
            }
            //if food id matches than replace price with new price
            else{
                next->price = newPrice;
                return true;
            }

        }
        return false;
    }
}


//Prints all the elements in the linked list starting from the head node.
void LinkedList::printFoodList()
{
    //return message if list is empty
    if (head == NULL) {
        cout << "\nThe list is empty\n" << endl;
    }
    else {
        Food* next = head;
        //loop to shift through list and display information according to paramaters
        while (next != NULL) {
            cout << setw(7) << left << next->foodName << setw(5) << right << next->id << setw(7) << right << "$" << next->price << endl;
            next = next->next;
        }
    }
} 
