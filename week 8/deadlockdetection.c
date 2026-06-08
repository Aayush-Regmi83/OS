#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], request[MAX][MAX];
    int available[MAX];

    int work[MAX];
    int finish[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }


    for(int i = 0; i < m; i++)
        work[i] = available[i];

    for(int i = 0; i < n; i++) {
        int flag = 0;
        for(int j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                flag = 1;
                break;
            }
        }
        finish[i] = (flag == 0) ? 1 : 0;
    }


    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j])
                        break;
                }

                if(j == m) {

                    for(int x = 0; x < m; x++)
                        work[x] += alloc[i][x];

                    finish[i] = 1;
                }
            }
        }
    }

    int deadlock = 0;

printf("\nSystem Deadlock Analysis:\n");

for(int i = 0; i < n; i++) {
    if(!finish[i]) {
        if(deadlock == 0) {
            printf("Deadlock detected!\n");
            printf("Processes causing deadlock: ");
        }
        printf("P%d ", i);
        deadlock = 1;
    }
}

if(!deadlock) {
    printf("No deadlock detected. All processes can finish.\n");
} else {
    printf("\nThese processes are stuck and waiting for each other.\n");

}
}

