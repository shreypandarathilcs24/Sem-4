#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];
    int type[n], done[n];

    for(int i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Type (0=System, 1=User): ");
        scanf("%d", &type[i]);

        done[i] = 0;
    }

    int time = 0, completed = 0;

    while(completed < n) {

        int idx = -1;

        // Check System processes first
        for(int i = 0; i < n; i++) {
            if(at[i] <= time && done[i] == 0 && type[i] == 0) {
                idx = i;
                break;
            }
        }

        // If no System process, check User process
        if(idx == -1) {
            for(int i = 0; i < n; i++) {
                if(at[i] <= time && done[i] == 0 && type[i] == 1) {
                    idx = i;
                    break;
                }
            }
        }

        // No process has arrived yet
        if(idx == -1) {
            time++;
            continue;
        }

        // Execute process
        time += bt[idx];

        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        done[idx] = 1;
        completed++;
    }

    float avg_tat = 0, avg_wt = 0;

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%s\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               (type[i] == 0) ? "SYS" : "USR",
               ct[i],
               tat[i],
               wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage WT = %.2f\n", avg_wt / n);

    return 0;
}
