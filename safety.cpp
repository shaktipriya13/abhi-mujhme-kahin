#include <iostream>
#include <vector>
using namespace std;

// Function to implement the Safety Algorithm
bool safetyAlgorithm(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<int> &available) {
    int n = allocation.size();     // Number of processes
    int m = allocation[0].size();  // Number of resources
    vector<int> work = available;  // Work vector, initially the available resources
    vector<bool> finish(n, false); // Finish array to mark processes as finished
    vector<int> safeSequence;      // Safe sequence of processes

    // Safety algorithm
    for (int count = 0; count < n;) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                // Check if the process can be allocated resources
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Allocate resources to process and mark it as finished
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
            // No process could be allocated, system is not in a safe state
            cout << "System is not in a safe state!" << endl;
            return false;
        }
    }

    // If the system is in a safe state, display the safe sequence
    cout << "System is in a safe state!" << endl;
    cout << "Safe Sequence: ";
    for (int i : safeSequence) {
        cout << "P" << i << " ";
    }
    cout << endl;
    return true;
}

int main() {
    int n, m; // Number of processes and resources

    // Get the number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;

    // Allocation matrix
    vector<vector<int>> allocation(n, vector<int>(m));
    cout << "Enter the allocation matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    // Max matrix
    vector<vector<int>> max(n, vector<int>(m));
    cout << "Enter the max matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    // Available resources
    vector<int> available(m);
    cout << "Enter the available resources: ";
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    // Run the safety algorithm
    safetyAlgorithm(allocation, max, available);

    return 0;
}
/*
Enter the number of processes: 5
Enter the number of resource types: 3
Enter the allocation matrix:
Process P0: 0 1 0
Process P1: 2 0 0
Process P2: 3 0 2
Process P3: 2 1 1
Process P4: 0 0 2
Enter the max matrix:
Process P0: 7 5 3
Process P1: 3 2 2
Process P2: 9 0 2
Process P3: 4 2 2
Process P4: 5 3 3
Enter the available resources: 3 3 2


System is in a safe state!
Safe Sequence: P1 P3 P4 P0 P2

*/