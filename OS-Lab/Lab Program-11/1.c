#include <stdio.h>

#define MAX 50

int found(int f[], int n, int page)
{
    for(int i=0;i<n;i++)
        if(f[i]==page)
            return i;
    return -1;
}

// FIFO
void FIFO(int p[], int n, int frames)
{
    int f[MAX], faults=0, pos=0;

    for(int i=0;i<frames;i++)
        f[i]=-1;

    for(int i=0;i<n;i++)
    {
        if(found(f,frames,p[i])==-1)
        {
            f[pos]=p[i];
            pos=(pos+1)%frames;
            faults++;
        }
    }

    printf("FIFO Faults = %d\n", faults);
}

// LRU
void LRU(int p[], int n, int frames)
{
    int f[MAX], time[MAX];
    int faults=0, cnt=0;

    for(int i=0;i<frames;i++)
    {
        f[i]=-1;
        time[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        int idx=found(f,frames,p[i]);

        if(idx!=-1)
        {
            time[idx]=++cnt;
        }
        else
        {
            int pos=0;

            for(int j=0;j<frames;j++)
            {
                if(f[j]==-1)
                {
                    pos=j;
                    break;
                }

                if(time[j]<time[pos])
                    pos=j;
            }

            f[pos]=p[i];
            time[pos]=++cnt;
            faults++;
        }
    }

    printf("LRU Faults = %d\n", faults);
}

// Optimal helper
int predict(int p[], int f[], int n, int start, int frames)
{
    int pos=0, farthest=-1;

    for(int i=0;i<frames;i++)
    {
        int j;

        for(j=start;j<n;j++)
        {
            if(f[i]==p[j])
            {
                if(j>farthest)
                {
                    farthest=j;
                    pos=i;
                }
                break;
            }
        }

        if(j==n)
            return i;
    }

    return pos;
}

// OPTIMAL
void OPT(int p[], int n, int frames)
{
    int f[MAX], faults=0;

    for(int i=0;i<frames;i++)
        f[i]=-1;

    for(int i=0;i<n;i++)
    {
        if(found(f,frames,p[i])==-1)
        {
            int pos=-1;

            for(int j=0;j<frames;j++)
            {
                if(f[j]==-1)
                {
                    pos=j;
                    break;
                }
            }

            if(pos==-1)
                pos=predict(p,f,n,i+1,frames);

            f[pos]=p[i];
            faults++;
        }
    }

    printf("OPT Faults = %d\n", faults);
}

int main()
{
    int n, frames, p[MAX];

    printf("Enter number of frames: ");
    scanf("%d",&frames);

    printf("Enter length of reference string: ");
    scanf("%d",&n);

    printf("Enter reference string: ");
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    FIFO(p,n,frames);
    LRU(p,n,frames);
    OPT(p,n,frames);

    return 0;
}
