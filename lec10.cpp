/* TOPIC: Hashing (Basics & Array Hashing)
   SOURCE: Striver's A2Z DSA Course - Step 1.6

   THE PROBLEM:
   Given an array, we need to answer Q queries.
   In each query, we are given a number X, and we need to tell 
   how many times X appears in the array.

   APPROACH 1: BRUTE FORCE
   - For every query, traverse the array and count occurrences.
   - Time Complexity: O(Q * N)
   - If Q = 10^5 and N = 10^5 -> 10^10 operations.
   - Result: TLE (Time Limit Exceeded) because 1 sec ≈ 10^8 operations.

   APPROACH 2: HASHING (Pre-storing and Fetching)
   - We create a "Hash Array" (Frequency Array).
   - We iterate the input array ONCE and update the hash array.
   - We answer queries instantly by checking the hash array.
   - Time Complexity: O(N) for pre-computation + O(Q) for fetching = O(N + Q).
*/

#include <iostream>
using namespace std;

// =========================================
// 1. NUMBER HASHING (Using Arrays)
// =========================================
/* LIMITATIONS OF ARRAY HASHING:
   1. Max Array Size in main(): ~10^6 (1,000,000)
   2. Max Array Size Global:    ~10^7 (10,000,000)
   
   If the problem says array elements can be up to 10^9, 
   we CANNOT use this method (We need C++ Maps for that).
*/

// Global definition allows larger size (approx 10^7)
// int hashArr[10000001]; 

void numberHashing() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements: ";
    // PRE-COMPUTE STEP
    // We need a hash array large enough to store the MAX number in input.
    // Example: If input has 12, we need index 12 (size 13).
    // Let's assume max element is small for this demo (< 13).
    
    // NOTE: In main(), max size is 10^6.
    // Hash array is initialized to 0 automatically if global, 
    // but inside main, we must initialize it (e.g., {0}).
    int hash[13] = {0}; 

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        // LOGIC: Go to the index matching the number and increment.
        hash[arr[i]] += 1;
    }

    int q;
    cout << "Enter number of queries: ";
    cin >> q;
    
    // FETCHING STEP
    cout << "Enter queries: " << endl;
    while (q--) {
        int number;
        cin >> number;
        
        // Fetch result instantly O(1)
        cout << number << " appears " << hash[number] << " times." << endl;
    }
}

// =========================================
// 2. CHARACTER HASHING
// =========================================
/* Logic:
   - Characters are mapped to integers using ASCII.
   - 'a' corresponds to index 0, 'b' to 1... 'z' to 25.
   - Formula: index = char - 'a'
   - If the string has ALL characters (uppercase + lowercase + symbols),
     use a hash array of size 256 (Total ASCII characters).
*/
void characterHashing() {
    string s;
    cout << "\nEnter string: ";
    cin >> s;

    // Array of size 26 for lowercase 'a'-'z'
    int hash[26] = {0}; 

    // PRE-COMPUTE
    for (int i = 0; i < s.size(); i++) {
        // 'a' - 'a' = 0
        // 'b' - 'a' = 1
        // 'c' - 'a' = 2
        hash[s[i] - 'a']++; 
    }

    int q;
    cout << "Enter char queries: ";
    cin >> q;

    // FETCHING
    while (q--) {
        char c;
        cin >> c;
        
        // Fetch count using the mapping formula
        cout << c << " appears " << hash[c - 'a'] << " times." << endl;
    }
}

// =========================================
// 3. UNIVERSAL CHARACTER HASHING (Size 256)
// =========================================
/* If input contains 'A', 'a', '$', '1'...
   Don't subtract 'a'. Just use the raw ASCII value as index.
*/
void universalCharHashing() {
    string s; 
    cin >> s;
    
    // 256 covers all extended ASCII characters
    int hash[256] = {0}; 
    
    for(int i = 0; i < s.size(); i++) {
        hash[s[i]]++; // Auto-casts char to int (ASCII)
    }
    
    int q; cin >> q;
    while(q--) {
        char c; cin >> c;
        cout << hash[c] << endl;
    }
}

int main() {
    // Uncomment to run specific parts
    // numberHashing();
    // characterHashing();
    
    return 0;
}