/*
 * ============================================================================
 * GREEDY ALGORITHM: Non-Overlapping Intervals (LeetCode 435)
 * ============================================================================
 * 
 * Problem Statement:
 * Given an array of intervals where intervals[i] = [start_i, end_i], return 
 * the MINIMUM number of intervals you need to remove to make the rest of 
 * the intervals non-overlapping.
 * 
 * Note on Overlap Condition:
 * Intervals touching at a point (e.g., [1, 2] and [2, 3]) are NOT considered 
 * overlapping in this problem. An overlap only happens if start < previous_end.
 * 
 * ----------------------------------------------------------------------------
 * THE GREEDY STRATEGY (Inverse of "N Meetings in One Room"):
 * 
 * 1. Maximize Non-Overlapping:
 *    Minimizing removals is identical to MAXIMIZING the number of non-overlapping
 *    intervals we can keep.
 *    -> Removals = Total Intervals (n) - Max Intervals Kept
 * 
 * 2. Why Sort by End Time?
 *    The interval that finishes earliest leaves the widest possible room 
 *    for subsequent intervals to fit without conflict.
 *    -> Sort intervals in ASCENDING order of their end time: intervals[i][1].
 * 
 * 3. Linear Scan:
 *    - Always keep the first interval (it finishes earliest).
 *    - Iterate from the second interval onward:
 *        - If intervals[i][start] >= last_end:
 *            They don't overlap! Keep it, increment count, and update last_end.
 *        - Else:
 *            They overlap! Skip it (effectively removing it).
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// CUSTOM COMPARATOR
// ============================================================================
/*
 * Sorts intervals by their end times in ascending order.
 * intervals[i][0] = start, intervals[i][1] = end
 */
bool comp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

// ============================================================================
// MAIN FUNCTION: eraseOverlapIntervals
// ============================================================================
/*
 * Time Complexity:
 *   - O(N log N) to sort intervals by end time.
 *   - O(N) single linear pass to greedily select compatible intervals.
 *   Total Time Complexity: O(N log N)
 * 
 * Space Complexity:
 *   - O(1) auxiliary space (sorting done in-place or O(log N) stack space).
 */
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) return 0;

    // Step 1: Sort intervals by end time in ascending order
    sort(intervals.begin(), intervals.end(), comp);

    // Step 2: Greedily pick the first interval
    int maxCompatible = 1;
    int lastEndTime = intervals[0][1];

    // Step 3: Iterate through the remaining intervals
    for (int i = 1; i < n; i++) {
        // Condition for NO overlap: start time >= last picked interval's end time
        if (intervals[i][0] >= lastEndTime) {
            maxCompatible++;               // Keep this interval
            lastEndTime = intervals[i][1]; // Update finish line
        }
        // Else: intervals[i] overlaps with our current scheduled set,
        // so we drop/ignore it (it counts toward removals).
    }

    // Step 4: Minimum removals needed = Total intervals - Maximum compatible kept
    return n - maxCompatible;
}

//==========================================================================

/*
 * ============================================================================
 * GREEDY / ARRAY: Insert Interval (LeetCode 57)
 * ============================================================================
 * 
 * Problem Statement:
 * You are given an array of non-overlapping intervals sorted in ascending 
 * order by start time: intervals[i] = [start_i, end_i].
 * You are also given a newInterval = [start, end].
 * 
 * Goal:
 * Insert newInterval into intervals such that intervals is still sorted in 
 * ascending order by start_i and still does not have any overlapping intervals.
 * Merge overlapping intervals if necessary.
 * 
 * ----------------------------------------------------------------------------
 * THE 3-STAGE LINEAR SCAN STRATEGY:
 * Since the input is already sorted and disjoint, we can divide the process 
 * into 3 clear phases using a single pointer `i`:
 * 
 * 1. LEFT SEGMENT (No Overlap, strictly before newInterval):
 *    - Condition: intervals[i][end] < newInterval[start]
 *    - These intervals finish before newInterval even begins.
 *    - Action: Add them directly to the result as-is.
 * 
 * 2. MIDDLE SEGMENT (Overlapping with newInterval):
 *    - Condition: intervals[i][start] <= newInterval[end]
 *    - These intervals collide with newInterval.
 *    - Action: Expand newInterval to cover the entire overlap:
 *        newInterval[start] = min(newInterval[start], intervals[i][start])
 *        newInterval[end]   = max(newInterval[end],   intervals[i][end])
 *    - Once the while loop ends, push the merged newInterval into the result.
 * 
 * 3. RIGHT SEGMENT (No Overlap, strictly after newInterval):
 *    - Condition: The remaining intervals after the merged block.
 *    - Since the input was sorted, nothing to the right can overlap anymore.
 *    - Action: Add the remaining intervals directly to the result.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// MAIN FUNCTION: insert
// ============================================================================
/*
 * Time Complexity: O(N)
 *   - Each interval in the input array is visited exactly once across the 
 *     three while loops.
 * 
 * Space Complexity: O(N)
 *   - O(N) auxiliary space required to store the resultant intervals list.
 *   - O(1) extra space outside of the output container.
 */
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    int n = intervals.size();
    int i = 0;

    // ------------------------------------------------------------------------
    // STAGE 1: Left portion (intervals completely to the left of newInterval)
    // ------------------------------------------------------------------------
    // Keep adding intervals as long as they end BEFORE newInterval starts.
    while (i < n && intervals[i][1] < newInterval[0]) {
        res.push_back(intervals[i]);
        i++;
    }

    // ------------------------------------------------------------------------
    // STAGE 2: Overlapping portion (merge all colliding intervals)
    // ------------------------------------------------------------------------
    // An interval overlaps if its start point is <= newInterval's end point.
    while (i < n && intervals[i][0] <= newInterval[1]) {
        // Expand the merged interval's boundaries
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    // Push the completely merged single interval into the result
    res.push_back(newInterval);

    // ------------------------------------------------------------------------
    // STAGE 3: Right portion (intervals completely to the right of newInterval)
    // ------------------------------------------------------------------------
    // Add all remaining intervals that start after the merged interval ends.
    while (i < n) {
        res.push_back(intervals[i]);
        i++;
    }

    return res;
}

