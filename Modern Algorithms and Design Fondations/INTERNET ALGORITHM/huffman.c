#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TREE_HT 100
#define MAX_CHARS 256

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
    int first_occurrence; 
    int tree_num;         
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

void printArr(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

struct MinHeapNode* newNode(char data, unsigned freq, int first_occurrence, int tree_num) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    temp->first_occurrence = first_occurrence;
    temp->tree_num = tree_num;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

int compareNodes(struct MinHeapNode* a, struct MinHeapNode* b) {
    if (a->freq != b->freq) {
        return a->freq < b->freq;
    }
    
    if ((a->data != '$') != (b->data != '$')) {
        return a->data != '$';  // True if a is character node
    }
    
    if (a->data != '$' && b->data != '$') {
        return a->first_occurrence < b->first_occurrence;
    }
    
    return a->tree_num < b->tree_num;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && compareNodes(minHeap->array[left], minHeap->array[smallest])) {
        smallest = left;
    }

    if (right < minHeap->size && compareNodes(minHeap->array[right], minHeap->array[smallest])) {
        smallest = right;
    }

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compareNodes(minHeapNode, minHeap->array[parent])) {
            minHeap->array[i] = minHeap->array[parent];
            i = parent;
        } else {
            break;
        }
    }
    
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int* sortByFirstOccurrence(char* input, int* char_count) {
    int len = strlen(input);
    int* char_order = (int*)malloc(MAX_CHARS * sizeof(int));
    
    for (int i = 0; i < MAX_CHARS; i++) {
        char_order[i] = -1;
    }
    
    *char_count = 0;
    for (int i = 0; i < len; i++) {
        unsigned char ch = input[i];
        if (char_order[ch] == -1) {
            char_order[ch] = i;
            (*char_count)++;
        }
    }
    
    return char_order;
}

struct MinHeap* createInitialHeap(char* input) {
    int len = strlen(input);
    int char_count = 0;
    int* first_occurrences = sortByFirstOccurrence(input, &char_count);
    
    int freq[MAX_CHARS] = {0};
    for (int i = 0; i < len; i++) {
        freq[(unsigned char)input[i]]++;
    }
    
    struct MinHeap* minHeap = createMinHeap(char_count);
    
    struct MinHeapNode** nodes = (struct MinHeapNode**)malloc(char_count * sizeof(struct MinHeapNode*));
    int node_count = 0;
    
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            nodes[node_count++] = newNode((char)i, freq[i], first_occurrences[i], 0);
        }
    }
    
    for (int i = 0; i < node_count - 1; i++) {
        for (int j = 0; j < node_count - i - 1; j++) {
            if (!compareNodes(nodes[j], nodes[j+1])) {
                struct MinHeapNode* temp = nodes[j];
                nodes[j] = nodes[j+1];
                nodes[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < node_count; i++) {
        minHeap->array[i] = nodes[i];
    }
    
    minHeap->size = node_count;
    buildMinHeap(minHeap);
    
    free(nodes);
    free(first_occurrences);
    
    return minHeap;
}

struct MinHeapNode** getSortedHeapArray(struct MinHeap* minHeap) {
    struct MinHeapNode** sortedArray = (struct MinHeapNode**)malloc(minHeap->size * sizeof(struct MinHeapNode*));
    for (int i = 0; i < minHeap->size; i++) {
        sortedArray[i] = minHeap->array[i];
    }
    
    for (int i = 0; i < minHeap->size - 1; i++) {
        for (int j = 0; j < minHeap->size - i - 1; j++) {
            if (!compareNodes(sortedArray[j], sortedArray[j+1])) {
                struct MinHeapNode* temp = sortedArray[j];
                sortedArray[j] = sortedArray[j+1];
                sortedArray[j+1] = temp;
            }
        }
    }
    
    return sortedArray;
}

void printMinHeap(struct MinHeap* minHeap) {
    struct MinHeapNode** sortedArray = getSortedHeapArray(minHeap);
    
    for (int i = 0; i < minHeap->size; i++) {
        if (sortedArray[i]->data == '$') {
            printf("T%-2d ", sortedArray[i]->tree_num);
        } else {
            printf("%-3c ", sortedArray[i]->data);
        }
    }
    printf("\n");
    for (int i = 0; i < minHeap->size; i++) {
        printf("%-3u ", sortedArray[i]->freq);
    }
    printf("\n");
    
    free(sortedArray);
}

void printTree(struct MinHeapNode* root, int space) {
    if (root == NULL)
        return;

    space += 10;
    printTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    
    if (root->data == '$') {
        printf("T%d(%u)\n", root->tree_num, root->freq);
    } else {
        printf("%c(%u)\n", root->data, root->freq);
    }

    printTree(root->left, space);
}

struct MinHeapNode* buildHuffmanTree(char* input) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createInitialHeap(input);
    
    printf("\nInitial min heap with all characters:\n");
    printf("-------------------------------------\n");
    printMinHeap(minHeap);
    
    int treeCount = 0;
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        printf("\nStep %d: Combine nodes with lowest frequencies\n", treeCount + 1);
        printf("Node 1: ");
        if (left->data == '$') {
            printf("T%d with frequency %u\n", left->tree_num, left->freq);
        } else {
            printf("'%c' with frequency %u\n", left->data, left->freq);
        }
            
        printf("Node 2: ");
        if (right->data == '$') {
            printf("T%d with frequency %u\n", right->tree_num, right->freq);
        } else {
            printf("'%c' with frequency %u\n", right->data, right->freq);
        }
        treeCount++;
        top = newNode('$', left->freq + right->freq, INT_MAX, treeCount);
        top->left = left;
        top->right = right;
        
        printf("\nTree T%d (Combined frequency: %u):\n", treeCount, top->freq);
        printTree(top, 0);
        
        insertMinHeap(minHeap, top);
        printf("\nCurrent Min Heap after insertion:\n");
        printf("------------------------------\n");
        printMinHeap(minHeap);
    }
    printf("\nFinal Huffman Tree (T%d):\n", treeCount);
    struct MinHeapNode* result = extractMin(minHeap);
    printTree(result, 0);
    
    return result;
}

