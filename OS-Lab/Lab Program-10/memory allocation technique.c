#include <stdio.h>

#define MAX 20

// ---------- FIRST FIT ----------
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    int used[MAX] = {0};

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            // Allocate only if block is unused
            if(!used[j] && blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                used[j] = 1; // Mark block as used
                break;
            }
        }
    }

    printf("\n========== FIRST FIT ==========\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}


// ---------- BEST FIT ----------
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    int used[MAX] = {0};

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int bestIdx = -1;

        for(int j = 0; j < m; j++)
        {
            if(!used[j] && blockSize[j] >= processSize[i])
            {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }

        if(bestIdx != -1)
        {
            allocation[i] = bestIdx;
            used[bestIdx] = 1;
        }
    }

    printf("\n========== BEST FIT ==========\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}


// ---------- WORST FIT ----------
void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    int used[MAX] = {0};

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int worstIdx = -1;

        for(int j = 0; j < m; j++)
        {
            if(!used[j] && blockSize[j] >= processSize[i])
            {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                {
                    worstIdx = j;
                }
            }
        }

        if(worstIdx != -1)
        {
            allocation[i] = worstIdx;
            used[worstIdx] = 1;
        }
    }

    printf("\n========== WORST FIT ==========\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}


// ---------- MAIN FUNCTION ----------
int main()
{
    int m, n;

    int blockSize[MAX];
    int processSize[MAX];

    // Input number of memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    // Input memory block sizes
    printf("Enter sizes of memory blocks:\n");
    for(int i = 0; i < m; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input number of processes
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // Input process sizes
    printf("Enter sizes of processes:\n");
    for(int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Separate copies for each technique
    int firstBlocks[MAX], bestBlocks[MAX], worstBlocks[MAX];

    for(int i = 0; i < m; i++)
    {
        firstBlocks[i] = blockSize[i];
        bestBlocks[i] = blockSize[i];
        worstBlocks[i] = blockSize[i];
    }

    // Function calls
    firstFit(firstBlocks, m, processSize, n);

    bestFit(bestBlocks, m, processSize, n);

    worstFit(worstBlocks, m, processSize, n);

    return 0;
}
