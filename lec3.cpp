/* TOPIC: C++ Standard Template Library (STL)
    SOURCE: Striver's A2Z DSA Course - Step 1.3

    WHAT IS STL?
    STL (Standard Template Library) is a collection of pre-written algorithms, containers, 
    and functions that save you from writing code from scratch.
    
    It has 4 parts:
    1. Algorithms
    2. Containers (Vector, Queue, Map, etc.)
    3. Functions
    4. Iterators

    HEADER FILE:
    #include <bits/stdc++.h> 
    // This includes ALL standard libraries (math, string, vector, etc.) at once.
    // It's great for Competitive Programming but might be heavy for production code.
*/

#include <bits/stdc++.h> 
using namespace std;

// =========================================
// 1. PAIRS
// =========================================
/* Pair is part of the Utility library. 
   It stores two variables together as a single unit.
*/
void explainPair() {
    // Simple Pair
    pair<int, int> p = {1, 3};
    cout << "First: " << p.first << " Second: " << p.second << endl;

    // Nested Pair (Storing 3 or more items)
    pair<int, pair<int, int>> p2 = {1, {3, 4}};
    // Accessing: 1, 3, 4
    cout << p2.first << " " << p2.second.first << " " << p2.second.second << endl;

    // Array of Pairs
    pair<int, int> arr[] = {{1, 2}, {2, 5}, {5, 1}};
    // Accessing index 1's second element
    cout << arr[1].second << endl; // Prints 5
}

// =========================================
// 2. VECTORS
// =========================================
/* A Vector is a dynamic array. Unlike arr[10] which is fixed, 
   vector can grow in size automatically when you add elements.
*/
void explainVector() {
    vector<int> v; // Creates an empty container {}

    v.push_back(1);    // {1}
    v.emplace_back(2); // {1, 2} (emplace_back is slightly faster than push_back)

    // Vector of Pairs
    vector<pair<int, int>> vec;
    vec.push_back({1, 2});
    vec.emplace_back(1, 2); // Automatically assumes it's a pair

    // Pre-filled Vectors
    vector<int> v3(5, 100); // {100, 100, 100, 100, 100}
    vector<int> v4(5);      // {0, 0, 0, 0, 0} (Size 5 with garbage/zero values)

    // Copying a vector
    vector<int> v5(v3); // v5 is a copy of v3

    // --- ITERATORS ---
    // Iterators point to the MEMORY ADDRESS of the element.
    
    // v.begin() points to the first element.
    vector<int>::iterator it = v.begin(); 
    it++; 
    cout << *(it) << endl; // Access value using *

    // v.end() points to the memory location AFTER the last element.
    // v.back() gives the last element value.

    // Printing a vector (Short way)
    // "auto" automatically detects data type.
    for (auto it : v) {
        cout << it << " ";
    }
    cout << endl;

    // --- DELETION & INSERTION ---
    // Erase a single element
    // v = {10, 20, 12, 23}
    v.erase(v.begin() + 1); // Removes 20 -> {10, 12, 23}

    // Erase a range [start, end) -> End is NOT included
    // v = {10, 20, 12, 23, 35}
    v.erase(v.begin() + 2, v.begin() + 4); // Removes index 2 and 3 ({12, 23})

    // Insert
    vector<int> v6(2, 100); // {100, 100}
    v6.insert(v6.begin(), 300); // {300, 100, 100}
    v6.insert(v6.begin() + 1, 2, 10); // Insert two 10s at index 1 -> {300, 10, 10, 100, 100}

    // Other functions
    // v.size(), v.pop_back(), v.swap(v2), v.clear(), v.empty()
}

// =========================================
// 3. LISTS & DEQUE
// =========================================
/* List is a Doubly Linked List. 
   Benefit: push_front() and push_back() are very cheap O(1).
   In Vector, insert at front is costly O(N).
*/
void explainList() {
    list<int> ls;
    ls.push_back(2);    // {2}
    ls.emplace_back(4); // {2, 4}
    
    ls.push_front(5);   // {5, 2, 4} (Very fast operation!)
    ls.emplace_front(10); // {10, 5, 2, 4}
    
    // Rest functions same as vector: begin, end, clear, insert, size, swap
}

/* Deque (Double Ended Queue)
   Similar to list and vector. 
*/
void explainDeque() {
    deque<int> dq;
    dq.push_back(1);
    dq.emplace_back(2);
    dq.push_front(4);
    dq.emplace_front(3); // {3, 4, 1, 2}

    dq.pop_back();  // Remove from back
    dq.pop_front(); // Remove from front

    dq.back(); 
    dq.front();
}

// =========================================
// 4. STACK (LIFO - Last In First Out)
// =========================================
/* Imagine a stack of plates. 
   The last plate put on top is the first one you take off.
   Operations are O(1).
   No indexing access (cannot do st[2]).
*/
void explainStack() {
    stack<int> st;
    st.push(1); // {1}
    st.push(2); // {2, 1}
    st.push(3); // {3, 2, 1}
    st.emplace(5); // {5, 3, 2, 1}

    cout << st.top() << endl; // Prints 5 (Element at the top)

    st.pop(); // Removes 5 -> {3, 2, 1}
    
    cout << st.top() << endl; // Prints 3
    cout << st.size() << endl;
    cout << st.empty() << endl;
}

