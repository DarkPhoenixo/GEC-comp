#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 5
#define ITEM_SIZE 10  
char buffer[BUFFER_SIZE][ITEM_SIZE]; 
int in = 0, out = 0;
int empty = BUFFER_SIZE;
int full = 0;
int mutex = 1;

void wait(int *s) {
    if (*s > 0)
        (*s)--;
    else
        printf("Wait failed: semaphore value is zero.\n");
}

void signal(int *s) {
    (*s)++;
}

void produce(char item[]) {
    wait(&empty);
    wait(&mutex);
    strcpy(buffer[in], item);
    printf("\nAdded: %s at position %d\n", item, in);
    in = (in + 1) % BUFFER_SIZE;
    signal(&mutex);
    signal(&full);
}

void consume() {
    wait(&full);
    wait(&mutex);
    printf("\nRemoved: %s from position %d\n", buffer[out], out);
    strcpy(buffer[out], "_"); 
    out = (out + 1) % BUFFER_SIZE;
    signal(&mutex);
    signal(&empty);
}

void displayBuffer() {
    int i;
    printf("\nBuffer Status:\n");
    printf("--------------\n");
    for (i = 0; i < BUFFER_SIZE; i++) {
        printf("Slot %d: %s\n", i, buffer[i]);
    }
    printf("--------------\n");
    printf("Empty: %d, Full: %d, In: %d, Out: %d\n", empty, full, in, out);
}

int main() {
    int choice;
    char item[ITEM_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
        strcpy(buffer[i], "_");
    
    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Produce Item\n");
        printf("2. Consume Item\n");
        printf("3. Display Buffer\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (empty == 0)
                    printf("\nOverflow\n");
                else {
                    printf("Enter item: ", ITEM_SIZE - 1);
                    scanf("%s", item);
                    produce(item);
                }
                break;
            case 2:
                if (full == 0)
                    printf("\nUnderflow\n");
                else
                    consume();
                break;
            case 3:
                displayBuffer();
                break;
            case 4:
                printf("\nExiting...\n");
                exit(0);
            default:
                printf("\nInvalid choice\n");
        }
    }
    return 0;
}
