/*
 * ============================================================================
 * GREEDY ALGORITHM: Fractional Knapsack
 * ============================================================================
 * 
 * Problem Statement:
 * You are given 'N' items, each with a 'value' and a 'weight'.
 * You have a knapsack (bag) with a maximum capacity 'W'.
 * Goal: Maximize the total value in the knapsack.
 * Twist: Unlike 0/1 Knapsack, you CAN break items and take a fraction 
 * of an item if the whole item doesn't fit.
 * 
 * THE GREEDY APPROACH:
 * 1. Calculate the 'value per unit weight' (value/weight) for each item.
 * 2. Sort the items based on this ratio in DESCENDING order.
 * 3. Iterate through the sorted items:
 *    - If the knapsack can hold the entire item, take it all.
 *    - If it can't hold the entire item, take the fraction that fits 
 *      and break the loop (the knapsack is now full).
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// 1. DATA STRUCTURE DEFINITION
// ============================================================================
// A struct to represent each item
struct Item {
    int value;
    int weight;
};

// ============================================================================
// 2. CUSTOM COMPARATOR FOR SORTING
// ============================================================================
/*
 * We need to sort the items in descending order of their (value / weight) ratio.
 * 
 * Warning: Because division can yield decimal numbers (e.g., 5.5 vs 5.2),
 * we MUST cast the values to 'double' before dividing to avoid integer 
 * division truncation (which would treat 5.5 and 5.2 both as 5).
 */
bool comp(Item a, Item b) {
    double r1 = (double) a.value / (double) a.weight;
    double r2 = (double) b.value / (double) b.weight;
    
    // Return true if the first item's ratio is greater (for descending order)
    return r1 > r2; 
}

// ============================================================================
// 3. MAIN ALGORITHM FUNCTION
// ============================================================================
/*
 * Time Complexity: O(N log N) + O(N) 
 *   - O(N log N) to sort the items array.
 *   - O(N) to iterate through the array to fill the knapsack.
 * 
 * Space Complexity: O(1)
 *   - No extra data structures are used, sorting is done in-place.
 */
double fractionalKnapsack(int W, Item arr[], int n) {
    // Step 1: Sort items by value/weight ratio descending
    sort(arr, arr + n, comp);
    
    // Variables to track current weight in bag and total value accumulated
    int currentWeight = 0;
    double finalValue = 0.0; // The result can be fractional
    
    // Step 2: Iterate through the sorted items
    for (int i = 0; i < n; i++) {
        
        // Case A: The whole item can fit into the remaining knapsack capacity
        if (currentWeight + arr[i].weight <= W) {
            currentWeight += arr[i].weight;
            finalValue += arr[i].value;
        } 
        
        // Case B: The whole item CANNOT fit. 
        // Take a fraction of it to exactly fill the remaining capacity.
        else {
            // Calculate how much weight capacity is left
            int remain = W - currentWeight;
            
            // Calculate value of the remaining fraction
            // (Total Value / Total Weight) * Remaining Weight Capacity
            finalValue += ((double) arr[i].value / (double) arr[i].weight) * (double) remain;
            
            // Once we take a fraction, the knapsack is entirely full.
            break; 
        }
    }
    
    return finalValue;
}

// ============================================================================
// DRIVER CODE
// ============================================================================
int main() {
    int n = 3;  // Number of items
    int W = 50; // Knapsack capacity
    
    // Array of Items {value, weight}
    Item arr[] = {{100, 20}, {60, 10}, {120, 30}};
    
    // Call the function
    double maxValue = fractionalKnapsack(W, arr, n);
    
    // Output: Expected to be 240.00
    // (Takes 60 value item entirely, 100 value item entirely, and 2/3 of 120 value item)
    cout << "Maximum value in Knapsack = " << fixed << setprecision(2) << maxValue << endl;
    
    return 0;
}
//================================================================================

/*
 * ============================================================================
 * GREEDY ALGORITHM: Shortest Job First (SJF) CPU Scheduling
 * ============================================================================
 * 
 * Problem Statement:
 * You are given 'n' processes where each process has a known execution time 
 * (burst time). Assume all processes arrive at time t = 0.
 * 
 * Goal:
 * Compute the average waiting time for all processes when scheduled using 
 * the non-preemptive Shortest Job First (SJF) algorithm.
 * (Return the integer floor/truncated value of the average).
 * 
 * Core Concept of SJF:
 * - A scheduling policy that always selects the waiting process with the 
 *   SMALLEST execution/burst time to execute next.
 * - Why Greedy? Executing shorter tasks earlier ensures subsequent waiting 
 *   times for other processes remain as small as possible, minimizing 
 *   the overall total waiting time.
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// SJF AVERAGE WAITING TIME FUNCTION
// ============================================================================
/*
 * Time Complexity: O(N log N) + O(N) 
 *   - O(N log N) to sort the burst times in non-decreasing order.
 *   - O(N) for a single linear pass to compute waiting times.
 * 
 * Space Complexity: O(1)
 *   - In-place sorting and scalar variables used (no extra memory).
 */
long long solve(vector<int>& bt) {
    int n = bt.size();
    
    // Step 1: Greedily pick shortest jobs first -> Sort in ascending order
    sort(bt.begin(), bt.end());
    
    // 't' keeps track of the current time on the CPU clock
    long long t = 0; 
    
    // 'totalWaitingTime' accumulates the waiting time experienced by all processes
    long long totalWaitingTime = 0;
    
    // Step 2: Iterate through all processes in sorted order
    for (int i = 0; i < n; i++) {
        // Since the current process arrives at t = 0, its waiting time 
        // is simply the current clock time 't' when CPU starts executing it.
        totalWaitingTime += t;
        
        // Advance CPU clock by the burst time of the current running process
        t += bt[i];
    }
    
    // Step 3: Return the average waiting time (integer division drops decimal part)
    return totalWaitingTime / n;
}

