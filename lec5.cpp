/* TOPIC: Introduction to Recursion
   SOURCE: Striver's A2Z DSA Course - Step 1.5

   CONCEPTS COVERED:
   1. What is Recursion? (Function calling itself)
   2. Stack Overflow (Infinite Recursion)
   3. Base Condition (How to stop recursion)
   4. Recursion Tree (Visualization)
   
   PREREQUISITE:
   - Basic knowledge of Functions.
   - Understanding that when a function is called, it waits in memory (Stack) 
     until it completes execution.
*/

#include <iostream>
using namespace std;

// =========================================
// 1. INFINITE RECURSION & STACK OVERFLOW
// =========================================
/* Definition: When a function calls itself indefinitely without a stop condition.
   
   What happens internally?
   - Main calls func(), func calls func(), which calls func()...
   - Each call waits in the "Stack Space" because it hasn't finished.
   - The memory (Stack) fills up completely.
   - Result: Segmentation Fault (Stack Overflow).
*/
void infiniteRecursion() {
    cout << "1" << endl;
    infiniteRecursion(); // Calls itself again... and again...
}


// =========================================
// 2. BASE CONDITION
// =========================================
/* Problem: The above code runs forever.
   Solution: "Base Condition".
   
   Definition: A condition inside the recursive function that stops further calls.
   It basically says: "Hey, stop calling yourself and return/go back."
*/

int cnt = 0; // Global counter for demonstration

void printFinite() {
    // BASE CONDITION
    // If count reaches 3, we stop and return.
    if (cnt == 3) {
        return; 
    }

    cout << cnt << endl; // Print current count
    cnt++;               // Increment count
    
    printFinite();       // Recursive Call
    
    // NOTE: Lines below this recursive call are executed 
    // when the function returns (Backtracking phase).
}

// =========================================
// 3. RECURSION TREE VISUALIZATION
// =========================================
/*
   How does `printFinite()` execute? (Visualizing the Tree)
   
   main()
    |
    |-- printFinite() [cnt=0] -> Prints 0, increments to 1
         |
         |-- printFinite() [cnt=1] -> Prints 1, increments to 2
              |
              |-- printFinite() [cnt=2] -> Prints 2, increments to 3
                   |
                   |-- printFinite() [cnt=3] -> HITS BASE CONDITION (return)
                   |
              <-- Returns to [cnt=2]
         <-- Returns to [cnt=1]
    <-- Returns to [cnt=0]
   <-- Returns to main()
*/


// =========================================
// EXAMPLE PROBLEMS
// =========================================

// Problem 1: Print Name N times using Recursion
void printName(int i, int n) {
    // Base Case: If current index i exceeds n, stop.
    if (i > n) {
        return;
    }
    
    cout << "Striver" << endl;
    
    // Recursive Call: Call function for the next index (i+1)
    printName(i + 1, n);
}

// Problem 2: Print 1 to N using Recursion
void print1toN(int i, int n) {
    // Base Case
    if (i > n) return;
    
    cout << i << endl;
    
    // Recursive Call
    print1toN(i + 1, n);
}

// Problem 3: Print N to 1 using Recursion
void printNto1(int i, int n) {
    // Base Case: If i drops below 1, stop.
    if (i < 1) return;
    
    cout << i << endl;
    
    // Recursive Call: Decrease i
    printNto1(i - 1, n);
}

int main() {
    int n = 4;
    
    cout << "--- Finite Recursion Example ---" << endl;
    printFinite(); // Prints 0, 1, 2
    
    cout << "\n--- Print Name 4 times ---" << endl;
    printName(1, n); // Starts from i=1
    
    cout << "\n--- Print 1 to 4 ---" << endl;
    print1toN(1, n);
    
    cout << "\n--- Print 4 to 1 ---" << endl;
    // For N to 1, we start with 'n' (4) and go down to 1.
    // NOTE: Function signature here is slightly different logic than above loop,
    // let's stick to the simplest params: (current_val, stop_limit)
    printNto1(n, n); 
    
    return 0;
}