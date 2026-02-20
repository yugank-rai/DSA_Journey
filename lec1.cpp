/*
 TOPIC: Time and Space Complexity (Striver's A2Z DSA Course)
    
*/

#include <iostream>
#include <vector>

using namespace std;

/* =========================================
    PART 1: WHAT IS TIME COMPLEXITY?
    =========================================
    
    Common Misconception: 
    Time complexity is NOT the time taken by a code to run (e.g., "2 seconds").
    
    Why?
    - "Time taken" depends on the machine (Old Windows vs New Mac).
    - An old laptop might take 5s, a supercomputer 0.01s for the SAME code.
    
    Definition:
    Time Complexity is the RATE at which the time taken increases with respect to the input size.
    
    - If input (N) grows by 10x, how much does the time grow?
    - We represent this using Big O Notation (O).
*/

void explainBigORules(int n) {
    /*
        =========================================
        PART 2: THE 3 RULES OF BIG O NOTATION
        =========================================
        
        When calculating complexity, we don't count every single CPU cycle.
        We follow these 3 rules:
        
        1. Always calculate for the WORST CASE scenario.
        2. Avoid Constants.
        3. Avoid Lower Values.
    */

    // RULE 1: WORST CASE SCENARIO
    // Big O = Upper Bound (Worst Case). 
    // Theta = Average Case.
    // Omega = Best Case.
    // In interviews, we usually only care about Big O (Worst Case) because we need the system to scale.

    // RULE 2: AVOID CONSTANTS
    // Example: If a code performs 4 * N^3 + 3 * N^2 + 8 operations.
    // If N = 100,000, adding 8 or multiplying by 4 is insignificant compared to N^3.
    // We drop the constants.
    // 4N^3 -> O(N^3)

    // RULE 3: AVOID LOWER VALUES
    // Example: If T(n) = N^3 + N^2
    // If N is large, N^2 is tiny compared to N^3.
    // We drop N^2.
    // Complexity is O(N^3).
}


/* =========================================
    PART 3: CALCULATING COMPLEXITY (Examples)
    =========================================
*/

// Example 1: Simple Loop
void simpleLoop(int n) {
    // This loop runs from 0 to n-1.
    // Operations: Assignment, Comparison, Increment, Print.
    // Total roughly: 3 * N operations.
    // Rule 2 (Avoid constants): Drop the 3.
    
    // Time Complexity: O(N)
    for (int i = 0; i < n; i++) {
        cout << "Raj" << endl; 
    }
}

// Example 2: Nested Loops
void nestedLoops(int n) {
    // Outer loop runs N times.
    for (int i = 0; i < n; i++) {
        
        // Inner loop also runs N times for EVERY iteration of i.
        // Total iterations = N * N = N^2.
        for (int j = 0; j < n; j++) {
            cout << "Hello" << endl;
        }
    }
    // Time Complexity: O(N^2)
}

// Example 3: Dependent Nested Loops (Tricky!)
void dependentLoops(int n) {
    /*
        Trace the iterations:
        i = 0 -> j runs 0 times (j < 0 is false)
        i = 1 -> j runs 1 time  (0)
        i = 2 -> j runs 2 times (0, 1)
        ...
        i = n -> j runs n times
        
        Total steps = 0 + 1 + 2 + ... + n
        Sum of first N natural numbers = N*(N+1)/2
        
        Equation: (N^2 / 2) + (N / 2)
        
        Apply Rule 2 (Remove constants): Remove /2
        Apply Rule 3 (Remove lower values): Remove N
        Result: N^2
        
        Time Complexity: O(N^2)
    */
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            cout << "Tricky" << endl;
        }
    }
}

/* =========================================
    PART 4: SPACE COMPLEXITY
    =========================================
    
    Definition:
    Space Complexity = Auxiliary Space + Input Space
    
    - Input Space: The space you take to store the data given to you (e.g., vector<int> arr).
    - Auxiliary Space: The EXTRA space you use to solve the problem.
    
    INTERVIEW TIP: 
    Never tamper with the input data just to save space, unless permitted. 
    It's better to use O(N) auxiliary space than to destroy the input data O(1).
*/

int sumInputs(int a, int b) {
    // Input Space: 2 integers (a, b) -> O(1)
    // Auxiliary Space: 1 integer (c) -> O(1)
    int c = a + b; 
    return c;
}

// Example of Space Complexity
void arrayExample(int n) {
    // We are creating a vector of size N.
    // We are allocating memory for N integers.
    vector<int> myArr(n); 
    
    // Space Complexity: O(N)
}

/* =========================================
    PART 5: THE "1 SECOND" RULE (For CP/Interviews)
    =========================================
    
    When you do Competitive Programming (CP) or online assessments (OA),
    there is a time limit (usually 1 second or 2 seconds).
    
    General Rule of Thumb:
    A modern server can execute roughly 10^8 (100 million) operations per second.
    
    If N = 10^5 (100,000):
    - O(N) solution?  10^5 ops < 10^8. (Passes)
    - O(N^2) solution? (10^5)^2 = 10^10 ops > 10^8. (Time Limit Exceeded / TLE)
    
    This helps you decide which algorithm to use:
    - If N <= 1000, you can likely use O(N^2).
    - If N <= 10^5 or 10^6, you usually need O(N) or O(N log N).
*/

int main() {
    int n = 5;
    
    cout << "--- Time Complexity Demonstration ---" << endl;
    simpleLoop(n);
    nestedLoops(n);
    dependentLoops(n);
    
    return 0;
}