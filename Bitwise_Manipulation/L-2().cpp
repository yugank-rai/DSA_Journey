/**
 * ============================================================================
 * DSA NOTES: MUST KNOW TRICKS IN BIT MANIPULATION
 * Source: L2. Must Know Tricks in Bit Manipulation | Swap two numbers without third variable
 * ============================================================================
 * * These notes are completely runnable in C++. You can read through the logic
 * and step-by-step explanations directly within the code.
 */

#include <iostream>

using namespace std;

/**
 * ----------------------------------------------------------------------------
 * 1. SWAP TWO NUMBERS WITHOUT A THIRD VARIABLE [00:00:18]
 * ----------------------------------------------------------------------------
 * Traditional swap uses a 'temp' variable. We can do this without it using XOR (^).
 * * XOR Properties:
 * 1. Even number of 1s = 0, Odd number of 1s = 1.
 * 2. N ^ N = 0 (XORing identical numbers results in 0).
 * 3. N ^ 0 = N (XORing with 0 keeps the number unchanged).
 */
void swapNumbers(int a, int b) {
    cout << "Before Swap: a = " << a << ", b = " << b << endl;
    
    a = a ^ b; // Step 1: a now holds the combined bits of (a XOR b)
    b = a ^ b; // Step 2: b = (a XOR b) XOR b => a XOR 0 => a. Now b holds original a.
    a = a ^ b; // Step 3: a = (a XOR original_b) XOR original_a => original_b. Now a holds original b.
    
    cout << "After Swap: a = " << a << ", b = " << b << endl;
}

/**
 * ----------------------------------------------------------------------------
 * 2. CHECK IF THE i-th BIT IS SET [00:03:49]
 * ----------------------------------------------------------------------------
 * We want to check if the bit at index 'i' (0-indexed from right to left) is 1.
 * * Approach 1: Left Shift (<<) [00:05:28]
 * Create a mask by shifting '1' to the left by 'i' places. 
 * If (n & mask) is non-zero, the bit is set.
 * * Approach 2: Right Shift (>>) [00:08:17]
 * Shift the number 'n' to the right by 'i' places to bring the i-th bit to the 0th position.
 * Then check (shifted_n & 1).
 */
bool checkIthBitSet(int n, int i) {
    // Approach 1 (Left Shift)
    // int mask = (1 << i);
    // return (n & mask) != 0;
    
    // Approach 2 (Right Shift - typically preferred)
    return ((n >> i) & 1) != 0;
}

/**
 * ----------------------------------------------------------------------------
 * 3. SET THE i-th BIT [00:10:44]
 * ----------------------------------------------------------------------------
 * Setting a bit means making it 1 (if it's already 1, leave it as 1).
 * * Logic: We create a mask with 1 at the i-th position and 0s everywhere else (1 << i).
 * We then use the OR (|) operator. 
 * (0 | 1 = 1), (1 | 1 = 1) -> The i-th bit becomes 1. 
 * Other bits (X | 0 = X) stay unchanged.
 */
int setIthBit(int n, int i) {
    int mask = (1 << i);
    return (n | mask);
}

/**
 * ----------------------------------------------------------------------------
 * 4. CLEAR THE i-th BIT [00:14:28]
 * ----------------------------------------------------------------------------
 * Clearing a bit means making it 0 (if it's already 0, leave it as 0).
 * * Logic: We create a mask with 0 at the i-th position and 1s everywhere else.
 * How? We take (1 << i) and apply the NOT (~) operator.
 * Then we use the AND (&) operator. (X & 0 = 0) at the i-th position, 
 * and (X & 1 = X) everywhere else.
 */
int clearIthBit(int n, int i) {
    int mask = ~(1 << i);
    return (n & mask);
}

