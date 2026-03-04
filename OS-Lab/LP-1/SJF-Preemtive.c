#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, tat, wt;
};

int main() {
    int n, completed = 0, time = 0, min_index;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;  // remaining time
    }

    while(completed != n) {
        int min_rt = 9999;
        min_index = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    min_index = i;
                }
            }
        }

        if(min_index == -1) {
            time++;
        } else {
            p[min_index].rt--;
            time++;

            if(p[min_index].rt == 0) {
                completed++;
                p[min_index].ct = time;
                p[min_index].tat = p[min_index].ct - p[min_index].at;
                p[min_index].wt = p[min_index].tat - p[min_index].bt;
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
