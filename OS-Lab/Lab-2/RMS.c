#include <stdio.h>

int main() {
    int n, i, j, time, hyper = 1;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int ci[n], ti[n], rt[n];

    for(i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);

        printf("Enter Capacity (Ci): ");
        scanf("%d", &ci[i]);

        printf("Enter Period (Ti): ");
        scanf("%d", &ti[i]);

        rt[i] = ci[i];
    }

    /* Hyperperiod (simple product of periods) */
    for(i = 0; i < n; i++)
        hyper *= ti[i];

    printf("\nGantt Chart:\n|");

    for(time = 0; time < hyper; time++) {

        /* Release tasks at beginning of each period */
        for(i = 0; i < n; i++) {
            if(time % ti[i] == 0)
                rt[i] = ci[i];
        }

        int highest = -1;

        /* RMS: smallest period = highest priority */
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                if(highest == -1 || ti[i] < ti[highest])
                    highest = i;
            }
        }

        if(highest == -1) {
            printf(" Idle |");
        }
        else {
            printf(" T%d |", highest + 1);
            rt[highest]--;
        }
    }

    printf("\n");

    return 0;
}