/**
 * ----------------------------------------------------------------------------
 * 5. TOGGLE THE i-th BIT [00:17:56]
 * ----------------------------------------------------------------------------
 * Toggling means 1 becomes 0, and 0 becomes 1.
 * * Logic: XOR (^) operator is perfect for toggling.
 * (1 ^ 1 = 0), (0 ^ 1 = 1).
 * So, we XOR 'n' with a mask that has a 1 at the i-th position.
 */
int toggleIthBit(int n, int i) {
    int mask = (1 << i);
    return (n ^ mask);
}

/**
 * ----------------------------------------------------------------------------
 * 6. REMOVE THE LAST SET BIT (RIGHTMOST) [00:21:22]
 * ----------------------------------------------------------------------------
 * Critical Pattern: When you do (n - 1), the rightmost set bit in 'n' flips to 0, 
 * and all bits to its right flip to 1.
 * Example: n = 40 (101000). n-1 = 39 (100111).
 * * If we do (n & (n - 1)), the rightmost set bit becomes 0, and everything else 
 * to the left remains exactly the same.
 */
int removeLastSetBit(int n) {
    return (n & (n - 1));
}

/**
 * ----------------------------------------------------------------------------
 * 7. CHECK IF NUMBER IS A POWER OF TWO [00:28:27]
 * ----------------------------------------------------------------------------
 * Observation: Any power of 2 has EXACTLY ONE bit set in its binary representation.
 * Ex: 16 = 10000.
 * If we remove the last set bit using (n & (n-1)), the result MUST be 0.
 */
bool isPowerOfTwo(int n) {
    if (n <= 0) return false; // Edge case for non-positive numbers
    return (n & (n - 1)) == 0;
}

/**
 * ----------------------------------------------------------------------------
 * 8. COUNT THE NUMBER OF SET BITS [00:31:27]
 * ----------------------------------------------------------------------------
 * Approach 1 (Division/Right Shift): Keep doing (n & 1) to check if the last bit 
 * is set, then right shift n (n = n >> 1). Takes O(Total Bits) time.
 * * Approach 2 (Optimal / Brian Kernighan’s Algorithm) [00:37:32]: 
 * Keep removing the rightmost set bit using n = (n & (n-1)) until the number becomes 0.
 * Time Complexity: O(Number of Set Bits), which is much faster than checking every single bit.
 */
int countSetBitsOptimal(int n) {
    int count = 0;
    while (n != 0) {
        n = (n & (n - 1)); // Removes the rightmost set bit
        count++;
    }
    return count;
}

// NOTE: In competitive programming, you can also use the built-in function:
// __builtin_popcount(n) for integers, and __builtin_popcountll(n) for long long.

int main() {
    cout << "--- Testing Swap ---" << endl;
    swapNumbers(5, 7);
    
    cout << "\n--- Bit Manipulation Tricks on N = 13 (Binary: 1101) ---" << endl;
    int n = 13;
    
    cout << "Is 2nd bit set (0-indexed)? " << (checkIthBitSet(n, 2) ? "True" : "False") << endl; 
    
    cout << "Setting the 1st bit: " << setIthBit(n, 1) << " (Expected 15)" << endl;
    
    cout << "Clearing the 2nd bit: " << clearIthBit(n, 2) << " (Expected 9)" << endl;
    
    cout << "Toggling the 2nd bit: " << toggleIthBit(n, 2) << " (Expected 9)" << endl;
    
    cout << "\n--- Removing rightmost set bit ---" << endl;
    cout << "Removing last set bit of 40: " << removeLastSetBit(40) << " (Expected 32)" << endl;
    
    cout << "\n--- Power of 2 Check ---" << endl;
    cout << "Is 16 power of 2? " << (isPowerOfTwo(16) ? "True" : "False") << endl;
    cout << "Is 14 power of 2? " << (isPowerOfTwo(14) ? "True" : "False") << endl;
    
    cout << "\n--- Count Set Bits ---" << endl;
    cout << "Set bits in 13 (1101): " << countSetBitsOptimal(13) << " (Expected 3)" << endl;
    
    return 0;
}