// ============================================================================
// DRIVER CODE
// ============================================================================
int main() {
    // Process burst times: P1: 4, P2: 3, P3: 7, P4: 1, P5: 2
    // All arriving at time t = 0
    vector<int> burstTimes = {4, 3, 7, 1, 2};
    
    /*
     * Trace:
     * Sorted Order: [1, 2, 3, 4, 7]
     * 
     * Process 1 (bt = 1): Starts at t=0  -> Waiting time = 0  -> CPU free at t=1
     * Process 2 (bt = 2): Starts at t=1  -> Waiting time = 1  -> CPU free at t=3
     * Process 3 (bt = 3): Starts at t=3  -> Waiting time = 3  -> CPU free at t=6
     * Process 4 (bt = 4): Starts at t=6  -> Waiting time = 6  -> CPU free at t=10
     * Process 5 (bt = 7): Starts at t=10 -> Waiting time = 10 -> CPU free at t=17
     * 
     * Total Waiting Time = 0 + 1 + 3 + 6 + 10 = 20
     * Average Waiting Time = 20 / 5 = 4
     */
    
    long long avgWaitingTime = solve(burstTimes);
    cout << "Average Waiting Time: " << avgWaitingTime << endl; // Output: 4
    
    return 0;
}

//===================================================================================
/*
 * ============================================================================
 * GREEDY ALGORITHM: Job Sequencing Problem
 * ============================================================================
 * 
 * Problem Statement:
 * Given a set of 'n' jobs where every job has:
 *   - Job ID
 *   - Deadline (the latest day/unit of time the job must be finished by)
 *   - Profit (earned if finished on or before the deadline)
 * Each job takes 1 unit of time (1 day). Only 1 job can be executed per day.
 * 
 * Goal:
 * Maximize the total profit and return:
 *   { Count of jobs done, Maximum profit earned }
 * 
 * ----------------------------------------------------------------------------
 * THE GREEDY STRATEGY:
 * 1. Profit Priority:
 *    Always try to perform the job that gives the HIGHEST profit first.
 *    -> Sort jobs in DESCENDING order of profit.
 * 
 * 2. Delay Execution (Key Insight):
 *    If a job has a deadline 'D', try to execute it as LATE as possible 
 *    (ideally on day 'D'). 
 *    Why? Because performing a job on Day 1 when its deadline is Day 4 
 *    unnecessarily blocks Day 1 for another job whose deadline might be Day 1!
 *    Delaying leaves earlier slots open for tighter-deadline jobs.
 * 
 * 3. Schedule Backward:
 *    For each job, check days from 'deadline' down to 1. 
 *    Place it in the first free day found.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Representation of a Job
struct Job {
    int id;       // Job Id
    int dead;     // Deadline of job
    int profit;   // Profit if job is done before or on deadline
};

// ============================================================================
// CUSTOM COMPARATOR
// ============================================================================
/*
 * Sorts jobs in descending order of profit.
 * If job A has a higher profit than job B, A should come first.
 */
bool comparison(Job a, Job b) {
    return (a.profit > b.profit);
}

// ============================================================================
// MAIN FUNCTION: JobScheduling
// ============================================================================
/*
 * Time Complexity:
 *   - O(N log N) to sort jobs by profit.
 *   - O(N) to find the maximum deadline.
 *   - O(N * maxDeadline) in the worst case for searching free slots.
 *   Total Time Complexity: O(N log N + N * maxDeadline)
 * 
 * Space Complexity:
 *   - O(maxDeadline) to store the hash/slot array tracking occupied days.
 * 
 * Note on Further Optimization:
 * The inner search for a free slot from 'deadline' down to 1 can be optimized 
 * from O(maxDeadline) down to O(1) using Disjoint Set Union (DSU / Find-Union).
 */
pair<int, int> JobScheduling(Job arr[], int n) {
    // Step 1: Greedily sort all jobs in descending order of profit
    sort(arr, arr + n, comparison);

    // Step 2: Find the maximum deadline across all jobs to size our schedule array
    int maxi = arr[0].dead;
    for (int i = 1; i < n; i++) {
        maxi = max(maxi, arr[i].dead);
    }

    // Step 3: Create a slot/hash array of size (maxi + 1)
    // 1-based indexing for days: slot[d] stores the job ID performed on day 'd'
    // Initialize all slots to -1 indicating that every day is currently free
    vector<int> slot(maxi + 1, -1);

    int countJobs = 0;
    int jobProfit = 0;

    // Step 4: Iterate through all sorted jobs
    for (int i = 0; i < n; i++) {
        // Greedily search backward from the job's deadline to day 1
        for (int j = arr[i].dead; j > 0; j--) {
            // Found a free slot on day 'j'
            if (slot[j] == -1) {
                slot[j] = arr[i].id; // Assign day 'j' to this job
                countJobs++;
                jobProfit += arr[i].profit;
                break; // Job scheduled; move to next job
            }
        }
    }

    return {countJobs, jobProfit};
}

// ============================================================================
// DRIVER CODE
// ============================================================================
int main() {
    int n = 8;
    // Example test case: {id, deadline, profit}
    Job arr[] = {
        {1, 4, 20},
        {2, 5, 60},
        {3, 6, 70},
        {4, 6, 65},
        {5, 4, 25},
        {6, 2, 80},
        {7, 2, 10},
        {8, 2, 22}
    };

    pair<int, int> ans = JobScheduling(arr, n);

    cout << "Total Jobs Done: " << ans.first << endl;
    cout << "Max Profit Earned: " << ans.second << endl;

    return 0;
}