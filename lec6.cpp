/* TOPIC: Basic Recursion Problems & Backtracking
   SOURCE: Striver's A2Z DSA Course - Video Re 2

   CONCEPTS COVERED:
   1. Print Name N times.
   2. Print 1 to N (Linear).
   3. Print N to 1 (Reverse).
   4. Print 1 to N (Using Backtracking).
   5. Print N to 1 (Using Backtracking).

   KEY LEARNING - BACKTRACKING:
   - "Backtracking" in this context means performing the task (printing)
     AFTER the recursive function call returns.
   - If you print BEFORE the call, it happens during the "Forward" phase.
   - If you print AFTER the call, it happens during the "Return" phase (Reverse order).
*/

#include <iostream>
using namespace std;

// =========================================
// PROBLEM 1: Print Name N times
// =========================================
void printName(int i, int n) {
    // Base Case: Stop if current index exceeds N
    if (i > n) return;

    cout << "Raj" << endl;

    // Recursive Call: Move to next index
    printName(i + 1, n);
}

// =========================================
// PROBLEM 2: Print 1 to N (Linearly)
// =========================================
void print1toN(int i, int n) {
    if (i > n) return;

    cout << i << " "; // Task happening during "Forward" phase
    
    print1toN(i + 1, n);
}

// =========================================
// PROBLEM 3: Print N to 1 (Reverse)
// =========================================
// Logic: Start from N, decrease i, stop when i < 1.
void printNto1(int i, int n) {
    if (i < 1) return; // Base Case

    cout << i << " ";
    
    printNto1(i - 1, n);
}

// =========================================
// PROBLEM 4: Print 1 to N (Using BACKTRACKING)
// =========================================
/* CHALLENGE: 
   Print 1 to N, BUT you are NOT allowed to use 'i+1'. 
   You must start from N and go down to 1.
   
   LOGIC:
   - Function calls go: f(3) -> f(2) -> f(1) -> f(0)[returns].
   - If we print AFTER the call, the first print happens for f(1), then f(2), then f(3).
   - This reverses the execution order.
*/
void print1toN_Backtrack(int i, int n) {
    // Base Case: If we go below 1, stop.
    if (i < 1) return;

    // 1. Recursive Call FIRST (Go deeper)
    print1toN_Backtrack(i - 1, n);

    // 2. Task AFTER return (Backtracking)
    // This line executes only when the above function returns.
    cout << i << " ";
}

// =========================================
// PROBLEM 5: Print N to 1 (Using BACKTRACKING)
// =========================================
/* CHALLENGE:
   Print N to 1, BUT start from 1 and go up to N.
   
   LOGIC:
   - Call f(1) -> f(2) -> f(3) -> f(4)[returns].
   - Print happens after return: 3 prints, then 2, then 1.
*/
void printNto1_Backtrack(int i, int n) {
    // Base Case: If i exceeds N, stop.
    if (i > n) return;

    // 1. Recursive Call
    printNto1_Backtrack(i + 1, n);

    // 2. Task AFTER return
    cout << i << " ";
}

int main() {
    int n = 3;

    cout << "--- Name 3 Times ---" << endl;
    printName(1, n);

    cout << "\n--- 1 to N (Linear) ---" << endl;
    print1toN(1, n);

    cout << "\n\n--- N to 1 (Linear) ---" << endl;
    printNto1(n, n); // Start with i = n

    cout << "\n\n--- 1 to N (Backtracking - Start from N) ---" << endl;
    print1toN_Backtrack(n, n); // Pass n as starting point

    cout << "\n\n--- N to 1 (Backtracking - Start from 1) ---" << endl;
    printNto1_Backtrack(1, n); // Pass 1 as starting point

    cout << endl;
    return 0;
}