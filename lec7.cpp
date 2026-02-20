/* TOPIC: Parameterized vs Functional Recursion
   SOURCE: Striver's A2Z DSA Course - Video Re 3

   CONCEPTS COVERED:
   1. Sum of first N numbers (Parameterized Way)
   2. Sum of first N numbers (Functional Way)
   3. Factorial of N (Functional Way)
   4. Complexity Analysis (Stack Space)
*/

#include <iostream>
using namespace std;

// =========================================
// 1. SUM OF N NUMBERS (Parameterized Way)
// =========================================
/* Pattern: void func(i, sum)
   - We carry the answer inside the parameters ("sum").
   - When base case is met, we print the answer.
   - The function doesn't return anything (void).
   
   Example: N = 3
   f(3, 0) -> f(2, 3) -> f(1, 5) -> f(0, 6) -> PRINT 6
*/
void solveParam(int i, int sum) {
    // Base Case: When i becomes 0 (or less than 1), we have added all numbers.
    if (i < 1) {
        cout << "Sum (Parameterized): " << sum << endl;
        return;
    }

    // Recursive Step: Decrease i, and add current i to sum
    solveParam(i - 1, sum + i);
}

// =========================================
// 2. SUM OF N NUMBERS (Functional Way)
// =========================================
/* Pattern: int func(n)
   - We want the function to RETURN the answer to us.
   - Logic: f(n) = n + f(n-1)
   - "Sum of 3 numbers" = 3 + "Sum of 2 numbers"
   
   Example: N = 3
   f(3) -> 3 + f(2)
                 |-> 2 + f(1)
                           |-> 1 + f(0)
                                     |-> 0 (Base Case)
   Result: 3 + 2 + 1 + 0 = 6
*/
int solveFunc(int n) {
    // Base Case
    if (n == 0) {
        return 0;
    }
    
    // Recursive Step
    return n + solveFunc(n - 1);
}

// =========================================
// 3. FACTORIAL OF N (Functional Way)
// =========================================
/* Problem: 4! = 4 * 3 * 2 * 1 = 24
   Logic: f(n) = n * f(n-1)
   
   CRITICAL BASE CASE CHANGE:
   - If we return 0 at base case, the whole product becomes 0.
   - 4 * 3 * 2 * 1 * 0 = 0 (WRONG!)
   - Base case must return 1.
*/
int factorial(int n) {
    // Base Case: Factorial of 0 or 1 is 1.
    if (n == 0) {
        return 1;
    }
    
    // Recursive Step
    return n * factorial(n - 1);
}

// =========================================
// 4. COMPLEXITY ANALYSIS
// =========================================
/*
   Time Complexity (TC): O(N)
   - The function runs N times (from N down to 0).
   
   Space Complexity (SC): O(N)
   - This is "Auxiliary Stack Space".
   - Even though we don't use an array, recursion uses the internal Stack memory.
   - f(3) waits for f(2), which waits for f(1)... 
   - N functions wait in memory simultaneously.
*/

int main() {
    int n = 3;
    int nFact = 4;

    cout << "--- Sum of First " << n << " Numbers ---" << endl;
    
    // 1. Parameterized Call
    // Start with n, and initial sum is 0
    solveParam(n, 0); 
    
    // 2. Functional Call
    int result = solveFunc(n);
    cout << "Sum (Functional): " << result << endl;

    cout << "\n--- Factorial of " << nFact << " ---" << endl;
    cout << "Factorial: " << factorial(nFact) << endl;

    return 0;
}