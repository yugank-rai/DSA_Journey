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