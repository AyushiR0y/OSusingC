#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMORY_SIZE 100

struct Customer {
    char name[50];
    int accountNumber;
    float balance;
};

struct MemoryBlock {
    struct Customer customer;
    int isAllocated;
};

struct MemoryBlock memory[MAX_MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        memory[i].isAllocated = 0;
    }
}

int firstFit(int size) {
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        if (!memory[i].isAllocated && sizeof(struct MemoryBlock) >= size) {
            memory[i].isAllocated = 1;
            return i;
        }
    }
    return -1;
}

int bestFit(int size) {
    int bestFitIndex = -1;
    int bestFitSize = MAX_MEMORY_SIZE + 1;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        if (!memory[i].isAllocated && sizeof(struct MemoryBlock) >= size) {
            if (sizeof(struct MemoryBlock) < bestFitSize) {
                bestFitIndex = i;
                bestFitSize = sizeof(struct MemoryBlock);
            }
        }
    }
    if (bestFitIndex != -1) {
        memory[bestFitIndex].isAllocated = 1;
    }
    return bestFitIndex;
}

int worstFit(int size) {
    int worstFitIndex = -1;
    int worstFitSize = -1;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        if (!memory[i].isAllocated && sizeof(struct MemoryBlock) >= size) {
            if (sizeof(struct MemoryBlock) > worstFitSize) {
                worstFitIndex = i;
                worstFitSize = sizeof(struct MemoryBlock);
            }
        }
    }
    if (worstFitIndex != -1) {
        memory[worstFitIndex].isAllocated = 1;
    }
    return worstFitIndex;
}

void displayCustomer(struct Customer customer) {
    printf("Account Number: %d\n", customer.accountNumber);
    printf("Customer Name: %s\n", customer.name);
    printf("Account Balance: %.2f\n", customer.balance);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Start the timer

    initializeMemory();

    printf("\n\t\tBank Management System\t\t\n");

    int choice, index;
    while (1) {
        printf("\n1. Allocate Memory for New Account (First Fit)\n");
        printf("2. Allocate Memory for New Account (Best Fit)\n");
        printf("3. Allocate Memory for New Account (Worst Fit)\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                index = firstFit(sizeof(struct MemoryBlock));
                break;
            case 2:
                index = bestFit(sizeof(struct MemoryBlock));
                break;
            case 3:
                index = worstFit(sizeof(struct MemoryBlock));
                break;
            case 4:
                end = clock(); // Stop the timer
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Exiting program. Total execution time: %f seconds\n", cpu_time_used);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                continue;
        }

        if (index != -1) {
            printf("\n\tMemory block allocated at index %d\n", index);
            printf("\nEnter Customer Name: ");
            scanf("%s", memory[index].customer.name);
            printf("Enter Account Number: ");
            scanf("%d", &memory[index].customer.accountNumber);
            printf("Enter Initial Account Balance: ");
            scanf("%f", &memory[index].customer.balance);

            printf("\n\tAccount Information:\n");
            displayCustomer(memory[index].customer);
            printf("\n\tAccount Successfully Created.\n");
        } else {
            printf("Memory allocation failed. Insufficient memory.\n");
        }
    }

    return 0;
}
