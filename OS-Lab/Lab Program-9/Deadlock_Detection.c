#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;
    printf(" Deadlock Detection Algorithm \n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m], work[m];
    bool finish[n];

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    // Initialize Finish array
    // If allocation is 0 for all resources, finish is true
    for (i = 0; i < n; i++) {
        bool hasAllocated = false;
        for (j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                hasAllocated = true;
                break;
            }
        }
        finish[i] = !hasAllocated;
    }

    // Detection Logic
    bool progress = true;
    while (progress) {
        progress = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (request[i][j] > work[j])
                        break;

                if (j == m) {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    }

    // Check for deadlocked processes
    bool deadlocked = false;
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            if (!deadlocked) {
                printf("\nSystem is in DEADLOCK. Deadlocked processes: ");
                deadlocked = true;
            }
            printf("P%d ", i);
        }
    }

    if (!deadlocked)
        printf("\nNo Deadlock Detected.");

    printf("\n");
    return 0;
}
