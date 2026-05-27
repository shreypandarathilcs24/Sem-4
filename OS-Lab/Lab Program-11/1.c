#include <stdio.h>

#define MAX 50

void print(int f[], int n) {
    for(int i=0;i<n;i++)
        (f[i]==-1)? printf("- ") : printf("%d ", f[i]);
    printf("\n");
}

int search(int f[], int n, int key) {
    for(int i=0;i<n;i++)
        if(f[i]==key) return i;
    return -1;
}

// FIFO
void FIFO(int p[], int n, int fno) {
    int f[MAX], faults=0, idx=0;

    for(int i=0;i<fno;i++) f[i]=-1;

    printf("\nFIFO:\n");

    for(int i=0;i<n;i++) {
        if(search(f,fno,p[i])==-1) {
            f[idx]=p[i];
            idx=(idx+1)%fno;
            faults++;

            printf("PF %d: ",faults);
            print(f,fno);
        }
    }
    printf("Total FIFO Faults = %d\n",faults);
}

// LRU
void LRU(int p[], int n, int fno) {
    int f[MAX], time[MAX], faults=0, cnt=0;

    for(int i=0;i<fno;i++) {
        f[i]=-1;
        time[i]=0;
    }

    printf("\nLRU:\n");

    for(int i=0;i<n;i++) {
        int pos=search(f,fno,p[i]);

        if(pos!=-1) {
            time[pos]=++cnt;
        }
        else {
            int lru=0;

            // find empty frame first
            for(int j=0;j<fno;j++) {
                if(f[j]==-1) {
                    lru=j;
                    goto replace;
                }
            }

            // find least recently used
            for(int j=1;j<fno;j++)
                if(time[j]<time[lru]) lru=j;

replace:
            f[lru]=p[i];
            time[lru]=++cnt;
            faults++;

            printf("PF %d: ",faults);
            print(f,fno);
        }
    }
    printf("Total LRU Faults = %d\n",faults);
}

// OPTIMAL helper
int predict(int p[], int f[], int n, int idx, int fno) {
    int far=-1, pos=0;

    for(int i=0;i<fno;i++) {
        int j;
        for(j=idx;j<n;j++) {
            if(f[i]==p[j]) {
                if(j>far) {
                    far=j;
                    pos=i;
                }
                break;
            }
        }
        if(j==n) return i;
    }
    return pos;
}

// OPTIMAL
void OPT(int p[], int n, int fno) {
    int f[MAX], faults=0;

    for(int i=0;i<fno;i++) f[i]=-1;

    printf("\nOPTIMAL:\n");

    for(int i=0;i<n;i++) {

        if(search(f,fno,p[i])==-1) {

            int pos=-1;

            for(int j=0;j<fno;j++)
                if(f[j]==-1) {
                    pos=j;
                    break;
                }

            if(pos==-1)
                pos=predict(p,f,n,i+1,fno);

            f[pos]=p[i];
            faults++;

            printf("PF %d: ",faults);
            print(f,fno);
        }
    }
    printf("Total OPT Faults = %d\n",faults);
}

int main() {
    int n,fno,p[MAX];

    printf("Frames: ");
    scanf("%d",&fno);

    printf("Length of reference string: ");
    scanf("%d",&n);

    printf("Enter reference string: ");
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    FIFO(p,n,fno);
    LRU(p,n,fno);
    OPT(p,n,fno);

    return 0;
}
