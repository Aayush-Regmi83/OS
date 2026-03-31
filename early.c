#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period;
    int ct, wt, tat;
} Process;

// Swap
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// Sort by Deadline (EDF)
void sortEDF(Process p[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].deadline > p[j+1].deadline) {
                swap(&p[j], &p[j+1]);
            }
        }
    }
}

// Sort by Period (RMS)
void sortRMS(Process p[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].period > p[j+1].period) {
                swap(&p[j], &p[j+1]);
            }
        }
    }
}

// Calculate CT, WT, TAT
void calculate(Process p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// Utilization
float calculateUtilization(Process p[], int n) {
    float U = 0.0;
    for(int i = 0; i < n; i++) {
        U += (float)p[i].bt / p[i].period;
    }
    return U;
}

// RM Bound
float calculateRMBound(int n) {
    return n * (pow(2, (float)1/n) - 1);
}

// Print EDF
void printEDF(Process p[], int n) {
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

// Print RMS
void printRMS(Process p[], int n) {
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

int main() {
    int n;
    Process p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");
    for(int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }

    float U = calculateUtilization(p, n);

    // EDF
    for(int i = 0; i < n; i++) temp[i] = p[i];
    sortEDF(temp, n);
    calculate(temp, n);

    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("CPU Utilization: %.2f\n", U);
    if(U <= 1.0)
        printf("Schedulable (Utilization <= 1)\n");
    else
        printf("Not Schedulable\n");

    printEDF(temp, n);

    // RMS
    for(int i = 0; i < n; i++) temp[i] = p[i];
    sortRMS(temp, n);
    calculate(temp, n);

    float bound = calculateRMBound(n);

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("CPU Utilization: %.2f\n", U);
    printf("RM Bound: %.4f\n", bound);

    if(U <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("Not Schedulable\n");

    printRMS(temp, n);

    return 0;
}