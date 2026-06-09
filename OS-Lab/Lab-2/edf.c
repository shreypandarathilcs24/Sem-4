#include <stdio.h>

int main() {
    int n, time, earliest;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int c[n], d[n], rt[n];

    for(int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &c[i]);

        printf("Deadline: ");
        scanf("%d", &d[i]);

        rt[i] = c[i];
    }

    printf("\nSchedule:\n|");

    while(1) {

        earliest = -1;

        for(int i = 0; i < n; i++) {
            if(rt[i] > 0) {
                if(earliest == -1 || d[i] < d[earliest])
                    earliest = i;
            }
        }

        if(earliest == -1)
            break;

        printf(" T%d |", earliest + 1);

        rt[earliest]--;
        time++;
    }

    printf("\n");

    return 0;
}
