/* TOPIC: Pattern Printing (Logic Building)
    SOURCE: Striver's A2Z DSA Course

    =========================================
    THE 4 RULES TO SOLVE ANY PATTERN
    =========================================
    1. For the OUTER loop, count the number of lines (Rows).
    2. For the INNER loop, focus on the columns & connect them to the rows.
    3. Print the "*" (or number/char) inside the inner loop.
    4. Observe SYMMETRY (Optional): If a pattern is symmetrical, handle the top and bottom separately.

    KEY VARIABLE NAMES USED BELOW:
    - n: Input size (e.g., number of rows).
    - i: Outer loop variable (Row index).
    - j: Inner loop variable (Column index).
*/

#include <iostream>
#include <algorithm> // For min() function used in Pattern 22
using namespace std;

// =========================================
// TYPE 1: SQUARE & RIGHT-ANGLED TRIANGLES
// =========================================

/* Pattern 1: Rectangular Star
   Logic: Simple nested loop.
   *****
   *****
   *****
*/
void pattern1(int n) {
    // Rule 1: Outer loop runs for 'n' rows.
    for (int i = 0; i < n; i++) {
        // Rule 2: Inner loop runs for 'n' columns.
        for (int j = 0; j < n; j++) {
            cout << "* ";
        }
        // Rule 3: Move to next line after printing columns.
        cout << endl;
    }
}

/* Pattern 2: Right-Angled Triangle
   Logic: Column count equals Row number.
   *
   **
   ***
*/
void pattern2(int n) {
    for (int i = 0; i < n; i++) {
        // Connect Columns to Rows:
        // Row 0 has 1 star, Row 1 has 2 stars...
        // So, J runs from 0 to i.
        for (int j = 0; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

/* Pattern 5: Inverted Right Pyramid
   Logic: As Row increases, Stars decrease.
   *****
   ****
   ***
*/
void pattern5(int n) {
    // Formula: Stars = n - RowIndex
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

// =========================================
// TYPE 2: PYRAMIDS (SPACES + STARS)
// =========================================

/* Pattern 7: Star Pyramid
   Logic: 
   - Print Spaces (n - i - 1)
   - Print Stars  (2 * i + 1)
   - Print Spaces (n - i - 1)
     * *** ***** */
void pattern7(int n) {
    for (int i = 0; i < n; i++) {
        // Step 1: Print Leading Spaces
        // Formula: n - i - 1
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }

        // Step 2: Print Stars
        // Formula: 2 * i + 1 (Odd numbers: 1, 3, 5...)
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << "*";
        }

        // Step 3: Print Trailing Spaces (Optional for visual, but good for logic)
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }
        cout << endl;
    }
}

// =========================================
// TYPE 3: SYMMETRY & BINARY
// =========================================

/* Pattern 10: Half Diamond
   Logic: The stars increase until the middle, then decrease.
   *
   **
   ***
   **
   *
*/
void pattern10(int n) {
    // Outer loop runs 2*n - 1 times
    for (int i = 1; i <= 2 * n - 1; i++) {
        // Logic to flip the pattern halfway
        int stars = i;
        if (i > n) {
            stars = 2 * n - i;
        }

        for (int j = 1; j <= stars; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

/* Pattern 11: Binary Number Triangle
   Logic: Flip 1 and 0.
   1
   0 1
   1 0 1
*/
void pattern11(int n) {
    int start = 1;
    for (int i = 0; i < n; i++) {
        // If row is even, start with 1. If odd, start with 0.
        if (i % 2 == 0) start = 1;
        else start = 0;

        for (int j = 0; j <= i; j++) {
            cout << start << " ";
            // Flip the bit for the next column
            start = 1 - start; 
        }
        cout << endl;
    }
}

// =========================================
// TYPE 4: COMPLEX NUMBER & CHARACTER LOGIC
// =========================================

/* Pattern 12: Number Crown
   Logic: Numbers + Spaces + Numbers
   1      1
   12    21
   123  321
*/
void pattern12(int n) {
    int space = 2 * (n - 1);
    for (int i = 1; i <= n; i++) {
        
        // Part 1: Numbers (1 to i)
        for (int j = 1; j <= i; j++) {
            cout << j;
        }

        // Part 2: Spaces
        for (int j = 1; j <= space; j++) {
            cout << " ";
        }

        // Part 3: Numbers Reverse (i to 1)
        for (int j = i; j >= 1; j--) {
            cout << j;
        }

        cout << endl;
        space -= 2; // Spaces reduce by 2 every row
    }
}

/* Pattern 17: Alpha Hill
   Logic: Characters increase then decrease.
     A
    ABA
   ABCBA
*/
void pattern17(int n) {
    for (int i = 0; i < n; i++) {
        
        // 1. Spaces
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }

        // 2. Characters
        char ch = 'A';
        int breakpoint = (2 * i + 1) / 2; // Middle index
        
        for (int j = 1; j <= 2 * i + 1; j++) {
            cout << ch;
            // If before middle, increment char. If after, decrement.
            if (j <= breakpoint) ch++;
            else ch--;
        }

        // 3. Spaces
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }
        cout << endl;
    }
}

// =========================================
// TYPE 5: BOUNDARY & DISTANCE (The "Boss" Pattern)
// =========================================

/* Pattern 22: The Number Spiral
   Logic: Use distance from the nearest boundary (Top, Bottom, Left, Right).
   4 4 4 4 4 4 4
   4 3 3 3 3 3 4
   4 3 2 2 2 3 4
   4 3 2 1 2 3 4
*/
void pattern22(int n) {
    // The matrix size is (2*n - 1)
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            
            // Calculate distance from all 4 sides
            int top = i;
            int left = j;
            int right = (2 * n - 2) - j;
            int bottom = (2 * n - 2) - i;

            // The value to print is n - (minimum distance to any edge)
            int minDistance = min(min(top, bottom), min(left, right));
            cout << (n - minDistance) << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 4;

    cout << "--- Pattern 7 (Pyramid) ---" << endl;
    pattern7(n);

    cout << "\n--- Pattern 12 (Number Crown) ---" << endl;
    pattern12(n);

    cout << "\n--- Pattern 22 (Number Spiral) ---" << endl;
    pattern22(n);

    return 0;
}