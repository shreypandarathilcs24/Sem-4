#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        printf("Arrival Time: ");
        printf("\nProcess %d\n", i + 1);
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    int current_time = 0;
    float total_tat = 0, total_wt = 0;

    for(int i = 0; i < n; i++) {

        if(current_time < at[i])
            current_time = at[i]; // CPU idle

        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        current_time = ct[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}
