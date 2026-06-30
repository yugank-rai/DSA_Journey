/**
 * ===========================================================================
 * DSA Notes: XOR of Numbers in a Given Range
 * Topic: Bit Manipulation
 * ===========================================================================
 * * PROBLEM 1: Find the XOR of all numbers from 1 to N.
 * ---------------------------------------------------------------------------
 * Naive Approach: 
 * Iterate from 1 to N and keep XORing the elements. 
 * Time Complexity: O(N), Space Complexity: O(1)
 * * Optimized Approach (O(1) Time):
 * If we write down the XOR from 1 to N for the first few numbers, 
 * we can observe a mathematically repeating pattern in blocks of 4:
 * * N = 1 -> 1               (N % 4 == 1) => Answer: 1
 * N = 2 -> 1^2 = 3         (N % 4 == 2) => Answer: N + 1
 * N = 3 -> 1^2^3 = 0       (N % 4 == 3) => Answer: 0
 * N = 4 -> 1^2^3^4 = 4     (N % 4 == 0) => Answer: N
 * * N = 5 -> 1               (N % 4 == 1) => Answer: 1
 * N = 6 -> 7               (N % 4 == 2) => Answer: N + 1
 * N = 7 -> 0               (N % 4 == 3) => Answer: 0
 * N = 8 -> 8               (N % 4 == 0) => Answer: N
 */

#include <iostream>
using namespace std;

// Function to find XOR of numbers from 1 to N in O(1) time [00:04:36]
int findXor1toN(int n) {
    // Check the remainder when N is divided by 4 to map it to our pattern
    if (n % 4 == 1) {
        return 1;
    } 
    else if (n % 4 == 2) {
        return n + 1;
    } 
    else if (n % 4 == 3) {
        return 0;
    } 
    else { // n % 4 == 0
        return n;
    }
}

/**
 * PROBLEM 2: Find the XOR of numbers in a given range [L, R]
 * ---------------------------------------------------------------------------
 * Naive Approach: 
 * Iterate from L to R and keep XORing.
 * Time Complexity: O(R - L + 1)
 * * Optimized Approach (O(1) Time):
 * We can reuse our O(1) `findXor1toN` function to solve this instantly!
 * We know that finding XOR from L to R is mathematically equivalent to:
 * (XOR from 1 to L-1) ^ (XOR from 1 to R)
 * * WHY THIS WORKS:
 * Rule of XOR: A ^ A = 0. 
 * If we XOR from 1 to R, it inherently includes the numbers from (1 to L-1) 
 * as well as our target range (L to R).
 * * By XORing this total result with (1 to L-1) again, the elements that exist 
 * outside our desired range (from 1 to L-1) will cancel themselves out (turn to 0).
 * What remains untouched is exactly the XOR from L to R.
 * * Walkthrough Example (L = 4, R = 7):
 * XOR(1 to 3) = 1 ^ 2 ^ 3
 * XOR(1 to 7) = 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6 ^ 7
 * * XOR(1 to 3) ^ XOR(1 to 7) = (1^1) ^ (2^2) ^ (3^3) ^ 4 ^ 5 ^ 6 ^ 7
 * =   0   ^   0   ^   0   ^ 4 ^ 5 ^ 6 ^ 7
 * = 4 ^ 5 ^ 6 ^ 7  -> The exact answer we want!
 */

// Function to find XOR of numbers from L to R in O(1) time [00:08:44]
int findXorLtoR(int L, int R) {
    // 1. Get XOR of all numbers from 1 to the number just before L
    int xorTillLMinus1 = findXor1toN(L - 1);
    
    // 2. Get XOR of all numbers from 1 to R
    int xorTillR = findXor1toN(R);
    
    // 3. XOR the two boundaries to cancel out the unneeded prefix elements
    return (xorTillLMinus1 ^ xorTillR);
}

