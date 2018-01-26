


#include<iostream>
using namespace std;

class Node {
    /*
     * Node class with a variable to store data and two pointers
     * to link it to the next and the previous node
     */
public:
    int data;
    Node* next;
    Node* prev;
    
    Node() {                // Default constructor for Node
        data = 0;            // initializes the data to zero
        next = NULL;        // and points prev and next to
        prev = NULL;        // NULL.
    }
};

class DLList {
    /*
     * Class for the double linked list data structure.
     * The list is identified by head and tail, which point
     * to the first and the last element of the list respectively.
     * A integer variable named size stores the number of
     * elements of the linked list.
     */
private:
    Node* head;
    Node* tail;
    int size;
    
public:
    DLList() {                // Default constructor for DLList
        head = NULL;        // initializes the list with both
        tail = NULL;        // head and tail pointing to NULL
        size = 0;            // and size equal to zero.
    }
    
    // Member functions of the class
    void insert(int d);            // inserts Node with data at the end of the list
    Node* getNode(int i);        // returns a pointer to the ith node
    int insertAt(int i, int d);    // inserts Node with data at the ith position
    void remove();                // removes the last Node of the list
    int removeAt(int i);        // removes the ith element of the list
    int countItems();            // return the number of Nodes in the list
    void display();                // displays the elements of the linked list
};

void DLList::insert(int d) {
    /*
     * Inserts a new Node containing the value given by d
     * at the end of the linked list.
     */
    Node* new_node = new Node;
    new_node->data = d;
    new_node->next = NULL;
    
    if (head == NULL) {                // Checks if the list is empty.
        new_node->prev = NULL;        // Steps to do if the there are no Nodes
        head = new_node;            // in the linked list.
    } else {
        tail->next = new_node;        // Steps to do if there is atleast one
        new_node->prev = tail;        // element in the linked list.
    }
    
    tail = new_node;
    ++size;                            // Size of the linked list is increased by one.
}

Node* DLList::getNode(int i) {
    /*
     * Function which returns a pointer to the ith node
     * of the linked list.
     * This function makes the code for the add and remove
     * functions much simpler.
     */
    if (i < 1 || i > size) {        // Checks if the value of i is sane.
        cout << "Invalid element position." << endl;
        return NULL;
    }
    
    Node* p;                        // Placeholder variable to traverse the list.
    
    /*
     * Condition to make sure that the function runs
     * in O(1+min{i, size-i}) time and not O(1+i) time.
     */
    
    if (i < (size/2)) {
        p = head;                    // List traversal starts from head if i<size/2
        for (int j=0; j<i-1; ++j)
            p = p->next;
        
    } else {
        p = tail;                    // List traversal starts from tail if i>size/2
        for (int j=0; j<(size-i); ++j)
            p = p->prev;
    }
    
    return p;
}

int DLList::insertAt(int i, int d) {
    /*
     * Inserts a Node with data=d at the ith position in the list.
     * Returns 0 if the Node is successfully added. Returns -1 if
     * the index is invalid.
     * Makes use of the getNode function to make the code more readable.
     */
    if (i < 1 || i > size+1) {        // Checks if the given value if i is sane.
        cout << "Invalid element position. No changes made to the list." << endl;
        return -1;
    }
    
    if (i == size+1) {                // Calls insert function to insert Node at
        insert(d);                    // the end of the list.
        return 0;
    }
    
    Node* new_node = new Node;
    new_node->data = d;
    
    if (size == 1) {                // Steps to perform to add Node at the start
        new_node->next = head;        // of the list.
        new_node->prev = NULL;
        head->prev = new_node;
        head = new_node;
    } else {                        // Steps to perform to add Node in the middle
        Node* p = getNode(i-1);        // of the list.
        new_node->next = p->next;
        new_node->prev = (p->next)->prev;
        (p->next)->prev = new_node;
        p->next = new_node;
    }
    
    ++size;                    // Increments to size variable to track the number of Nodes
    return 0;
}

void DLList::remove() {
    /*
     * Removes the last Node of the linked list.
     */
    if (size == 0) {        // Does nothing if the list is empty.
        cout << "No elements in the list. Nothing to do." << endl;
        return;
    } else if (size == 1) {        // Has to take care of head if
        delete head;            // there is only one Node in the list.
        head = NULL;
        tail = NULL;
    } else {
        Node* p = tail;            // Placeholder variable to manually delete
        delete p;                // the node from memory.
        tail = tail->prev;
        tail->next = NULL;
    }
    
    --size;
}

int DLList::removeAt(int i) {
    /*
     * Removes the ith element of the list.
     * Returns 0 if the removal is successful, Returns -1 if
     * the value of i is invalid.
     */
    if (i < 1 || i > size) {
        cout << "Invalid element position. No changes made to the list." << endl;
        return -1;
    }
    
    if (i == size) {        // Calls the remove function if the last element is
        remove();            // to be deleted.
        return 0;
    } else if (i == 1) {    // Special case for deletion of first element
        head = head->next;    // because head needs to be taken care of.
        delete head->prev;
        head->prev = NULL;
    } else {                // Steps for deletion of an element in the middle.
        Node* p = getNode(i);
        (p->prev)->next = p->next;
        (p->next)->prev = p->prev;
        delete p;
    }
    
    --size;                    // Decrements the size variable to keep it up to date.
    return 0;
}

int DLList::countItems() {
    /*
     * Counts the number of Nodes in the linked list.
     * As the length of the linked list is tracked with
     * the "size" variable, the variable is simply returned
     * to the parent function.
     */
    return size;
}

void DLList::display() {
    /*
     * Displays all the elements of the linked list.
     */
    if (size == 0) {            // Prints error message if the list is empty.
        cout << "There are no elements in the list. Nothing to do." << endl;
    }
    
    Node* p = head;                // Placeholder variable used to traverse the list.
    for (int i=0; i<size; ++i) {
        cout << p->data << "->";
        p = p->next;
    }
    
    cout << "NULL" << endl;
}

int main() {
    DLList list;
    for(int i=0; i<10; ++i) {
        list.insert(i);
    }
    
    list.display();
    list.remove();
    list.removeAt(1);
    list.removeAt(9);
    list.display();
    cout << list.countItems() << endl;
    
    return 0;
}
