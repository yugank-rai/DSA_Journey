/* TOPIC: Quick Sort Algorithm
   SOURCE: Striver's A2Z DSA Course - Step 2.2

   STRATEGY: Divide and Conquer
   1. Pick a Pivot (We use the 1st element).
   2. Partition: Place the pivot in its CORRECT position in the sorted array.
      - All elements smaller than pivot -> LEFT
      - All elements greater than pivot -> RIGHT
   3. Recursively repeat for Left and Right halves.

   COMPLEXITY:
   - Time Complexity: O(N log N) (Average Case)
     - Worst Case: O(N^2) (When array is already sorted and we pick 1st element as pivot).
   - Space Complexity: O(1) 
     - No extra array is used (unlike Merge Sort).
     - However, Recursion Stack Space is O(N) in worst case.
*/

#include <iostream>
#include <vector>
#include <algorithm> // For swap()

using namespace std;

// =========================================
// 1. THE PARTITION FUNCTION
// =========================================
/* Logic:
   - Pivot = arr[low] (First element).
   - Goal: Find the correct index for 'Pivot' so that:
     [ ... < Pivot ... ] PIVOT [ ... > Pivot ... ]
   
   - We use two pointers: 'i' (low) and 'j' (high).
   - 'i' looks for element GREATER than pivot.
   - 'j' looks for element SMALLER than pivot.
   - If found, SWAP them.
   - Stop when i crosses j.
*/
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        
        // Find the first element GREATER than pivot from the left
        // We iterate as long as elements are <= pivot
        // Boundary check: i should not exceed high
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }

        // Find the first element SMALLER than pivot from the right
        // We iterate as long as elements are > pivot
        // Boundary check: j should not go below low (redundant but safe)
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }

        // If i and j have not crossed, it means we found 
        // a large element on left and small element on right. SWAP them.
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    // Once i crosses j, 'j' points to the correct position for the pivot.
    // Why? Because 'j' crossed 'i', meaning 'j' is now at the last element <= pivot.
    swap(arr[low], arr[j]);
    
    // Return the partition index (where pivot is now placed)
    return j; 
}

// =========================================
// 2. THE QUICK SORT FUNCTION (Recursive)
// =========================================
void qs(vector<int> &arr, int low, int high) {
    // Base Case: If low >= high, the subarray has 1 or 0 elements (sorted).
    if (low < high) {
        
        // 1. Partition the array and get the pivot's correct index
        int pIndex = partition(arr, low, high);
        
        // 2. Recursively sort the LEFT part (low to pIndex - 1)
        qs(arr, low, pIndex - 1);
        
        // 3. Recursively sort the RIGHT part (pIndex + 1 to high)
        qs(arr, pIndex + 1, high);
    }
}

// Helper Function wrapper
vector<int> quickSort(vector<int> arr) {
    qs(arr, 0, arr.size() - 1);
    return arr;
}

int main() {
    vector<int> arr = {4, 6, 2, 5, 7, 9, 1, 3};
    int n = arr.size();

    cout << "Original Array: ";
    for (auto it : arr) cout << it << " ";
    cout << endl;

    cout << "--- Quick Sort ---" << endl;
    
    // Call Quick Sort
    qs(arr, 0, n - 1);

    cout << "Sorted Array:   ";
    for (auto it : arr) cout << it << " ";
    cout << endl;

    return 0;
}