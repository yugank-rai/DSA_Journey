/*
 * ============================================================================
 * DYNAMIC PROGRAMMING 2: Climbing Stairs | 1D Recurrence Relations
 * ============================================================================
 * 
 * Problem Statement:
 * You are climbing a staircase. It takes 'n' steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can 
 * you climb to the top?
 * 
 * THE GOLDEN RULES TO WRITE ANY 1D DP RECURRENCE:
 * 1. Express the problem in terms of an index (e.g., stair number).
 * 2. Do all possible actions on that index according to the problem 
 *    (e.g., jump 1 step OR jump 2 steps).
 * 3. Combine the results based on what the question asks:
 *    - "Count all ways" -> SUM the recursive calls.
 *    - "Find minimum/maximum" -> take the MIN/MAX of the recursive calls.
 * 
 * Notice: This exactly mirrors the Fibonacci logic (f(n) = f(n-1) + f(n-2)).
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// STAGE 1: MEMOIZATION (TOP-DOWN DP)
// ============================================================================
/*
 * Time Complexity: O(N)
 * Space Complexity: O(N) stack space + O(N) DP array = O(N)
 */
int countWays_memo(int ind, vector<int>& dp) {
    // 1. Base Cases
    // If you are at the 0th stair, there is 1 way (stay there / you've arrived)
    if (ind == 0) return 1;
    
    // If you are at the 1st stair, there is only 1 way to get there (from 0)
    // (This also prevents index out of bounds when calling ind - 2)
    if (ind == 1) return 1;
    
    // 2. DP Check
    if (dp[ind] != -1) return dp[ind];
    
    // 3. Do all possible actions and combine
    // Action A: Jumped 1 step to get here
    int left = countWays_memo(ind - 1, dp);
    
    // Action B: Jumped 2 steps to get here
    int right = countWays_memo(ind - 2, dp);
    
    // We want the total distinct ways, so we SUM the actions.
    dp[ind] = left + right;
    
    return dp[ind];
}


// ============================================================================
// STAGE 2: TABULATION (BOTTOM-UP DP)
// ============================================================================
/*
 * Time Complexity: O(N)
 * Space Complexity: O(N) for DP array (no recursion stack)
 */
int countWays_tabulation(int n) {
    if (n <= 1) return 1;
    
    // 1. Declare DP array
    vector<int> dp(n + 1, -1);
    
    // 2. Initialize Base Cases directly
    dp[0] = 1;
    dp[1] = 1;
    
    // 3. Build upwards iteratively
    for (int i = 2; i <= n; i++) {
        // dp[i] represents total ways to reach step i
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}


// ============================================================================
// STAGE 3: SPACE OPTIMIZATION
// ============================================================================
/*
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 * 
 * Just like Fibonacci, we only need the last two values at any given point.
 */
int countWays_optimized(int n) {
    if (n <= 1) return 1;
    
    // Represents dp[i-2] (Ways to reach stair 0)
    int prev2 = 1; 
    
    // Represents dp[i-1] (Ways to reach stair 1)
    int prev = 1;  
    
    for (int i = 2; i <= n; i++) {
        // Current ways is sum of the ways to reach the previous two steps
        int curr = prev + prev2;
        
        // Shift pointers for the next iteration
        prev2 = prev;
        prev = curr;
    }
    
    return prev;
}

// ============================================================================
