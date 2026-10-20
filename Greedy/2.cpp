/*
 * ============================================================================
 * GREEDY ALGORITHM: N Meetings in One Room
 * ============================================================================
 * 
 * Problem Statement:
 * You are given a single meeting room and 'N' meetings. Each meeting has:
 *   - start[i]: Starting time of the meeting
 *   - end[i]  : Ending time of the meeting
 * 
 * Goal:
 * Find the MAXIMUM number of meetings that can be accommodated in the single 
 * room without overlapping. A new meeting can only start strictly AFTER the 
 * previous one has finished (start > previous_end).
 * (Some variations also ask for the exact order/indices of meetings).
 * 
 * ----------------------------------------------------------------------------
 * THE GREEDY STRATEGY:
 * Why sort by end time rather than start time?
 * - If you pick a meeting that starts earliest, it might run for a very long 
 *   time (e.g., [0, 100]) and block dozens of shorter meetings.
 * - By picking the meeting that FINISHES EARLIEST, you free up the room 
 *   at the earliest possible moment, leaving the maximum amount of time 
 *   available to schedule remaining meetings.
 * 
 * Steps:
 * 1. Store start time, end time, and 1-based original position for each meeting.
 * 2. Sort all meetings in ASCENDING order of their end time.
 * 3. Schedule the first meeting (as it finishes earliest).
 * 4. Iterate through the rest: if a meeting's start time > current free time,
 *    schedule it and update the free time to its end time.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Data structure to hold meeting details
struct Meeting {
    int start;
    int end;
    int pos; // 1-based index to track order if required by the interviewer
};

// ============================================================================
// CUSTOM COMPARATOR
// ============================================================================
/*
 * Sort meetings in ascending order of finish/end time.
 * If two meetings have the same end time, you can break ties using position 
 * (pos), though sorting purely by end time is sufficient for counting.
 */
bool comp(Meeting m1, Meeting m2) {
    if (m1.end < m2.end) return true;
    if (m1.end > m2.end) return false;
    return m1.pos < m2.pos; // Tie-breaker: earlier original index
}

// ============================================================================
// MAIN FUNCTION: maxMeetings
// ============================================================================
/*
 * Time Complexity:
 *   - O(N) to package start and end times into struct array.
 *   - O(N log N) to sort the meetings based on end time.
 *   - O(N) to iterate through the meetings and greedily pick valid ones.
 *   Total Time Complexity: O(N log N)
 * 
 * Space Complexity:
 *   - O(N) to store the Meeting objects and selected meeting order.
 */
int maxMeetings(int start[], int end[], int n) {
    vector<Meeting> meet(n);

    // Step 1: Pack the data together
    for (int i = 0; i < n; i++) {
        meet[i].start = start[i];
        meet[i].end = end[i];
        meet[i].pos = i + 1; // 1-based indexing for display
    }

    // Step 2: Sort greedily by ending time
    sort(meet.begin(), meet.end(), comp);

    // Step 3: First meeting always executes because it finishes first
    int count = 1;
    int freeTime = meet[0].end;

    // Vector to store the order of chosen meeting indices (if asked)
    vector<int> meetingOrder;
    meetingOrder.push_back(meet[0].pos);

    // Step 4: Check subsequent meetings
    for (int i = 1; i < n; i++) {
        // Can only attend if start time is STRICTLY greater than free time
        if (meet[i].start > freeTime) {
            count++;
            freeTime = meet[i].end;           // Room is occupied until this meeting ends
            meetingOrder.push_back(meet[i].pos); // Track meeting number
        }
    }

    // Printing meeting order for reference
    cout << "Selected Meeting IDs (1-based): ";
    for (int id : meetingOrder) {
        cout << id << " ";
    }
    cout << "\n";

    return count;
}

// ============================================================================
// DRIVER CODE
// ============================================================================
int main() {
    // Example test case:
    // Meeting 1: [0, 5]
    // Meeting 2: [3, 4]
    // Meeting 3: [1, 2]
    // Meeting 4: [5, 9]
    // Meeting 5: [5, 7]
    // Meeting 6: [8, 9]
    int start[] = {0, 3, 1, 5, 5, 8};
    int end[]   = {5, 4, 2, 9, 7, 9};
    int n = sizeof(start) / sizeof(start[0]);

    int ans = maxMeetings(start, end, n);

    // Expected Output:
    // Selected Meeting IDs: 3 (1-2), 2 (3-4), 5 (5-7), 6 (8-9)
    // Max meetings = 4
    cout << "Maximum meetings possible: " << ans << endl;

    return 0;
}