// ============================================================================

/*
 * ============================================================================
 * ARRAY / GREEDY: Merge Overlapping Intervals (LeetCode 56)
 * ============================================================================
 * 
 * Problem Statement:
 * Given an array of intervals where intervals[i] = [start_i, end_i], merge all 
 * overlapping intervals, and return an array of the non-overlapping intervals 
 * that cover all the intervals in the input.
 * 
 * Example:
 * Input:  [[1, 3], [2, 6], [8, 10], [15, 18]]
 * Output: [[1, 6], [8, 10], [15, 18]]
 * Explanation: Since [1, 3] and [2, 6] overlap, they merge into [1, 6].
 * 
 * ----------------------------------------------------------------------------
 * INTERVIEW TIP:
 * Always ask the interviewer whether the intervals are given in sorted order.
 * If not, the very first step is to SORT them by their start times:
 *   intervals[i][0] <= intervals[i+1][0]
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: BRUTE FORCE
// ============================================================================
/*
 * Intuition:
 * 1. Sort the intervals based on start time.
 * 2. Pick an interval at index `i` (let's say [start, end]).
 * 3. Run an inner loop from `j = i + 1` to check subsequent intervals:
 *      - If intervals[j][0] <= end: It overlaps! Expand end = max(end, intervals[j][1]).
 *      - If intervals[j][0] > end: No more overlaps possible since array is sorted; break.
 * 4. Add [start, end] to the result, and advance `i` past all merged elements.
 * 
 * Time Complexity: O(N log N) + O(2N) ≈ O(N log N)
 * Space Complexity: O(N) to store merged result.
 */
vector<vector<int>> merge_bruteForce(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) return intervals;

    // Step 1: Sort by start time
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        int start = intervals[i][0];
        int end = intervals[i][1];

        // Skip if this interval is already merged into the previous group
        if (!ans.empty() && end <= ans.back()[1]) {
            continue;
        }

        // Check subsequent intervals for potential overlaps
        for (int j = i + 1; j < n; j++) {
            if (intervals[j][0] <= end) {
                // Overlaps -> extend boundary
                end = max(end, intervals[j][1]);
            } else {
                // Since intervals are sorted, no further interval can overlap
                break;
            }
        }
        ans.push_back({start, end});
    }

    return ans;
}


// ============================================================================
// APPROACH 2: OPTIMAL (SINGLE PASS AFTER SORTING)
// ============================================================================
/*
 * Intuition:
 * Instead of nested loops, process elements sequentially into `ans`:
 * 
 * 1. Sort all intervals by start time.
 * 2. Traverse each interval:
 *    - CASE A (New Interval): 
 *      If `ans` is empty OR the current interval's start > `ans.back()[1]`:
 *      There is NO overlap with the previously recorded interval.
 *      Push the current interval directly into `ans`.
 * 
 *    - CASE B (Overlap Detected):
 *      If current interval's start <= `ans.back()[1]`:
 *      It overlaps with the interval currently at the back of `ans`.
 *      Merge it by updating:
 *        ans.back()[1] = max(ans.back()[1], current interval's end)
 * 
 * Time Complexity: 
 *   - O(N log N) to sort intervals.
 *   - O(N) single linear scan.
 *   Total Time Complexity: O(N log N)
 * 
 * Space Complexity:
 *   - O(N) auxiliary space for the output array (O(1) extra space).
 */
