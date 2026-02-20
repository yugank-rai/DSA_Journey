#include <bits/stdc++.h>
using namespace std;

// PROBLEM 1: Left Rotate Array by 1 Place
// -------------------------------------------------------
// Intuition:
// Shift every element to the left (i-1).
// The first element (index 0) is stored temporarily and placed at the end.
// Time Complexity: O(N)
// Space Complexity: O(1)
void leftRotateByOne(vector<int> &arr) {
    int n = arr.size();
    if (n == 0) return;

    // Step 1: Store the first element
    int temp = arr[0];

    // Step 2: Shift elements left
    for (int i = 1; i < n; i++) {
        arr[i - 1] = arr[i];
    }

    // Step 3: Put the stored element at the back
    arr[n - 1] = temp;
}

// PROBLEM 2: Left Rotate Array by D Places (Optimal)
// -------------------------------------------------------
// Intuition (Reversal Algorithm):
// Instead of using a temp array (which takes O(D) space), we use reversal.
// 1. Reverse first D elements.
// 2. Reverse remaining N-D elements.
// 3. Reverse the whole array.
// Time Complexity: O(2N) -> O(N)
// Space Complexity: O(1)
void leftRotateByD(vector<int> &arr, int d) {
    int n = arr.size();
    // Handle cases where d > n
    d = d % n;

    // C++ STL 'reverse' function takes iterators [start, end)
    
    // Step 1: Reverse first D elements (0 to d-1)
    reverse(arr.begin(), arr.begin() + d);

    // Step 2: Reverse remaining elements (d to n-1)
    reverse(arr.begin() + d, arr.end());

    // Step 3: Reverse the entire array
    reverse(arr.begin(), arr.end());
}
// -----------------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

// PROBLEM: Move Zeros to End
// -------------------------------------------------------
// Goal: Push all 0s to the right, keep non-0s relative order same.
// Optimal Approach (Two Pointer):
// Pointer 'j': Always points to the first zero found.
// Pointer 'i': Iterates to find non-zero elements.
// Whenever 'i' finds a non-zero, we swap(arr[i], arr[j]) and move 'j' forward.
// Time Complexity: O(N)
// Space Complexity: O(1)
void moveZeros(vector<int> &arr) {
    int n = arr.size();
    int j = -1;

    // Step 1: Find the first zero
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            j = i;
            break;
        }
    }

    // If no zero found, we are done
    if (j == -1) return;

    // Step 2: Iterate and Swap
    for (int i = j + 1; i < n; i++) {
        if (arr[i] != 0) {
            // Swap the non-zero (i) with the zero (j)
            swap(arr[i], arr[j]);
            j++; // Move j to the next zero
        }
    }
}

// --------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

// PROBLEM 1: Union of Two Sorted Arrays
// -------------------------------------------------------
// Definition: All unique elements from both arrays.
// Optimal Approach (Two Pointer):
// Since arrays are sorted, we walk through both simultaneously.
// We pick the smaller element to ensure sorted order.
// We only add to our result if it's not a duplicate of the last added element.
// Time Complexity: O(N1 + N2)
// Space Complexity: O(N1 + N2) for returning answer
vector<int> findUnion(vector<int> &a, vector<int> &b) {
    int n1 = a.size();
    int n2 = b.size();
    int i = 0, j = 0;
    vector<int> unionArr;

    while (i < n1 && j < n2) {
        // Case 1: a[i] is smaller
        if (a[i] <= b[j]) {
            // Check for duplicate before adding
            if (unionArr.size() == 0 || unionArr.back() != a[i]) {
                unionArr.push_back(a[i]);
            }
            i++;
        } 
        // Case 2: b[j] is smaller
        else {
            if (unionArr.size() == 0 || unionArr.back() != b[j]) {
                unionArr.push_back(b[j]);
            }
            j++;
        }
    }

    // Add remaining elements from a
    while (i < n1) {
        if (unionArr.size() == 0 || unionArr.back() != a[i]) {
            unionArr.push_back(a[i]);
        }
        i++;
    }

    // Add remaining elements from b
    while (j < n2) {
        if (unionArr.size() == 0 || unionArr.back() != b[j]) {
            unionArr.push_back(b[j]);
        }
        j++;
    }

    return unionArr;
}

// PROBLEM 2: Intersection of Two Sorted Arrays
// -------------------------------------------------------
// Definition: Elements present in BOTH arrays.
// Approach: Two Pointers i and j.
// 1. If a[i] < b[j]: a[i] can't be in intersection (it's too small), so i++.
// 2. If b[j] < a[i]: b[j] is too small, so j++.
// 3. If a[i] == b[j]: Match found! Add to result, then i++ AND j++.
// Time Complexity: O(N1 + N2)
// Space Complexity: O(1) (ignoring return vector space)
vector<int> findIntersection(vector<int> &a, vector<int> &b) {
    int n1 = a.size();
    int n2 = b.size();
    int i = 0, j = 0;
    vector<int> ans;

    while (i < n1 && j < n2) {
        if (a[i] < b[j]) {
            i++;
        } 
        else if (b[j] < a[i]) {
            j++;
        } 
        else {
            // Match found
            ans.push_back(a[i]);
            i++;
            j++;
        }
    }
    return ans;
}