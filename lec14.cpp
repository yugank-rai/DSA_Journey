/* TOPIC: Easy Array Problems
   SOURCE: Striver's A2Z DSA Course - Step 3.1

   PROBLEMS COVERED:
   1. Largest Element in an Array
   2. Second Largest Element in an Array
   3. Check if Array is Sorted
   4. Remove Duplicates from Sorted Array (In-place)

   NOTE: All solutions below are the MOST OPTIMAL versions.
*/

#include <iostream>
#include <vector>
#include <climits> // For INT_MIN

using namespace std;

// =========================================
// 1. LARGEST ELEMENT IN AN ARRAY
// =========================================
/* Logic:
   - Assume the first element (arr[0]) is the largest.
   - Traverse the array. If you find an element > current largest, update largest.
   
   Complexity:
   - Time: O(N) (Single pass)
   - Space: O(1)
*/
int findLargest(int arr[], int n) {
    int largest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

// =========================================
// 2. SECOND LARGEST ELEMENT (Optimal)
// =========================================
/* Logic (Single Pass):
   - We maintain two variables: 'largest' and 'secondLargest'.
   - Initialize 'largest' = arr[0], 'secondLargest' = -1 (or INT_MIN).
   - Iterate through the array:
     CASE 1: arr[i] > largest
       - The current largest becomes the SECOND largest.
       - The new element becomes the LARGEST.
     CASE 2: arr[i] < largest but arr[i] > secondLargest
       - We found a new candidate for second largest. Update 'secondLargest'.
   
   Complexity:
   - Time: O(N) (Single pass)
   - Space: O(1)
*/
int findSecondLargest(int arr[], int n) {
    if (n < 2) return -1; // Edge case: Array too small

    int largest = arr[0];
    int sLargest = -1; // Assuming non-negative integers. Use INT_MIN if negatives exist.

    for (int i = 1; i < n; i++) {
        
        // If current element is greater than the largest found so far
        if (arr[i] > largest) {
            sLargest = largest; // Old largest becomes second largest
            largest = arr[i];   // Update largest
        }
        // If current is smaller than largest, but greater than second largest
        // AND it is not equal to largest (to handle duplicates like [7, 7, 5])
        else if (arr[i] < largest && arr[i] > sLargest) {
            sLargest = arr[i];
        }
    }
    return sLargest;
}

// =========================================
// 3. CHECK IF ARRAY IS SORTED
// =========================================
/* Logic:
   - Iterate from index 1 to n-1.
   - Check if current element (arr[i]) is greater than or equal to previous (arr[i-1]).
   - If arr[i] < arr[i-1] at any point, the array is NOT sorted. Return false.
   
   Complexity:
   - Time: O(N)
   - Space: O(1)
*/
bool checkSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        // If current element is smaller than previous, order is broken
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// =========================================
// 4. REMOVE DUPLICATES FROM SORTED ARRAY
// =========================================
/* Logic (Two Pointer Approach):
   - Since array is sorted, duplicates are grouped together.
   - Pointer 'i': Points to the last unique element found.
   - Pointer 'j': Iterates through the array to find new unique elements.
   - When arr[j] != arr[i], it means we found a NEW unique element.
     1. Increment 'i'.
     2. Place arr[j] at the new 'i' position.
   - Return (i + 1) as the count of unique elements.

   Complexity:
   - Time: O(N)
   - Space: O(1) (In-place modification)
*/
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;

    int i = 0; // Pointer for position of unique elements

    for (int j = 1; j < n; j++) {
        // If we find a different element
        if (arr[j] != arr[i]) {
            i++;             // Move unique pointer forward
            arr[i] = arr[j]; // Place the new unique element there
        }
    }
    // i is the index, so (i+1) is the count of unique elements
    return i + 1;
}

// Helper to print array
void printArray(int arr[], int n) {
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {1, 2, 4, 7, 7, 5}; 
    int n = 6;

    // 1. Largest
    cout << "Largest: " << findLargest(arr, n) << endl;

    // 2. Second Largest
    cout << "Second Largest: " << findSecondLargest(arr, n) << endl;

    // 3. Check Sorted
    int sortedArr[] = {1, 2, 3, 4, 5};
    cout << "Is Sorted (1=Yes, 0=No): " << checkSorted(sortedArr, 5) << endl;

    // 4. Remove Duplicates
    int dupArr[] = {1, 1, 2, 2, 2, 3, 3};
    int nDup = 7;
    cout << "\nOriginal Array with Duplicates: ";
    printArray(dupArr, nDup);
    
    int k = removeDuplicates(dupArr, nDup);
    
    cout << "Array after removing duplicates (First " << k << " elements): ";
    printArray(dupArr, k);

    return 0;
}