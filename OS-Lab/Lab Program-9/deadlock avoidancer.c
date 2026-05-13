#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;
    printf(" Banker's Algorithm (Avoidance)\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finish[n], safeSeq[n], work[m], count = 0;
    for (i = 0; i < n; i++) finish[i] = 0;
    for (i = 0; i < m; i++) work[i] = avail[i];

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("\nSystem is not in a safe state!");
            return 0;
        }
    }

    printf("\nFollowing is the SAFE Sequence:\n");
    for (i = 0; i < n - 1; i++)
        printf(" P%d ->", safeSeq[i]);
    printf(" P%d\n", safeSeq[n - 1]);

    return 0;
}