int main() {
    // --- Test Cases ---
    
    // Problem 1: XOR from 1 to N
    int N = 6;
    cout << "XOR from 1 to " << N << " is: " << findXor1toN(N) << "\n";
    // Expected output: 7 (Because 6 % 4 == 2, which maps to N + 1)

    // Problem 2: XOR from L to R
    int L = 4, R = 7;
    cout << "XOR from " << L << " to " << R << " is: " << findXorLtoR(L, R) << "\n";
    // Expected output: 2 (Because 4^5^6^7 evaluates to 2)

    return 0;
}
/**
 * ===========================================================================
 * DSA Notes: Single Number III (LeetCode 260)
 * Topic: Bit Manipulation
 * ===========================================================================
 * PROBLEM STATEMENT:
 * You are given an array of integers where every number appears TWICE 
 * except for TWO distinct numbers which appear exactly ONCE.
 * Find the two numbers that appear exactly once.
 * * Example: nums = [2, 4, 2, 6, 3, 7, 7, 3]
 * Unique elements: 4 and 6
 * ---------------------------------------------------------------------------
 * Naive Approach: Hashing
 * Create a Map to store frequency. Iterate and find the two elements with freq = 1.
 * Time Complexity: O(N log M) or O(N), Space Complexity: O(N)
 * * Optimized Approach: Bitwise XOR (O(N) Time, O(1) Space)
 * 1. XOR all numbers. The duplicates cancel out (X ^ X = 0).
 * Result = (unique_num_1 ^ unique_num_2)
 * 2. The result XOR is non-zero because the two numbers are distinct.
 * Any SET BIT (1) in this XOR result means that at this specific bit position, 
 * the two unique numbers differ (one has a 1, the other has a 0).
 * 3. Find the rightmost set bit in this XOR result to act as a separator.
 * 4. Separate all numbers in the original array into two "buckets" 
 * based on whether they have this specific bit set or not.
 * 5. XOR all the numbers in each bucket separately. The duplicates will cancel 
 * out within the buckets, leaving exactly one unique number per bucket!
 */

#include <iostream>
#include <vector>

using namespace std;

// Function to find the two numbers appearing exactly once [00:18:06]
vector<int> singleNumber(vector<int>& nums) {
    long xorResult = 0; // Using long to avoid overflow edge cases [00:22:06]
    
    // Step 1: XOR all elements.
    // At the end, xorResult will contain the XOR of the two unique numbers.
    for (int i = 0; i < nums.size(); i++) {
        xorResult ^= nums[i];
    }
    
    // Step 2: Find the rightmost set bit of the xorResult.
    // The formula (num & ~(num - 1)) or (num ^ (num & (num - 1))) isolates the rightmost 1-bit.
    // Example: If xorResult = 10 (binary 1010), rightmostSetBit = 2 (binary 0010).
    // Note: We used a bit trick (xorResult & (xorResult - 1)) ^ xorResult 
    // to get the rightmost bit, which is equivalent to xorResult & ~(xorResult - 1)
    int rightmostSetBit = (xorResult & (xorResult - 1)) ^ xorResult;
    
    int bucket1 = 0;
    int bucket2 = 0;
    
    // Step 3: Divide numbers into two buckets and XOR them simultaneously.
    for (int i = 0; i < nums.size(); i++) {
        // Check if the number has the rightmost bit set
        if ((nums[i] & rightmostSetBit) != 0) {
            // Number belongs to Bucket 1
            bucket1 ^= nums[i];
        } else {
            // Number belongs to Bucket 2
            bucket2 ^= nums[i];
        }
    }
    
    // Step 4: After loop ends, bucket1 and bucket2 will hold our two unique numbers.
    return {bucket1, bucket2};
}

int main() {
    // --- Test Case ---
    vector<int> nums = {2, 4, 2, 6, 3, 7, 7, 3};
    
    cout << "Array: ";
    for(int num : nums) cout << num << " ";
    cout << "\n";
    
    vector<int> result = singleNumber(nums);
    
    cout << "The two single numbers are: " << result[0] << " and " << result[1] << "\n";
    // Expected output: 4 and 6 (Order may vary)

    return 0;
}
