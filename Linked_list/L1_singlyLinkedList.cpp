#include <iostream>
#include <vector>
using namespace std;

// ============================================================================
// TOPIC: Introduction to LinkedList | Traversal | Length | Search
// ============================================================================

// 1. DEFINING A NODE
// A LinkedList is made of individual "nodes". 
// Unlike arrays which occupy contiguous memory, nodes are scattered in memory.
// Each node needs two things: the actual 'data' and a 'next' pointer (the memory address of the next node).
struct Node {
    public:
        int data;
        Node* next; // Pointer to the next node in the list

        // Constructor 1: Used when we want to link the new node to an existing node
        Node(int data1, Node* next1) {
            data = data1;
            next = next1;
        }

        // Constructor 2: Used when creating a node at the end (next is naturally null)
        Node(int data1) {
            data = data1;
            next = nullptr;
        }
};

// ============================================================================

// 2. CONVERT AN ARRAY TO A LINKED LIST
// Time Complexity: O(N), Space Complexity: O(1) auxiliary space
Node* convertArr2LL(vector<int>& arr) {
    if(arr.empty()) return nullptr;

    // 'head' is our anchor. It points to the very first node of the Linked List.
    Node* head = new Node(arr[0]); 
    
    // 'mover' is a temporary pointer that will help us traverse and build the list 
    // without losing our 'head' anchor.
    Node* mover = head; 

    for (int i = 1; i < arr.size(); i++) {
        // Create a standalone node for the current array element
        Node* temp = new Node(arr[i]);
        
        // Connect the previous node (where mover is sitting) to this new node
        mover->next = temp; 
        
        // Advance the mover to the new node so it's ready for the next iteration
        mover = temp;       
    }
    return head; // Always return the head so the list can be accessed later
}

// ============================================================================

// 3. TRAVERSAL OF A LINKED LIST
// Time Complexity: O(N)
void printLL(Node* head) {
    // RULE: NEVER move the 'head' pointer directly, otherwise you lose the start of your list!
    // Always use a temporary pointer for traversal.
    Node* temp = head;
    
    // Keep moving forward until we hit nullptr (the end of the list)
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next; // Jump to the memory address of the next node
    }
    cout << endl;
}

// ============================================================================

// 4. FIND THE LENGTH OF THE LINKED LIST
// Time Complexity: O(N)
int lengthOfLL(Node* head) {
    int count = 0;
    Node* temp = head;
    
    while (temp != nullptr) {
        count++; // Increment counter for each node we land on
        temp = temp->next;
    }
    return count;
}

// ============================================================================

// 5. SEARCH FOR AN ELEMENT IN THE LINKED LIST
// Time Complexity: O(N) in the worst case (if element is at the end or missing)
int checkIfPresent(Node* head, int val) {
    Node* temp = head;
    
    while (temp != nullptr) {
        if (temp->data == val) {
            return 1; // Element found, exit early
        }
        temp = temp->next;
    }
    return 0; // Reached the end of the list without finding the target
}

// ============================================================================

int main() {
    // Sample array to test our functions
    vector<int> arr = {12, 5, 8, 7};

    // 1. Conversion
    Node* head = convertArr2LL(arr);
    cout << "LinkedList successfully created from array." << endl;

    // 2. Traversal
    cout << "Traversing and printing LinkedList: ";
    printLL(head);

    // 3. Length
    cout << "Length of the LinkedList: " << lengthOfLL(head) << endl;

    // 4. Searching
    int target = 8;
    if (checkIfPresent(head, target)) {
        cout << "Element " << target << " is PRESENT in the LinkedList." << endl;
    } else {
        cout << "Element " << target << " is NOT PRESENT in the LinkedList." << endl;
    }

    return 0;
}