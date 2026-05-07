#include <stdio.h>

#define MAX 10

int n, adj[MAX][MAX], inDegree[MAX];

void topoSort() {
    int queue[MAX], front = 0, rear = 0, count = 0;

    for (int i = 0; i < n; i++)
        if (inDegree[i] == 0)
            queue[rear++] = i;

    printf("Topological Order: ");
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v + 1);
        count++;
        for (int i = 0; i < n; i++)
            if (adj[v][i] && --inDegree[i] == 0)
                queue[rear++] = i;
    }

    if (count != n)
        printf("\nCycle detected! Topological sort not possible.");
    printf("\n");
}

int main() {
    int edges, u, v;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &edges);

    for (int i = 0; i < edges; i++) {
        printf("Edge %d (u v): ", i + 1);
        scanf("%d %d", &u, &v);
        adj[u-1][v-1] = 1;
        inDegree[v-1]++;
    }

    topoSort();
    return 0;
}
