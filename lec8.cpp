/* TOPIC: Reverse Array & Palindrome Check (Recursion)
   SOURCE: Striver's A2Z DSA Course - Video Re 4

   CONCEPTS COVERED:
   1. Reverse an Array (Using 2 Pointers)
   2. Reverse an Array (Using 1 Pointer)
   3. Check if String is Palindrome (Using Recursion)
   
   COMPLEXITY:
   - Time Complexity: O(N/2) -> which is effectively O(N)
   - Space Complexity: O(N/2) -> Aux Stack Space O(N)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For swap()

using namespace std;

// =========================================
// 1. REVERSE ARRAY (Two Pointers Recursion)
// =========================================
/* Logic:
   - Use two pointers: 'L' (Left) and 'R' (Right).
   - Swap arr[L] and arr[R].
   - Recursively call for (L+1, R-1).
   - Stop when L >= R (pointers cross each other).
*/
void reverseArrayTwoPointers(int l, int r, int arr[]) {
    // Base Case: If Left pointer crosses or meets Right, stop.
    if (l >= r) {
        return;
    }
    
    // Swap the elements at L and R
    swap(arr[l], arr[r]);
    
    // Recursive Call: Move L forward, R backward
    reverseArrayTwoPointers(l + 1, r - 1, arr);
}

// =========================================
// 2. REVERSE ARRAY (One Pointer Recursion)
// =========================================
/* Logic:
   - We only use 'i' (index).
   - If we know 'i' is the start, the corresponding end index is 'n - i - 1'.
   - Swap arr[i] and arr[n - i - 1].
   - Stop when 'i' reaches the middle (n / 2).
*/
void reverseArrayOnePointer(int i, int arr[], int n) {
    // Base Case: If i reaches the middle, stop.
    if (i >= n / 2) {
        return;
    }
    
    // Swap index 'i' with index 'n - i - 1'
    swap(arr[i], arr[n - i - 1]);
    
    // Recursive Call: Move to the next index
    reverseArrayOnePointer(i + 1, arr, n);
}

// =========================================
// 3. CHECK PALINDROME (String)
// =========================================
/* Definition: A string is a palindrome if it reads the same forward and backward.
   Example: "MADAM" -> Reverse -> "MADAM" (True)
   
   Logic:
   - Check if str[i] is equal to str[n - i - 1].
   - If NOT equal, return false immediately.
   - If equal, recursively check the next inner pair (i + 1).
   - Base Case: If we reach the middle (i >= n/2), it means all pairs matched. Return true.
*/
bool checkPalindrome(int i, string &s) {
    // Base Case: If we crossed the middle, all checks passed.
    if (i >= s.size() / 2) {
        return true;
    }
    
    // Check if current pair does NOT match
    if (s[i] != s[s.size() - i - 1]) {
        return false;
    }
    
    // Recursive Call: Check next pair
    return checkPalindrome(i + 1, s);
}

int main() {
    // --- TEST 1: Reverse Array (1 Pointer) ---
    int n = 5;
    int arr[5] = {1, 2, 3, 4, 5};
    
    cout << "Original Array: ";
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;

    // Call function
    reverseArrayOnePointer(0, arr, n);
    
    cout << "Reversed Array: ";
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;

    // --- TEST 2: Palindrome Check ---
    string s = "MADAM";
    // NOTE: For 'MADSM', it would return false (0)
    
    bool isPal = checkPalindrome(0, s);
    
    cout << "\nString: " << s << endl;
    if (isPal) cout << "Result: Palindrome" << endl;
    else cout << "Result: Not a Palindrome" << endl;

    return 0;
}