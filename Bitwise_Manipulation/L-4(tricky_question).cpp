/**
 * ===========================================================================
 * DSA Notes: Divide Two Integers (LeetCode 29)
 * Topic: Bit Manipulation / Mathematics
 * ===========================================================================
 * PROBLEM STATEMENT:
 * Given two integers `dividend` and `divisor`, divide them without using 
 * multiplication, division, and mod operator.
 * Truncate the decimal part (return the integer quotient).
 * Handle 32-bit signed integer overflows properly.
 * ---------------------------------------------------------------------------
 * Naive Approach: 
 * Keep subtracting the `divisor` from the `dividend` and increment a counter 
 * until `dividend` becomes less than `divisor`.
 * Time Complexity: O(Dividend) -> Will result in Time Limit Exceeded (TLE).
 * * * Optimized Approach: Bit Manipulation (O(log^2 N) Time, O(1) Space)
 * Instead of subtracting the divisor one by one, we can subtract it in 
 * chunks of powers of 2.
 * * Example: 22 / 3
 * We want to find how many times 3 fits in 22.
 * Instead of 22 - 3 - 3 - 3...
 * We check powers of 2 multiplied by 3 (using left shift):
 * - Can we remove 3 * (2^0) = 3? Yes.
 * - Can we remove 3 * (2^1) = 6? Yes.
 * - Can we remove 3 * (2^2) = 12? Yes.
 * - Can we remove 3 * (2^3) = 24? No, 24 > 22.
 * * So, we remove 12 from 22. Remaining = 10. We added 2^2 (4) to our quotient.
 * Now check for 10:
 * - Can we remove 3 * (2^0) = 3? Yes.
 * - Can we remove 3 * (2^1) = 6? Yes.
 * - Can we remove 3 * (2^2) = 12? No, 12 > 10.
 * * So, remove 6 from 10. Remaining = 4. We add 2^1 (2) to our quotient.
 * Now check for 4:
 * - Can we remove 3 * (2^0) = 3? Yes.
 * - Can we remove 3 * (2^1) = 6? No.
 * * Remove 3 from 4. Remaining = 1. We add 2^0 (1) to our quotient.
 * Remaining (1) < Divisor (3). Stop.
 * Final Quotient = 4 + 2 + 1 = 7.
 */

#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

// Function to divide two integers [00:09:18]
int divide(int dividend, int divisor) {
    // Edge case: overflow when dividing INT_MIN by -1
    // INT_MIN is -2^31. Dividing by -1 gives +2^31, which exceeds INT_MAX.
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }
    
    // Determine the sign of the result
    // The result is negative ONLY if exactly one of them is negative. [00:09:59]
    bool sign = (dividend >= 0) == (divisor >= 0); 
    // True means positive result, False means negative result.
    
    // Convert both to positive long to prevent overflow during absolute value conversion
    // e.g., abs(INT_MIN) overflows a standard 32-bit signed int. [00:18:03]
    long n = abs((long)dividend);
    long d = abs((long)divisor);
    
    long quotient = 0;
    
    // While the remaining dividend is greater than or equal to divisor
    while (n >= d) {
        int count = 0;
        
        // Find the maximum power of 2 we can multiply the divisor by 
        // without exceeding the current dividend 'n'.
        // (d << (count + 1)) is equivalent to d * 2^(count + 1)
        while (n >= (d << (count + 1))) {
            count++;
        }
        
        // Add the corresponding power of 2 to our quotient
        // (1 << count) is equivalent to 2^count
        quotient += (1L << count);
        
        // Subtract the subtracted chunk from 'n'
        n -= (d << count);
    }
    
    // Apply the sign to the calculated quotient
    // If sign is false (it was supposed to be negative), negate it.
    long finalResult = sign ? quotient : -quotient;
    
    // Handle specific boundary conditions ensuring it falls in 32-bit integer limits
    if (finalResult > INT_MAX) return INT_MAX;
    if (finalResult < INT_MIN) return INT_MIN;
    
    return (int)finalResult;
}

int main() {
    // --- Test Cases ---
    
    int dividend1 = 22, divisor1 = 3;
    cout << dividend1 << " / " << divisor1 << " = " << divide(dividend1, divisor1) << "\n";
    // Expected output: 7

    int dividend2 = 7, divisor2 = -3;
    cout << dividend2 << " / " << divisor2 << " = " << divide(dividend2, divisor2) << "\n";
    // Expected output: -2
    
    int dividend3 = INT_MIN, divisor3 = -1;
    cout << "INT_MIN / -1 = " << divide(dividend3, divisor3) << " (Overflow Handled)\n";
    // Expected output: 2147483647 (INT_MAX)

    return 0;
}