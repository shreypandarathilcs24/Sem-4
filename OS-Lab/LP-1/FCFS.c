#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];

    // Input
    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort according to Arrival Time
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {

            if(at[i] > at[j]) {

                int temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    int current_time = 0;
    float total_tat = 0, total_wt = 0;

    // FCFS Scheduling
    for(int i = 0; i < n; i++) {

        if(current_time < at[i])
            current_time = at[i];

        ct[i] = current_time + bt[i];

        tat[i] = ct[i] - at[i];

        wt[i] = tat[i] - bt[i];

        current_time = ct[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f",
           total_tat / n);

    printf("\nAverage Waiting Time = %.2f\n",
           total_wt / n);

    return 0;
}
