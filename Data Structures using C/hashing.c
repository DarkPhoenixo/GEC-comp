#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 7 



struct Record {
    int key;
    enum type_of_record {EMPTY, DELETED, OCCUPIED} status;
};

struct Record table[MAX];

int hash(int key) {
    return key % MAX;
}

int search(int key, struct Record table[]) {
    int h = hash(key);
    int location = h;
    int i;
    for (i = 1; i != MAX; i++) {
        if (table[location].status == EMPTY) {
            return -1;
        }
        if (table[location].key == key) {
            return location;
        }
        location = (h + i) % MAX;
    }
    return -1;
}

int quad_search(int key, struct Record table[]) {
    int h = hash(key);
    int location = h;
    int i;
    for (i = 1; i != MAX; i++) {
        if (table[location].status == EMPTY) {
            return -1;
        }
        if (table[location].key == key) {
            return location;
        }
        location = (h + (i * i)) % MAX;
    }
    return -1;
}

int hashsec(int key) {
    return (7 + (key % 7));
}

int doub_search(int key, struct Record table[]) {
    int h = hash(key);
    int hsec = hashsec(key);
    int location = h;
    int i;
    for (i = 1; i != MAX; i++) {
        if (table[location].status == EMPTY) {
            return -1;
        }
        if (table[location].key == key) {
            return location;
        }
        location = (h + (hsec * i)) % MAX;
    }
    return -1;
}

void insert(int key, struct Record table[]) {
    int h = hash(key);
    int location = h;
    int i;
    for (i = 0; i != MAX; i++) {
        if (table[location].status == EMPTY || table[location].status == DELETED) {
            table[location].key = key;
            table[location].status = OCCUPIED;
            printf("Record inserted\n");
            return;
        }
        location = (h + i) % MAX;
    }
    if (table[location].key == key) {
        printf("Duplicate key\n");
        return;
    } else {
        printf("Record cannot be inserted: Table Overflow\n");
        return;
    }
}


void quad_insert(int key, struct Record table[]) {
    int h = hash(key);
    int location = h;
    int i;
    for (i = 0; i != MAX; i++) {
        if (table[location].status == EMPTY || table[location].status == DELETED) {
            table[location].key = key;
            table[location].status = OCCUPIED;
            printf("Record inserted\n");
            return;
        }
        location = (h + (i * i)) % MAX;
    }
    if (table[location].key == key) {
        printf("Duplicate key\n");
        return;
    } else {
        printf("Record cannot be inserted: Table Overflow\n");
        return;
    }
}

void double_insert(int key, struct Record table[]) {
    int h = hash(key);
    int hsec = hashsec(key);
    int location = h;
    int i;
    for (i = 0; i != MAX; i++) {
        if (table[location].status == EMPTY || table[location].status == DELETED) {
            table[location].key = key;
            table[location].status = OCCUPIED;
            printf("Record inserted\n");
            return;
        }
        location = (h + (hsec * i)) % MAX;
    }
    if (table[location].key == key) {
        printf("Duplicate key\n");
        return;
    } else {
        printf("Record cannot be inserted: Table Overflow\n");
        return;
    }
}

void delete(int dkey, struct Record table[]) {
    int location = search(dkey, table);
    if (location == -1) {
        printf("Key not found\n");
    } else {
        table[location].status = DELETED;
        printf("Record deleted\n");
    }
}

void display(struct Record table[]) {
    int i;
    int hasRecords = 0;
    for (i = 0; i < MAX; i++) {
        if (table[i].status == OCCUPIED) {
            hasRecords = 1;
            break;
        }
    }
    if (hasRecords) {
        printf("Location\tKey\n");
        for (i = 0; i != MAX; i++) {
            if (table[i].status == OCCUPIED) {
                printf("%8d\t%d\n", i, table[i].key);
            }
        }
    } else {
        printf("No records to display\n");
    }
}

int main() {
    int choice, key;
int i,n,option;
int num [MAX];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
             printf("Enter the number of elements to be inserted: ");
                scanf("%d",&n);
                for(i=0;i<n;i++){
                    printf("Enter the element: ");
                    scanf("%d",&num[i]);
                }
                printf ("Enter the choice of probing ,enter 1 for linear probing ,2 for quadratic probing and 3 for Double Hashing \n");   
                scanf("%d",&option);
                
                    switch(choice){
                        case 1:
                        for (i=0;i<n;i++){
                            insert(num[i],table);}
                            break;
                        case 2:
                        for (i=0;i<n;i++){
                            quad_insert(num[i],table);}
                            break;
                        case 3:
                        for (i=0;i<n;i++){
                            double_insert(num[i],table);}
                            break;
                            default : printf("Invalid choice\n");
                            break ;
                    }
                    break ;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key, table);
                break;
            case 3:
                display(table);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
