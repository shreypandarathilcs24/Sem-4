#include <stdio.h>

int main() {
    int n, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    while(completed < n) {
        int s = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                if(s == -1 || rt[i] < rt[s])
                    s = i;
            }
        }

        if(s == -1) {
            time++;
        }
        else {
            rt[s]--;      // execute for 1 unit
            time++;

            if(rt[s] == 0) {
                completed++;

                ct[s] = time;
                tat[s] = ct[s] - at[s];
                wt[s] = tat[s] - bt[s];
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}
