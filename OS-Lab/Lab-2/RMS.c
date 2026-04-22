#include <stdio.h>
#include <math.h>

struct Task {
    int pid, ci, ti;
    int remaining;
};

int main() {
    int n;
    float u = 0, bound;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task t[n];

    for (int i = 0; i < n; i++) {
        t[i].pid = i + 1;

        printf("\nTask %d\n", i + 1);
        printf("Enter Capacity (Ci): ");
        scanf("%d", &t[i].ci);

        printf("Enter Period (Ti): ");
        scanf("%d", &t[i].ti);

        t[i].remaining = t[i].ci;
        u += (float)t[i].ci / t[i].ti;
    }

    bound = n * (pow(2, (float)1/n) - 1);

    printf("\nCPU Utilization = %.4f\n", u);
    printf("Bound = %.4f\n", bound);

    if (u <= bound)
        printf("Schedulable using RMS\n");
    else
        printf("Scheduling not guaranteed\n");

    return 0;
}
