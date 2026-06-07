#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int completed = 0, time = 0;

    while(completed < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(at[i] <= time && rt[i] > 0) {

                found = 1;

                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                }
                else {
                    time += rt[i];
                    rt[i] = 0;

                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    completed++;
                }
            }
        }

        if(!found)
            time++;
    }

    float avg_tat = 0, avg_wt = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i],
               ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage WT = %.2f\n", avg_wt / n);

    return 0;
}
