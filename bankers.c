#include <stdio.h>

#define P 5   // Number of processes
#define R 4   // Number of resources

int main() {
    int allocation[P][R], maximum[P][R], need[P][R];
    int available[R];
    int finish[P] = {0};
    int safeSequence[P];

    int i, j, k;
    
    printf("Enter Allocation Matrix (5x4):\n");
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Maximum Matrix (5x4):\n");
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter Available Resources (4 values):\n");
    for(i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need matrix
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for(i = 0; i < P; i++) {
        for(j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int count = 0;
    while(count < P) {
        int found = 0;
        for(i = 0; i < P; i++) {
            if(finish[i] == 0) {
                int flag = 0;
                for(j = 0; j < R; j++) {
                    if(need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0) {
                    for(k = 0; k < R; k++) {
                        available[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT in Safe State!\n");
            return 0;
        }
    }

    printf("\nSystem is in Safe State.\nSafe Sequence:\n");

    char *processNames[] = {
        "Google Drive",
        "Firefox",
        "Word Processor",
        "Excel",
        "PowerPoint"
    };

    for(i = 0; i < P; i++) {
        printf("%s", processNames[safeSequence[i]]);
        if(i != P-1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}