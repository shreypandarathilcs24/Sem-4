#include <stdio.h>
#include <stdbool.h>

// Function to check if the current state is safe
bool isSafe(int n, int m, int alloc[n][m], int need[n][m], int avail[m], bool printSeq) {
    int finish[n], safeSeq[n], work[m], count = 0;
    
    for (int i = 0; i < n; i++) finish[i] = 0;
    for (int i = 0; i < m; i++) work[i] = avail[i];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            return false;
        }
    }

    if (printSeq) {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n - 1; i++) printf("P%d -> ", safeSeq[i]);
        printf("P%d\n", safeSeq[n - 1]);
    }
    return true;
}

int main() {
    int n, m, i, j;

    printf("--- Banker's Algorithm: Resource Request & Avoidance ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Initial Safety Check
    if (!isSafe(n, m, alloc, need, avail, true)) {
        printf("\nInitial state is UNSAFE! Deadlock is possible.\n");
        return 0;
    }

    // Resource Request Section
    int p_idx;
    int request[m];
    printf("\n--- New Resource Request ---");
    printf("\nEnter process ID making request (0 to %d): ", n - 1);
    scanf("%d", &p_idx);
    printf("Enter request amounts for %d resources: ", m);
    for (i = 0; i < m; i++) scanf("%d", &request[i]);

    // Step 1 & 2: Check against Need and Availability
    bool possible = true;
    for (i = 0; i < m; i++) {
        if (request[i] > need[p_idx][i]) {
            printf("Error: Process P%d exceeded its maximum claim.\n", p_idx);
            possible = false;
            break;
        }
        if (request[i] > avail[i]) {
            printf("Resources not available. P%d must wait.\n", p_idx);
            possible = false;
            break;
        }
    }

    if (possible) {
        // Step 3: Pretend to allocate
        for (i = 0; i < m; i++) {
            avail[i] -= request[i];
            alloc[p_idx][i] += request[i];
            need[p_idx][i] -= request[i];
        }

        // Step 4: Verify Safety
        if (isSafe(n, m, alloc, need, avail, true)) {
            printf("RESULT: Request GRANTED.\n");
        } else {
            printf("RESULT: Request DENIED (Unsafe State). Rolling back...\n");
            // Rollback changes
            for (i = 0; i < m; i++) {
                avail[i] += request[i];
                alloc[p_idx][i] -= request[i];
                need[p_idx][i] += request[i];
            }
        }
    }

    return 0;
}
