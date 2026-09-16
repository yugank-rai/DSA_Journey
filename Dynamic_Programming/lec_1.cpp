/*
 * ============================================================================
 * DYNAMIC PROGRAMMING 1: Introduction | Memoization | Tabulation | Optimization
 * ============================================================================
 * 
 * Core Concept: "Those who cannot remember the past are condemned to repeat it."
 * 
 * Dynamic Programming (DP) is simply an optimization over plain recursion. 
 * When a recursive algorithm repeatedly solves the same subproblems 
 * (Overlapping Subproblems), we can store the results to save massive 
 * amounts of computation time.
 *
 * We progress through 3 evolutionary stages to solve DP problems:
 * 1. Memoization (Top-Down): Caching recursive answers in an array/map.
 * 2. Tabulation (Bottom-Up): Iteratively building answers from the base cases.
 * 3. Space Optimization: Eliminating arrays if we only need a few previous states.
 * 
 * Below, we solve the classic N-th Fibonacci Number using all three stages.
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// STAGE 1: MEMOIZATION (TOP-DOWN DP)
// ============================================================================
/*
 * Concept: 
 * We start from the top (e.g., f(5)) and recursively break it down.
 * To avoid re-calculating the same branches (like f(3) multiple times), 
 * we store the answer the first time we calculate it.
 * 
 * Time Complexity: O(N) -> Each state from 0 to N is computed exactly once.
 * Space Complexity: O(N) + O(N) -> O(N) for recursion stack + O(N) for DP array.
 */

int fib_memo(int n, vector<int>& dp) {
    // 1. The Base Case (Same as standard recursion)
    if (n <= 1) {
        return n;
    }
    
    // 2. The DP Check: Has this subproblem been solved before?
    // If the value isn't -1, it means we already have the answer.
    if (dp[n] != -1) {
        return dp[n];
    }
    
    // 3. Compute and Store: 
    // Calculate using the recurrence relation and store it BEFORE returning.
    dp[n] = fib_memo(n - 1, dp) + fib_memo(n - 2, dp);
    
    return dp[n];
}


// ============================================================================
// STAGE 2: TABULATION (BOTTOM-UP DP)
// ============================================================================
/*
 * Concept: 
 * We ditch the recursion entirely. Instead, we start from the absolute 
 * bottom (base cases f(0) and f(1)) and iterate upwards to reach f(n).
 * 
 * Time Complexity: O(N) -> We use a simple loop from 2 to N.
 * Space Complexity: O(N) -> We still use a DP array, but NO recursion stack space.
 */

int fib_tabulation(int n) {
    if (n <= 1) return n; 
    
    // 1. Declare the DP array of size n + 1
    vector<int> dp(n + 1, -1);
    
    // 2. Initialize the Base Cases directly into the array
    dp[0] = 0;
    dp[1] = 1;
    
    // 3. Build upwards from 2 to N using the recurrence relation
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}


// ============================================================================
// STAGE 3: SPACE OPTIMIZATION
// ============================================================================
/*
 * Concept (The "Ah-ha!" Moment): 
 * Look at the recurrence relation: dp[i] = dp[i-1] + dp[i-2]
 * To calculate the current Fibonacci number, we ONLY ever need the 
 * previous one and the second previous one. We don't need the entire history!
 * We can replace the O(N) array with just a couple of variables.
 * 
 * Time Complexity: O(N) -> A single loop from 2 to N.
 * Space Complexity: O(1) -> We only use three integer variables!
 */

int fib_optimized(int n) {
    if (n <= 1) return n;
    
    // Represents dp[i-2]
    int prev2 = 0; 
    
    // Represents dp[i-1]
    int prev = 1;  
    
    for (int i = 2; i <= n; i++) {
        // 1. Calculate the current state
        int curr = prev + prev2;
        
        // 2. Shift the variables forward for the next iteration
        prev2 = prev; // The old (i-1) becomes the new (i-2)
        prev = curr;  // The old (curr) becomes the new (i-1)
    }
    
    // When the loop finishes, 'prev' holds the N-th Fibonacci number
    return prev;
}

// ============================================================================
