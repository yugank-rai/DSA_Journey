/* TOPIC: Sorting Algorithms - Part 1
   SOURCE: Striver's A2Z DSA Course - Step 2.1

   ALGORITHMS COVERED:
   1. Selection Sort (Select Minimum & Swap)
   2. Bubble Sort (Push Maximum to the End)
   3. Insertion Sort (Place Element in Correct Position)

   NOTE:
   - All sorting functions take the array and its size (n) as input.
   - We use the `swap()` function (or a temporary variable logic).
*/

#include <iostream>
#include <vector>
#include <algorithm> // For swap()

using namespace std;

// =========================================
// 1. SELECTION SORT
// =========================================
/* ALGORITHM: "Select Minimums & Swap"
   
   Logic:
   1. Iterate from i = 0 to n-2.
   2. For each i, assume arr[i] is the minimum.
   3. Search the rest of the array (from i to n-1) to find the ACTUAL minimum.
   4. Swap the actual minimum with arr[i].
   5. Result: The beginning of the array becomes sorted step-by-step.

   Complexity:
   - Time: O(N^2) (Best, Average, Worst) -> Always runs two loops.
   - Space: O(1)
*/

void selectionSort(int arr[], int n) {
    // Outer loop runs from 0 to n-2
    // Why n-2? Because if n-1 elements are sorted, the last one is auto-sorted.
    for (int i = 0; i <= n - 2; i++) {
        
        int mini = i; // Assume current index is the minimum
        
        // Inner loop: Find the minimum in the unsorted part (i to n-1)
        for (int j = i; j <= n - 1; j++) {
            if (arr[j] < arr[mini]) {
                mini = j; // Update index of minimum
            }
        }
        
        // Swap the found minimum with the element at the current position (i)
        // Manual Swap Logic:
        // int temp = arr[mini];
        // arr[mini] = arr[i];
        // arr[i] = temp;
        
        swap(arr[mini], arr[i]); // Using C++ built-in swap
    }
}

// =========================================
// 2. BUBBLE SORT
// =========================================
/* ALGORITHM: "Push Maximum to the End" via Adjacent Swaps.
   
   Logic:
   1. Compare adjacent elements (j and j+1).
   2. If arr[j] > arr[j+1], SWAP them.
   3. Repeat this for all elements. After the first pass, the Max element reaches the end.
   4. Reduce the loop range for the next pass (since last element is sorted).

   Optimization:
   - If NO swaps happen in a pass, the array is already sorted. Break early.

   Complexity:
   - Time (Worst/Avg): O(N^2)
   - Time (Best): O(N) (If array is already sorted & optimized code is used)
   - Space: O(1)
*/

void bubbleSort(int arr[], int n) {
    // Outer loop runs from n-1 down to 1
    // It dictates the range of the unsorted array (0 to i)
    for (int i = n - 1; i >= 1; i--) {
        
        int didSwap = 0; // Optimization Flag
        
        // Inner loop runs from 0 to i-1
        // It pushes the max element to index 'i'
        for (int j = 0; j <= i - 1; j++) {
            
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                didSwap = 1;
            }
        }
        
        // OPTIMIZATION: If no swaps occurred, array is sorted.
        if (didSwap == 0) {
            break;
        }
    }
}

// =========================================
// 3. INSERTION SORT
// =========================================
/* ALGORITHM: "Takes an element & places it in its correct order"
   
   Logic:
   1. Start from i = 0.
   2. Take the element at i. Look at its LEFT side.
   3. Keep swapping it with the left neighbor as long as the left neighbor is GREATER.
   4. Stop when the left neighbor is smaller or you reach the start.
   
   Analogy: Sorting playing cards in your hand.

   Complexity:
   - Time (Worst/Avg): O(N^2)
   - Time (Best): O(N) (If array is sorted, the inner while loop never runs).
   - Space: O(1)
*/

void insertionSort(int arr[], int n) {
    // Outer loop: iterate through every element
    for (int i = 0; i <= n - 1; i++) {
        
        int j = i;
        
        // Inner loop: Comparison happens to the LEFT (j-1)
        // Run as long as:
        // 1. We are not at the start (j > 0)
        // 2. The left neighbor is greater than current (arr[j-1] > arr[j])
        while (j > 0 && arr[j - 1] > arr[j]) {
            
            swap(arr[j - 1], arr[j]);
            j--; // Move left to check further
        }
    }
}

// Helper to print array
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n = 6;
    int arr1[] = {13, 46, 24, 52, 20, 9};
    int arr2[] = {13, 46, 24, 52, 20, 9};
    int arr3[] = {13, 46, 24, 52, 20, 9};

    cout << "Original Array: ";
    printArray(arr1, n);

    cout << "\n--- Selection Sort ---" << endl;
    selectionSort(arr1, n);
    printArray(arr1, n);

    cout << "\n--- Bubble Sort ---" << endl;
    bubbleSort(arr2, n);
    printArray(arr2, n);

    cout << "\n--- Insertion Sort ---" << endl;
    insertionSort(arr3, n);
    printArray(arr3, n);

    return 0;
}