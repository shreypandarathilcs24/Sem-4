#include <stdio.h>

struct Process {
    int pid;
    int ci;   // execution time
    int di;   // deadline
};

int main() {
    int n;
    float u = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Enter Execution Time (Ci): ");
        scanf("%d", &p[i].ci);

        printf("Enter Deadline (Di): ");
        scanf("%d", &p[i].di);

        u += (float)p[i].ci / p[i].di;
    }

    printf("\nCPU Utilization = %.4f\n", u);

    if (u <= 1)
        printf("Schedulable using EDF\n");
    else
        printf("Not Guaranteed\n");

    return 0;
}
