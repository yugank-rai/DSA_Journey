/* TOPIC: Multiple Recursion Calls (Fibonacci Number)
   SOURCE: Striver's A2Z DSA Course - Video Re 5

   CONCEPTS COVERED:
   1. Multiple Recursion: func() calling itself more than once (e.g., f(n-1) + f(n-2)).
   2. Fibonacci Series: 0, 1, 1, 2, 3, 5, 8...
      - 0th term = 0
      - 1st term = 1
      - Nth term = (N-1)th term + (N-2)th term
   3. Recursion Tree Execution Order (Depth First).
   4. Time Complexity: Exponential ~O(2^n).
*/

#include <iostream>
using namespace std;

// =========================================
// FIBONACCI FUNCTION (Multiple Recursion)
// =========================================
/* Logic:
   To find f(4), we need f(3) and f(2).
   To find f(3), we need f(2) and f(1).
   ... until we hit the base cases (0 or 1).
*/
int fib(int n) {
    // Base Case:
    // If n is 0, return 0.
    // If n is 1, return 1.
    if (n <= 1) {
        return n;
    }

    // Recursive Calls:
    // We call the function TWICE.
    // IMPORTANT: 'last' is calculated COMPLETELY before 'slast' starts.
    int last = fib(n - 1);       
    int slast = fib(n - 2);      

    // Merge step
    return last + slast;
}

/* =========================================
    VISUALIZING THE RECURSION TREE (Trace for N = 4)
   =========================================
   
   The code executes Depth-First (Left branch finishes first).
   
               f(4)
             /      \
        f(3)          f(2)
       /    \        /    \
     f(2)   f(1)   f(1)   f(0)
    /    \    |      |      |
  f(1)  f(0)  1      1      0
   |      |
   1      0

   STEP-BY-STEP EXECUTION ORDER:
   1. f(4) calls f(3)
   2. f(3) calls f(2)
   3. f(2) calls f(1) -> Returns 1
   4. f(2) calls f(0) -> Returns 0
   5. f(2) computes 1 + 0 = 1, returns 1 to f(3).
   6. f(3) calls f(1) (Right branch) -> Returns 1.
   7. f(3) computes 1 + 1 = 2, returns 2 to f(4).
   8. f(4) calls f(2) (Right huge branch).
   9. f(2) calls f(1) -> Returns 1.
   10. f(2) calls f(0) -> Returns 0.
   11. f(2) computes 1 + 0 = 1, returns 1 to f(4).
   12. f(4) computes 2 + 1 = 3. Final Answer = 3.

   Note: Notice how f(2) is calculated TWICE? 
   This redundancy is why the time complexity is high.
*/

// =========================================
// TIME COMPLEXITY ANALYSIS
// =========================================
/* - Each function call spawns 2 more calls.
   - This growth is Exponential.
   - For N=4, we made ~9 calls.
   - For N=5, it grows significantly.
   
   Time Complexity: O(2^n) (Approximate)
   - Specifically, it's O(1.618^n) related to the Golden Ratio.
   - In interviews, saying O(2^n) or "Exponential" is acceptable for this naive approach.
   
   Space Complexity: O(N)
   - This is the maximum depth of the stack tree (Height of tree).
*/

int main() {
    int n = 4;
    
    // We want the Nth Fibonacci number
    cout << "The " << n << "th Fibonacci Number is: " << fib(n) << endl;
    
    // Output should be 3 (Sequence: 0, 1, 1, 2, 3...)
    
    return 0;
}