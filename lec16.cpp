#include <bits/stdc++.h>
using namespace std;

// PROBLEM: Find the Missing Number
// -------------------------------------------------------

/* * 1. Brute Force Approach
 * Logic: 
 * We know numbers are from 1 to N.
 * For every number 'i' from 1 to N, we iterate through the entire array 
 * to check if 'i' exists. If it doesn't, that's our missing number.
 * * Time Complexity: O(N * N) -> Near O(N^2)
 * Space Complexity: O(1)
 */
int missingNumberBrute(vector<int>& a, int N) {
    // Loop through 1 to N
    for (int i = 1; i <= N; i++) {
        int flag = 0; // Flag to check if number exists
        
        // Search for 'i' in the array
        for (int j = 0; j < N - 1; j++) {
            if (a[j] == i) {
                flag = 1;
                break;
            }
        }
        
        // If flag is still 0, 'i' was not found
        if (flag == 0) return i;
    }
    return -1;
}

/* * 2. Better Approach (Using Hashing)
 * Logic:
 * Use a frequency array (hash array) of size N+1.
 * Iterate through the input array and mark the presence of elements in the hash array.
 * Finally, iterate from 1 to N in the hash array; the index with value 0 is missing.
 * * Time Complexity: O(N) + O(N) = O(2N)
 * Space Complexity: O(N) (for the hash array)
 */
int missingNumberBetter(vector<int>& a, int N) {
    // Create hash array of size N+1 initialized to 0
    vector<int> hash(N + 1, 0);

    // Mark present numbers
    for (int i = 0; i < N - 1; i++) {
        hash[a[i]]++;
    }

    // Check which number is missing
    for (int i = 1; i <= N; i++) {
        if (hash[i] == 0) {
            return i;
        }
    }
    return -1;
}

/* * 3. Optimal Approach 1 (Summation)
 * Logic:
 * The sum of first N natural numbers is N*(N+1)/2.
 * Calculate this expected sum. Then calculate the actual sum of array elements.
 * Missing Number = Expected Sum - Actual Sum.
 * * Note: Use 'long long' to prevent integer overflow for large N.
 * * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int missingNumberOptimalSum(vector<int>& a, int N) {
    // Expected Sum of 1 to N
    long long expectedSum = (long long)N * (N + 1) / 2;
    
    // Actual Sum of array elements
    long long actualSum = 0;
    for (int i = 0; i < N - 1; i++) {
        actualSum += a[i];
    }
    
    return (int)(expectedSum - actualSum);
}

/* * 4. Optimal Approach 2 (XOR) - BEST
 * Logic:
 * XOR property: a ^ a = 0 and a ^ 0 = a.
 * 1. XOR all numbers from 1 to N (xor1).
 * 2. XOR all elements in the array (xor2).
 * 3. XORing xor1 and xor2 will cancel out all common numbers.
 * The result will be the missing number.
 * * Why better than Sum? It handles integer overflow issues.
 * * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int missingNumberOptimalXOR(vector<int>& a, int N) {
    int xor1 = 0, xor2 = 0;

    // XOR of array elements (part of 1 to N)
    for (int i = 0; i < N - 1; i++) {
        xor2 = xor2 ^ a[i];
        
        // Optimization: We can compute xor1 in this loop too for 1 to N-1
        xor1 = xor1 ^ (i + 1); 
    }
    
    // We still need to XOR with N, because the loop only went up to N-1
    xor1 = xor1 ^ N;

    return xor1 ^ xor2;
}

// ----------------------------------------------------------------------------------------
// PROBLEM: Max Consecutive Ones
// -------------------------------------------------------

/*
 * Optimal Approach
 * Logic:
 * Iterate through the array.
 * - If we see a 1, increment a counter (current_count).
 * - If we see a 0, the streak is broken. Reset current_count to 0.
 * - Always keep updating max_count with the maximum value of current_count found so far.
 * * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int findMaxConsecutiveOnes(vector<int>& nums) {
    int max_count = 0;
    int current_count = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
            current_count++;
            max_count = max(max_count, current_count);
        } else {
            // Reset counter when 0 is encountered
            current_count = 0;
        }
    }
    return max_count;
}

// --------------------------------------------------------------------------------------
// PROBLEM: Find the Number Appearing Once
// -------------------------------------------------------

/* * 1. Better Approach (Using Map)
 * Logic:
 * Use a map to store the frequency of each element.
 * Iterate the map to find the element with frequency 1.
 * * Time Complexity: O(N * logM) or O(N) depending on map type.
 * Space Complexity: O(N/2 + 1) -> O(N)
 */
int getSingleElementBetter(vector<int>& arr) {
    int n = arr.size();
    map<int, int> mpp;
    
    // Count frequencies
    for (int i = 0; i < n; i++) {
        mpp[arr[i]]++;
    }
    
    // Find the one with frequency 1
    for (auto it : mpp) {
        if (it.second == 1) {
            return it.first;
        }
    }
    return -1;
}

/* * 2. Optimal Approach (XOR)
 * Logic:
 * XOR property: A ^ A = 0.
 * If we XOR all elements in the array:
 * - All numbers appearing twice will cancel each other out (become 0).
 * - Only the number appearing once will remain.
 * * Example: 4 ^ 1 ^ 2 ^ 1 ^ 2
 * = (1^1) ^ (2^2) ^ 4
 * = 0 ^ 0 ^ 4
 * = 4
 * * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int getSingleElementOptimal(vector<int>& arr) {
    int n = arr.size();
    int xorr = 0;
    
    for (int i = 0; i < n; i++) {
        xorr = xorr ^ arr[i];
    }
    
    return xorr;
}