// =========================================
// 5. QUEUE (FIFO - First In First Out)
// =========================================
/* Imagine a line at a ticket counter. 
   First person in line is the first served.
*/
void explainQueue() {
    queue<int> q;
    q.push(1); // {1}
    q.push(2); // {1, 2}
    q.emplace(4); // {1, 2, 4}

    q.back() += 5; // Adds 5 to the last element (4+5=9) -> {1, 2, 9}

    cout << q.back() << endl; // Prints 9
    cout << q.front() << endl; // Prints 1

    q.pop(); // Removes first element (1) -> {2, 9}
}

// =========================================
// 6. PRIORITY QUEUE (PQ)
// =========================================
/* The element with the HIGHEST priority (largest value) stays at the top.
   Data is not stored linearly; it's a tree (Heap) internally.
   Push: O(log n), Top: O(1), Pop: O(log n)
*/
void explainPQ() {
    // MAX HEAP (Default): Largest element at top
    priority_queue<int> pq;
    pq.push(5); // {5}
    pq.push(2); // {5, 2}
    pq.push(8); // {8, 5, 2}
    pq.emplace(10); // {10, 8, 5, 2}

    cout << pq.top() << endl; // Prints 10

    pq.pop(); // Removes 10 -> {8, 5, 2}

    // MIN HEAP: Smallest element at top
    priority_queue<int, vector<int>, greater<int>> minPq;
    minPq.push(5);
    minPq.push(2);
    minPq.push(8);
    minPq.emplace(10); // {2, 5, 8, 10}

    cout << minPq.top() << endl; // Prints 2
}

// =========================================
// 7. SET CONTAINERS
// =========================================

// SET: Stores everything in SORTED order and UNIQUE.
void explainSet() {
    set<int> st;
    st.insert(1); // {1}
    st.emplace(2); // {1, 2}
    st.insert(2); // Still {1, 2} (No duplicates allowed)
    st.insert(4); // {1, 2, 4}
    st.insert(3); // {1, 2, 3, 4} (Auto-sorted)

    // Function find returns an iterator
    auto it = st.find(3); 

    // If element is not found, it returns st.end()
    auto it2 = st.find(6); 

    st.erase(5); // Erases 5 (takes logarithmic time)

    int cnt = st.count(1); // Returns 1 if present, 0 if not (since unique)
}

// MULTISET: Stores SORTED but ALLOWS DUPLICATES.
void explainMultiSet() {
    multiset<int> ms;
    ms.insert(1); // {1}
    ms.insert(1); // {1, 1}
    ms.insert(1); // {1, 1, 1}

    ms.erase(1); // ERASES ALL OCCURRENCES of 1 -> {}

    // To erase only ONE occurrence:
    // ms.erase(ms.find(1)); 
}

// UNORDERED SET: UNIQUE but NOT SORTED.
// Operations are O(1) in average case. Worst case O(N).
void explainUnorderedSet() {
    unordered_set<int> st;
    // Same functions as set, but order is random.
    // Lower_bound and Upper_bound do NOT work here.
}

// =========================================
// 8. MAP CONTAINERS
// =========================================
/* Map stores Key-Value pairs. 
   Keys are UNIQUE and SORTED. Values can be duplicates.
   Key -> Value
*/
void explainMap() {
    map<int, int> mpp;
    // map<int, pair<int, int>> mpp; // Key int, Value pair
    // map<pair<int, int>, int> mpp; // Key pair, Value int

    mpp[1] = 2; // Key 1 -> Value 2
    mpp.emplace(3, 1); // Key 3 -> Value 1
    mpp.insert({2, 4}); // Key 2 -> Value 4

    // Map stores: {{1, 2}, {2, 4}, {3, 1}} (Sorted by Keys)

    // Iterating map
    for (auto it : mpp) {
        cout << it.first << " " << it.second << endl; 
    }

    cout << mpp[1] << endl; // Prints 2
    cout << mpp[5] << endl; // Prints 0 (or null) if key doesn't exist

    auto it = mpp.find(3); // Points to {3, 1}
    // *(it).second gives 1
}

// MULTIMAP: Duplicate keys allowed, Sorted.
// UNORDERED MAP: Unique keys, Not sorted. O(1) mostly.

// =========================================
// 9. ALGORITHMS
// =========================================

// Custom Comparator Function (Boolean)
// Example: Sort by second element ascending. If second is same, sort by first descending.
bool comp(pair<int, int> p1, pair<int, int> p2) {
    if (p1.second < p2.second) return true;
    if (p1.second > p2.second) return false;
    
    // If we are here, second elements are same
    if (p1.first > p2.first) return true; // Descending order for first
    return false;
}

void explainAlgo() {
    int a[] = {1, 5, 3, 2};
    int n = 4;
    vector<int> v = {1, 5, 3, 2};

    // Sorting [start, end)
    sort(a, a + n); // Sorts array
    sort(v.begin(), v.end()); // Sorts vector

    // Sort descending
    sort(v.begin(), v.end(), greater<int>());

    // Sort with custom comparator
    pair<int, int> pairs[] = {{1, 2}, {2, 1}, {4, 1}};
    sort(pairs, pairs + 3, comp); 
    // Result: {{4,1}, {2,1}, {1,2}}

    // Count Set Bits (Binary 1s)
    int num = 7; // 111
    int cnt = __builtin_popcount(num); // Returns 3

    // Next Permutation
    string s = "123";
    // Prints 123, 132, 213, 231, 312, 321
    do {
        cout << s << endl;
    } while (next_permutation(s.begin(), s.end()));
    
    // Max Element
    int maxi = *max_element(a, a + n);
}

int main() {
    explainVector();
    return 0;
}