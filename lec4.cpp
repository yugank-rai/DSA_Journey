/* TOPIC: Basic Maths for DSA (Logic Building)
   SOURCE: Striver's A2Z DSA Course - Step 1.4

   CONCEPTS COVERED:
   1. Extraction of Digits (Modulo % and Division /)
   2. Reverse a Number
   3. Palindrome Check
   4. Armstrong Number
   5. Print all Divisors (Brute Force vs Optimized)
   6. Prime Check (Brute Force vs Optimized)
   7. GCD / HCF (Euclidean Algorithm)
*/

#include <iostream>
#include <vector>
#include <cmath>   // For log10
#include <algorithm> // For sort, min

using namespace std;

// =========================================
// 1. COUNT DIGITS / EXTRACTION OF DIGITS
// =========================================
/* Logic: 
   - To get the last digit: n % 10
   - To remove the last digit: n / 10
   - Repeat until n becomes 0.
*/
int countDigits(int n) {
    int count = 0;
    int temp = n; 
    
    while (temp > 0) {
        // int lastDigit = temp % 10; // (Optional: If you need to process the digit)
        temp = temp / 10;
        count++;
    }
    return count;
}

// Optimized Way (Logarithmic)
// Time Complexity: O(1)
void countDigitsLog(int n) {
    int count = (int)(log10(n) + 1);
    cout << "Digits (Log Method): " << count << endl;
}

// =========================================
// 2. REVERSE A NUMBER
// =========================================
/* Logic:
   - Extract last digit (lastDigit = n % 10)
   - Build new number: reverseNum = (reverseNum * 10) + lastDigit
   Example: 123
   1. 0*10 + 3 = 3
   2. 3*10 + 2 = 32
   3. 32*10 + 1 = 321
*/
int reverseNumber(int n) {
    int revNum = 0;
    while (n > 0) {
        int lastDigit = n % 10;
        revNum = (revNum * 10) + lastDigit;
        n = n / 10;
    }
    return revNum;
}

// =========================================
// 3. CHECK PALINDROME
// =========================================
/* Definition: A number that reads the same backward as forward (e.g., 121, 1331).
   Logic: 
   - Store the original number in a duplicate variable.
   - Reverse the number.
   - Compare reversed number with duplicate.
*/
void checkPalindrome(int n) {
    int duplicate = n; // Store copy because n will become 0
    int revNum = 0;
    
    while (n > 0) {
        int lastDigit = n % 10;
        revNum = (revNum * 10) + lastDigit;
        n = n / 10;
    }

    if (duplicate == revNum) 
        cout << duplicate << " is a Palindrome." << endl;
    else 
        cout << duplicate << " is NOT a Palindrome." << endl;
}

// =========================================
// 4. ARMSTRONG NUMBER
// =========================================
/* Definition: A number equals the sum of its digits raised to the power of the number of digits.
   Example: 371 (3 digits)
   3^3 + 7^3 + 1^3 = 27 + 343 + 1 = 371 (True)
   
   Example: 1634 (4 digits)
   1^4 + 6^4 + 3^4 + 4^4 = 1634 (True)
*/
void checkArmstrong(int n) {
    int sum = 0;
    int duplicate = n;
    
    // (Optional) Calculate number of digits dynamically if needed
    // For this standard example, we assume cube (power of 3) often used for 3 digit numbers
    // But generalized code handles any power.
    int k = to_string(n).length(); // Number of digits

    while (n > 0) {
        int lastDigit = n % 10;
        sum = sum + pow(lastDigit, k); 
        n = n / 10;
    }

    if (sum == duplicate) cout << duplicate << " is an Armstrong Number." << endl;
    else cout << duplicate << " is NOT an Armstrong Number." << endl;
}

// =========================================
// 5. PRINT ALL DIVISORS
// =========================================
/* Brute Force: Loop from 1 to n. O(N).
   
   Optimized Logic (Square Root Method):
   - Divisors come in pairs. E.g., for 36:
     1 x 36
     2 x 18
     3 x 12
     4 x 9
     6 x 6
   - If 'i' divides 'n', then 'n/i' also divides 'n'.
   - We only need to loop up to sqrt(n).
   
   Time Complexity: O(sqrt(N))
*/
void printDivisors(int n) {
    vector<int> divisors;
    
    // Loop only till sqrt(n)
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i); // Add the first factor
            
            // Add the second factor only if it's different (avoid 6x6 adding 6 twice)
            if ((n / i) != i) {
                divisors.push_back(n / i);
            }
        }
    }
    
    // Sort to print in order
    sort(divisors.begin(), divisors.end());
    
    cout << "Divisors of " << n << ": ";
    for (auto it : divisors) cout << it << " ";
    cout << endl;
}

// =========================================
// 6. CHECK FOR PRIME
// =========================================
/* Definition: A number with exactly 2 factors: 1 and itself.
   
   Optimized Logic:
   - Count factors looping only up to sqrt(n).
   - If count > 2, break early? No, just count.
   - Actually, easier: Check if any number between 2 and sqrt(n) divides n.
     If yes, it's NOT prime.
*/
void checkPrime(int n) {
    int count = 0; // Number of factors
    
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++; // Found one factor
            if ((n / i) != i) count++; // Found pair factor
        }
    }
    
    if (count == 2) cout << n << " is a Prime Number." << endl;
    else cout << n << " is NOT a Prime Number." << endl;
}

// =========================================
// 7. GCD / HCF (Euclidean Algorithm)
// =========================================
/* Brute Force: Iterate from min(n1, n2) down to 1. O(min(n1, n2)).
   
   Euclidean Algorithm:
   gcd(a, b) = gcd(a - b, b) where a > b.
   
   Better Euclidean Algorithm (using Modulo):
   gcd(a, b) = gcd(a % b, b) where a > b.
   Keep doing a % b until one of them becomes 0.
   The other non-zero number is the answer.
   
   Time Complexity: O(log(phi) min(a,b)) -> Very fast.
*/
void findGCD(int a, int b) {
    int originalA = a, originalB = b;
    
    while (a > 0 && b > 0) {
        if (a > b) a = a % b;
        else b = b % a;
    }
    
    // Once loop ends, one is 0. The other is GCD.
    if (a == 0) cout << "GCD of " << originalA << " & " << originalB << " is: " << b << endl;
    else cout << "GCD of " << originalA << " & " << originalB << " is: " << a << endl;
}

int main() {
    int n = 371; // Example for Armstrong
    int n2 = 121; // Example for Palindrome
    int n3 = 36;  // Example for Divisors
    
    cout << "--- Basic Maths Demo ---" << endl;
    
    checkPalindrome(n2);
    checkArmstrong(n);
    printDivisors(n3);
    checkPrime(17);
    findGCD(52, 10);
    
    return 0;
}