vector<vector<int>> merge_optimal(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) return intervals;

    // Step 1: Sort intervals by start time
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;

    // Step 2: Linear scan and merge on the fly
    for (int i = 0; i < n; i++) {
        // CASE A: Empty result OR no overlap with the last merged interval
        if (ans.empty() || intervals[i][0] > ans.back()[1]) {
            ans.push_back(intervals[i]);
        }
        // CASE B: Overlap exists -> update the end point of the last interval
        else {
            ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        }
    }

    return ans;
}

// ============================================================================

/*
 * ============================================================================
 * GREEDY / TWO POINTERS: Minimum Platforms (Railway Station Problem)
 * ============================================================================
 * 
 * Problem Statement:
 * Given arrival and departure times of all trains that reach a railway station,
 * find the MINIMUM number of platforms required so that no train is kept waiting.
 * Consider that all trains arrive on the same day and leave on the same day.
 * 
 * Note: If a train arrives and another departs at the exact same minute 
 * (arr[i] <= dep[j]), arrival takes precedence (platform needed).
 * 
 * ----------------------------------------------------------------------------
 * INTUITION & THE "CHRONOLOGICAL TIMELINE" INSIGHT:
 * 
 * 1. Independent Sorting:
 *    Does a platform care *which* specific train arrived or departed? No!
 *    A platform only cares:
 *      - Did an arrival event happen? -> Increase needed platforms (+1).
 *      - Did a departure event happen? -> Free up a platform (-1).
 *    Therefore, we can sort the `arr[]` and `dep[]` arrays independently.
 * 
 * 2. Two-Pointer Simulation:
 *    - Pointer `i` points to the next arrival event.
 *    - Pointer `j` points to the next departure event.
 *    - If arr[i] <= dep[j]: An arrival occurs before (or at same time as) 
 *      the next departure -> count++, i++.
 *    - Else (arr[i] > dep[j]): A train leaves before the next one arrives 
 *      -> count--, j++.
 *    - At each step, record the peak platforms required: max(maxPlatforms, count).
 * 
 * 3. Termination Condition:
 *    Once all trains have arrived (i == n), no more platforms will ever be 
 *    demanded. Any remaining departures will only decrease the count.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: BRUTE FORCE (COUNTING MAXIMUM OVERLAPS)
// ============================================================================
/*
 * For each train `i`, count how many other trains `j` have time intervals 
 * that overlap with train `i`.
 * 
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
int findPlatform_bruteForce(int arr[], int dep[], int n) {
    int maxPlatforms = 1;

    for (int i = 0; i < n; i++) {
        int count = 1; // Train i itself requires a platform
        for (int j = i + 1; j < n; j++) {
            // Check if train i and train j overlap in time
            if ((arr[i] >= arr[j] && arr[i] <= dep[j]) || 
                (arr[j] >= arr[i] && arr[j] <= dep[i])) {
                count++;
            }
        }
        maxPlatforms = max(maxPlatforms, count);
    }

    return maxPlatforms;
}


// ============================================================================
// APPROACH 2: OPTIMAL TWO-POINTER SWEEP (TIMELINE SIMULATION)
// ============================================================================
/*
 * Time Complexity:
 *   - O(N log N) to sort arr[]
 *   - O(N log N) to sort dep[]
 *   - O(2N) to traverse both arrays with two pointers.
 *   Total Time Complexity: O(2 * N log N + 2N) ≈ O(N log N)
 * 
 * Space Complexity:
 *   - O(1) auxiliary space (sorting in-place).
 */
int findPlatform_optimal(int arr[], int dep[], int n) {
    // Step 1: Sort arrivals and departures independently
    sort(arr, arr + n);
    sort(dep, dep + n);

    // Two pointers:
    // i tracks next incoming train (start at 0)
    // j tracks next outgoing train (start at 0)
    int i = 0, j = 0;

    int currentPlatforms = 0;
    int maxPlatforms = 0;

    // Step 2: Simulate chronological timeline
    // The loop only needs to run while trains are still arriving (i < n).
    while (i < n && j < n) {
        // Case A: A train is arriving before or at the time another is departing
        if (arr[i] <= dep[j]) {
            currentPlatforms++; // Occupy a platform
            i++;                // Advance arrival pointer
        } 
        // Case B: A train departs before the next one arrives
        else {
            currentPlatforms--; // Free up a platform
            j++;                // Advance departure pointer
        }

        // Keep track of the peak platform demand throughout the day
        maxPlatforms = max(maxPlatforms, currentPlatforms);
    }

    return maxPlatforms;
}

// ============================================================================
