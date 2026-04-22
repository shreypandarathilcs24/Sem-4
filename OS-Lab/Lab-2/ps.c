#include <stdio.h>

struct Process {
    int pid;
    int weight;
};

int main() {
    int n, totalWeight = 0, totalTime;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter total CPU time: ");
    scanf("%d", &totalTime);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);
        printf("Enter Weight: ");
        scanf("%d", &p[i].weight);

        totalWeight += p[i].weight;
    }

    printf("\nProportional Scheduling:\n");

    for (int i = 0; i < n; i++) {
        float share = ((float)p[i].weight / totalWeight) * totalTime;

        printf("Process P%d gets %.2f units of CPU time\n",
               p[i].pid, share);
    }

    return 0;
}
