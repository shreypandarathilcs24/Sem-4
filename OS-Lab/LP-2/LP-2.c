 #include <stdio.h>

int main() {
    int n,i,time=0,highest;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n],bt[n],pr[n],ct[n],tat[n],wt[n],done[n];

    for(i=0;i<n;i++){
        printf("\nProcess P%d\n",i+1);
        printf("Arrival Time: ");
        scanf("%d",&at[i]);
        printf("Burst Time: ");
        scanf("%d",&bt[i]);
        printf("Priority: ");
        scanf("%d",&pr[i]);
        done[i]=0;
    }

    int completed=0;

    printf("\nGantt Chart:\n|");

    while(completed<n){
        highest=-1;

        for(i=0;i<n;i++){
            if(at[i]<=time && done[i]==0){
                if(highest==-1 || pr[i]<pr[highest])
                    highest=i;
            }
        }

        if(highest==-1){
            time++;
        }
        else{
            printf(" P%d |",highest+1);

            time += bt[highest];

            ct[highest]=time;
            tat[highest]=ct[highest]-at[highest];
            wt[highest]=tat[highest]-bt[highest];

            done[highest]=1;
            completed++;
        }
    }

    printf("\n\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }

    return 0;
}