void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("'%c': ", root->data);
        printArr(arr, top);
    }
}

void storeCodes(struct MinHeapNode* root, int arr[], int top, char* huffmanCode[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, huffmanCode);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffmanCode);
    }
    if (!(root->left) && !(root->right)) {
        huffmanCode[root->data] = (char*)malloc((top + 1) * sizeof(char));
        for (int i = 0; i < top; i++) {
            huffmanCode[root->data][i] = arr[i] + '0';
        }
        huffmanCode[root->data][top] = '\0';
    }
}
void compressString(char* input) {
    int len = strlen(input);
    int freq[MAX_CHARS] = {0};
    int* first_occurrences = sortByFirstOccurrence(input, &len);  // Reusing len variable
    for (int i = 0; i < strlen(input); i++) {
        freq[(unsigned char)input[i]]++;
    }
    printf("\nBuilding Huffman Tree Step by Step:\n");
    printf("==================================\n");
    struct MinHeapNode* root = buildHuffmanTree(input);
    
    int arr[MAX_TREE_HT], top = 0;
    char* huffmanCode[MAX_CHARS] = {NULL};
    storeCodes(root, arr, top, huffmanCode);
    
    int compressedBits = 0;
    len = strlen(input);  
    for (int i = 0; i < len; i++) {
        if (huffmanCode[(int)input[i]] != NULL) {
            compressedBits += strlen(huffmanCode[(int)input[i]]);
        }
    } 
    printf("\nHuffman Codes:\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            printf("'%c': %s\n", (char)i, huffmanCode[i]);
        }
    }
    for (int i = 0; i < MAX_CHARS; i++) {
        if (huffmanCode[i] != NULL) {
            free(huffmanCode[i]);
        }
    }
    free(first_occurrences);
}

int main() {
    char input[1000];
    int choice;
    
    do {
        printf("\n=== Huffman Coding Algorithm with Step-by-Step Tree Visualization ===\n");
        printf("1. Encode a string\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1:
                printf("Enter a string to encode: ");
                fgets(input, sizeof(input), stdin);
                
                size_t len = strlen(input);
                if (len > 0 && input[len-1] == '\n') {
                    input[len-1] = '\0';
                }
                if (strlen(input) > 0) {
                    compressString(input);
                } else {
                    printf("Please enter a valid string.\n");
                }
                break;
            case 2:
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);
    
    return 0;
} 
 
