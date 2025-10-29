#include <stdio.h>
#include <stdlib.h>
#define MAX 17

struct Record {
    int key;
    struct Record *link;
};

struct Record *table[MAX];

int hash(int key) {
    return key % MAX;
}

int search(int key, struct Record *table[]) {
    int h = hash(key);
    struct Record *tmp = table[h];
    while (tmp != NULL) {
        if (tmp->key == key) {
            return h;
        }
        tmp = tmp->link;
    }
    return -1;
}

void insert(int key, struct Record *table[]) {
    int h = hash(key);
    struct Record *tmp = (struct Record *)malloc(sizeof(struct Record));
    if (search(key, table) != -1) {
        printf("Duplicate key\n");
        return;
    }
    tmp->key = key;
    tmp->link = table[h];
    table[h] = tmp;
   
}

void delete(int key, struct Record *table[]) {
    struct Record *tmp, *ptr;
    int h = hash(key);
    ptr = table[h];
    if (table[h] == NULL) {
        printf("Key not found\n");
        return;
    }
    if (ptr->key == key) {
        tmp = table[h];
        table[h] = table[h]->link;
        free(tmp);
        printf("Record deleted\n");
        return;
    }
    while (ptr->link != NULL) {
        if (ptr->link->key == key) {
            tmp = ptr->link;
            ptr->link = tmp->link;
            free(tmp);
            printf("Record deleted\n");
            return;
        }
        ptr = ptr->link;
    }
    printf("Key not found\n");
}



   
void display(struct Record *table[]) {
    int i;
    struct Record *ptr;
     printf("\nHash Table:\n");

    printf("Index \tKey\n");

    printf("-----\t---\n");
    int add ;
    for (i = 0; i < MAX; i++) {
        if (table[i] != NULL) {
            printf("[ %d ]-->", i);
            ptr = table[i];
            while (ptr != NULL) {
                add = &ptr->key;
                printf("|%4d]->[ %d",add, ptr->key);
                ptr = ptr->link;
            }
            printf("|NULL]");
            printf("\n");
        }
        else {
            printf("[ %d ] \t----\n", i);
        }
    }
}

int main() {
         printf ("*****************************************************");
    printf("\n Roll number: 23B-CO-078\n");
    printf(" PR Number - 202311098\n");
    printf("*****************************************************\n\n\n");
    int choice, key,i,n;

    for (int i = 0; i < MAX; i++) {
        table[i] = NULL;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            printf("Enter number of elements to be inserted: ");
            scanf("%d", &n);
            for (i = 0; i < n; i++) {
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key, table);
            }
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key, table);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(key, table) != -1) {
                    printf("Key found at location %d\n", search(key, table));
                } else {
                    printf("Key not found\n");
                }
                break;
            case 4:
                display(table);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
