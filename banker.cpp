#include <iostream>
#include <vector>
using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<int> &available) {
    int n = allocation.size();     // Number of processes
    int m = allocation[0].size();  // Number of resources
    vector<int> work = available;  // Copy of available resources
    vector<bool> finish(n, false); // Tracks if a process has finished
    vector<int> safeSequence;      // Stores the safe sequence

    // Safety algorithm
    for (int count = 0; count < n;) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state!" << endl;
            return false;
        }
    }

    // Display the safe sequence
    cout << "System is in a safe state!" << endl;
    cout << "Safe Sequence: ";
    for (int i : safeSequence) {
        cout << "P" << i << " ";
    }
    cout << endl;
    return true;
}

int main() {
    // Number of processes and resources
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter allocation matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter max matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter available resources:" << endl;
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    isSafe(allocation, max, available);

    return 0;
}

/*
Sample Input:
Enter number of processes: 3
Enter number of resources: 3

Enter allocation matrix:
0 1 0
2 0 0
3 0 3

Enter max matrix:
7 5 3
3 2 2
9 0 2

Enter available resources:
3 3 2

Expected Output:
System is in a safe state!
Safe Sequence: P1 P2 P0
*/

/*
Explanation:
For P1:
  Need = Max - Allocation = (3-2, 2-0, 2-0) = (1, 2, 2)
  Available = (3, 3, 2) >= (1, 2, 2) → Can allocate.
  Work = Available + Allocation = (3, 3, 2) + (2, 0, 0) = (5, 3, 2)

For P2:
  Need = Max - Allocation = (9-3, 0-0, 2-3) = (6, 0, -1)
  Available = (5, 3, 2) >= (6, 0, 0) → Can allocate.
  Work = (5, 3, 2) + (3, 0, 3) = (8, 3, 5)

For P0:
  Need = Max - Allocation = (7-0, 5-1, 3-0) = (7, 4, 3)
  Available = (8, 3, 5) >= (7, 4, 3) → Can allocate.
  Work = (8, 3, 5) + (0, 1, 0) = (8, 4, 5)
*/
