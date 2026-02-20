/* TOPIC: Merge Sort Algorithm
   SOURCE: Striver's A2Z DSA Course - Step 2.2

   STRATEGY: Divide and Conquer
   1. Divide: Recursively split the array into halves until single elements remain.
   2. Merge: Combine (merge) two sorted halves back into a single sorted array.

   COMPLEXITY:
   - Time Complexity: O(N log N) 
     (Reason: N for merging, log N for dividing/splitting steps).
   - Space Complexity: O(N) 
     (Reason: Temporary vector used during the merge step).
*/

#include <iostream>
#include <vector>

using namespace std;

// =========================================
// 1. THE MERGE FUNCTION
// =========================================
/* Logic:
   - We have two sorted parts:
     1. Left Part: [low ... mid]
     2. Right Part: [mid+1 ... high]
   - We need to merge them into a single sorted sequence.
   - We use a temporary vector to store elements in the correct order.
   - We use two pointers (left, right) to compare elements.
*/
void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // Temporary array to store merged elements
    
    // Pointers for the two halves
    int left = low;      // Starting index of left half
    int right = mid + 1; // Starting index of right half

    // LOOP: Run until one of the halves is exhausted
    while (left <= mid && right <= high) {
        
        // Compare elements from left and right halves
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++; // Move left pointer
        } 
        else {
            temp.push_back(arr[right]);
            right++; // Move right pointer
        }
    }

    // IF LEFT HALF STILL HAS ELEMENTS
    // (Right half got exhausted first)
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    // IF RIGHT HALF STILL HAS ELEMENTS
    // (Left half got exhausted first)
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // COPY BACK: Move elements from 'temp' back to the original 'arr'
    // 'temp' stores elements from index 0 to (high-low).
    // 'arr' needs to be updated from index 'low' to 'high'.
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

// =========================================
// 2. THE MERGE SORT FUNCTION (Recursive)
// =========================================
/* Logic:
   - Find the middle index.
   - Recursively call mergeSort for the left half.
   - Recursively call mergeSort for the right half.
   - Once the halves return (sorted), call 'merge()' to combine them.
*/
void mergeSort(vector<int> &arr, int low, int high) {
    // Base Case: If the array has 1 or 0 elements, it is already sorted.
    if (low >= high) return;

    // Divide: Find middle index
    int mid = (low + high) / 2;

    // Recursion: Sort the Left Half [low ... mid]
    mergeSort(arr, low, mid);

    // Recursion: Sort the Right Half [mid+1 ... high]
    mergeSort(arr, mid + 1, high);

    // Conquer: Merge the two sorted halves
    merge(arr, low, mid, high);
}

// Helper to print vector
void printVector(const vector<int> &arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {9, 4, 7, 6, 3, 1, 5};
    int n = arr.size();

    cout << "Original Array: ";
    printVector(arr);

    cout << "--- Merge Sort ---" << endl;
    
    // Call Merge Sort on the full array (index 0 to n-1)
    mergeSort(arr, 0, n - 1);

    cout << "Sorted Array:   ";
    printVector(arr);

    return 0;
}