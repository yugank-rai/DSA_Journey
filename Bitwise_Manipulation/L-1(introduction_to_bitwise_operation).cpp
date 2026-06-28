/**
 * ============================================================================
 * DSA NOTES: INTRODUCTION TO BIT MANIPULATION 
 * Source: L1. Introduction to Bit Manipulation | 1's 2's Compliment | Bit Operators
 * ============================================================================
 * * These notes are fully written in C++ format. You can copy this entire block 
 * directly into your IDE, read through the logic, and even run the examples.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * ----------------------------------------------------------------------------
 * 1. DECIMAL TO BINARY CONVERSION [00:00:18]
 * ----------------------------------------------------------------------------
 * To convert a decimal number to binary:
 * 1. Keep dividing the number by 2.
 * 2. Store the remainder (0 or 1).
 * 3. Stop when the number becomes 1 (or 0).
 * 4. Reverse the accumulated remainders to get the binary string.
 * * Time Complexity: O(log2(N)) - because we divide by 2 in each step.
 * Space Complexity: O(log2(N)) - space needed to store the string.
 */
string decimalToBinary(int n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        if (n % 2 == 1) {
            result += "1";
        } else {
            result += "0";
        }
        n = n / 2;
    }
    // The remainders are collected backwards, so we must reverse them
    reverse(result.begin(), result.end());
    return result;
}

/**
 * ----------------------------------------------------------------------------
 * 2. BINARY TO DECIMAL CONVERSION [00:07:04]
 * ----------------------------------------------------------------------------
 * To convert binary to decimal:
 * 1. Traverse the string from right (end) to left (start).
 * 2. Multiply the bit by increasing powers of 2 (2^0, 2^1, 2^2...).
 * 3. Add them all up.
 * * Time Complexity: O(Length of String)
 * Space Complexity: O(1)
 */
int binaryToDecimal(string s) {
    int num = 0;
    int powerOf2 = 1; // Initially 2^0 = 1
    
    // Iterate from right to left
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '1') {
            num += powerOf2;
        }
        powerOf2 *= 2; // Incrementally update the power of 2 (1 -> 2 -> 4 -> 8...)
    }
    return num;
}

/**
 * ----------------------------------------------------------------------------
 * 3. MEMORY & NEGATIVE NUMBERS [00:10:40] -> [00:26:25]
 * ----------------------------------------------------------------------------
 * - A standard integer is 32 bits. The 31st bit (leftmost) is the SIGN BIT.
 * - 0 means positive.
 * - 1 means negative.
 * * Q: How does the computer store a negative number (e.g., -13)?
 * A: It uses 2's Complement.
 * * ONE'S COMPLEMENT [00:12:58]: 
 * - Simply flip all the bits (0 becomes 1, 1 becomes 0).
 * * TWO'S COMPLEMENT [00:13:36]:
 * - Step 1: Find the 1's complement.
 * - Step 2: Add 1 to it.
 * - The computer stores THIS result in memory to represent the negative number.
 */

void bitwiseOperators() {
    /**
     * ------------------------------------------------------------------------
     * 4. BITWISE OPERATORS [00:14:54]
     * ------------------------------------------------------------------------
     */
    int a = 13; // Binary: 1101
    int b = 7;  // Binary: 0111
    
    // A. AND Operator (&) [00:15:05]
    // Rule: True (1) only if BOTH bits are 1. Otherwise False (0).
    // 1101 & 0111 = 0101 (which is 5 in decimal)
    int and_result = a & b; 
    
    // B. OR Operator (|) [00:17:18]
    // Rule: True (1) if AT LEAST ONE bit is 1.
    // 1101 | 0111 = 1111 (which is 15 in decimal)
    int or_result = a | b;  
    
    // C. XOR Operator (^) [00:18:29]
    // Rule: Returns 1 if the number of 1s is ODD. Returns 0 if the number of 1s is EVEN.
    // Basically: 1 ^ 0 = 1, 0 ^ 1 = 1. Same bits result in 0.
    // 1101 ^ 0111 = 1010 (which is 10 in decimal)
    int xor_result = a ^ b; 
    
    // D. NOT Operator (~) [00:34:26]
    // Rule: Flips all bits.
    // Important logic under the hood:
    // 1. Flip all bits (including sign bit).
    // 2. If the new sign bit is 1 (negative), the computer reads it as 2's complement.
    // ~5 becomes -6. 
    int not_result = ~5;
    
    /**
     * ------------------------------------------------------------------------
     * 5. SHIFT OPERATORS [00:19:53]
     * ------------------------------------------------------------------------
     */
    
    // A. Right Shift (>>)
    // Rule: Shifts bits to the right. The rightmost bits fall off the cliff.
    // Mathematical shortcut: x >> k is equivalent to x / (2^k)
    int right_shift = 13 >> 1; // 1101 becomes 0110 (which is 6). 13 / 2^1 = 6.
    int right_shift_two = 13 >> 2; // 13 / 2^2 = 13 / 4 = 3.
    
    // B. Left Shift (<<) [00:31:47]
    // Rule: Shifts bits to the left. Zeros are added to the right.
    // Mathematical shortcut: x << k is equivalent to x * (2^k)
    int left_shift = 13 << 1; // 13 * 2^1 = 26
    
    // WARNING on Left Shift [00:33:33]: 
    // If you left shift the maximum integer (INT_MAX), it will overflow 
    // into the sign bit and give you weird/negative numbers.
}

/**
 * ----------------------------------------------------------------------------
 * MIN & MAX INTEGER VALUES [00:27:57]
 * ----------------------------------------------------------------------------
 * INT_MAX (Largest Positive Integer): 
 * 31 bits of 1s (Sign bit is 0). Value = 2^31 - 1.
 * * INT_MIN (Smallest Negative Integer):
 * Sign bit is 1, followed by 31 zeros. Value = -(2^31).
 */

int main() {
    // You can test the functions here
    cout << "Decimal 13 to Binary: " << decimalToBinary(13) << endl;
    cout << "Binary 1101 to Decimal: " << binaryToDecimal("1101") << endl;
    
    return 0;
}