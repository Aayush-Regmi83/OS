#include <stdio.h>

void Priority_NonPreemptive(int id[], int at[], int bt[], int pr[], int n)
{
    int ct[n], tat[n], wt[n], start[n];
    int time=0, completed=0;
    float sumTAT=0, sumWT=0, sumRT=0;

    int ganttP[50], ganttT[50], g=0;

    for(int i=0;i<n;i++)
        ct[i]=tat[i]=wt[i]=start[i]=-1;

    printf("\n--- Non-Preemptive Priority Scheduling ---");

    while(completed < n)
    {
        int idx=-1, highest=1e9;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && ct[i]==-1 && pr[i] < highest)
            {
                highest = pr[i];
                idx = i;
            }
        }

        if(idx==-1)
        {
            time++;
        }
        else
        {
            start[idx] = time;

            ganttP[g] = id[idx];
            ganttT[g] = time;
            g++;

            time += bt[idx];

            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            int response = start[idx] - at[idx];

            sumTAT += tat[idx];
            sumWT += wt[idx];
            sumRT += response;

            completed++;
        }
    }

    ganttT[g] = time;

    printf("\nGantt Chart:\n|");
    for(int i=0;i<g;i++)
        printf(" P%d |", ganttP[i]);

    printf("\n%d", ganttT[0]);
    for(int i=1;i<=g;i++)
        printf("   %d", ganttT[i]);

    printf("\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT");

    for(int i=0;i<n;i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
        id[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i],start[i]-at[i]);
    }

    printf("\n\nAverage TAT: %.2f",sumTAT/n);
    printf("\nAverage WT: %.2f",sumWT/n);
    printf("\nAverage RT: %.2f\n",sumRT/n);
}



void Priority_Preemptive(int id[], int at[], int bt[], int pr[], int n)
{
    int rt[n], ct[n], tat[n], wt[n], start[n];
    int time=0, completed=0;
    float sumTAT=0, sumWT=0, sumRT=0;

    int ganttP[200], ganttT[200], g=0;

    for(int i=0;i<n;i++)
    {
        rt[i]=bt[i];
        ct[i]=tat[i]=wt[i]=-1;
        start[i]=-1;
    }

    printf("\n--- Preemptive Priority Scheduling ---");

    while(completed < n)
    {
        int idx=-1, highest=1e9;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0 && pr[i] < highest)
            {
                highest = pr[i];
                idx = i;
            }
        }

        if(idx==-1)
        {
            time++;
        }
        else
        {
            if(start[idx] == -1)
                start[idx] = time;

            ganttP[g] = id[idx];
            ganttT[g] = time;
            g++;

            rt[idx]--;
            time++;

            if(rt[idx]==0)
            {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                int response = start[idx] - at[idx];

                sumTAT += tat[idx];
                sumWT += wt[idx];
                sumRT += response;

                completed++;
            }
        }
    }

    ganttT[g] = time;

    printf("\nGantt Chart:\n|");
    for(int i=0;i<g;i++)
        printf(" P%d |", ganttP[i]);

    printf("\n%d", ganttT[0]);
    for(int i=1;i<=g;i++)
        printf("   %d", ganttT[i]);

    printf("\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT");

    for(int i=0;i<n;i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
        id[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i],start[i]-at[i]);
    }

    printf("\n\nAverage TAT: %.2f",sumTAT/n);
    printf("\nAverage WT: %.2f",sumWT/n);
    printf("\nAverage RT: %.2f\n",sumRT/n);
}



int main()
{
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int id[n], at[n], bt[n], pr[n];

    for(int i=0;i<n;i++)
    {
        id[i]=i+1;

        printf("\nArrival Time for P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time for P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Priority for P%d (lower number = higher priority): ",i+1);
        scanf("%d",&pr[i]);
    }

    printf("\n\nCPU Scheduling Menu");
    printf("\n1. Priority Scheduling (Non-Preemptive)");
    printf("\n2. Priority Scheduling (Preemptive)");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            Priority_NonPreemptive(id,at,bt,pr,n);
            break;

        case 2:
            Priority_Preemptive(id,at,bt,pr,n);
            break;

        default:
            printf("\nInvalid Choice!");
    }

    return 0;
}
