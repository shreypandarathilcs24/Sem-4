#include <stdio.h>

#define MAX 10

int a[MAX], dir[MAX], n;

void print() {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// Find the largest mobile element
int mobile() {
    int mob = -1, pos = -1;
    for (int i = 0; i < n; i++) {
        int j = i + dir[i]; // neighbor in direction
        if (j >= 0 && j < n && a[i] > a[j] && a[i] > mob) {
            mob = a[i];
            pos = i;
        }
    }
    return pos;
}

void johnsonTrotter() {
    print();
    int pos;
    while ((pos = mobile()) != -1) {
        int next = pos + dir[pos];

        // Swap mobile element with neighbor
        int tmp = a[pos]; a[pos] = a[next]; a[next] = tmp;
        tmp = dir[pos]; dir[pos] = dir[next]; dir[next] = tmp;

        // Reverse direction of all elements larger than mobile
        for (int i = 0; i < n; i++)
            if (a[i] > a[next])
                dir[i] = -dir[i];

        print();
    }
}

int main() {
    printf("Enter n: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        dir[i] = -1; // all start moving left
    }

    johnsonTrotter();
    return 0;
}
