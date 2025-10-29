#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 50

int top = -1;
char stack_arr[MAX]; // Stack for operators
float float_stack[MAX]; // Stack for floating-point values

int isFull() {
    return top == MAX - 1;
}

void Push(char data) {
    if (isFull()) {
        printf("Stack Overflow\n");
        return;
    }
    stack_arr[++top] = data;
}

int isEmpty() {
    return top == -1;
}

char Pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack_arr[top--];
}

int floatStackIsFull() {
    return top == MAX - 1;
}

void floatPush(float data) {
    if (floatStackIsFull()) {
        printf("Float Stack Overflow\n");
        return;
    }
    float_stack[++top] = data;
}

float floatPop() {
    if (isEmpty()) {
        printf("Float Stack Underflow\n");
        exit(1);
    }
    return float_stack[top--];
}

int isOperator(char Infix) {
    return (Infix == '+' || Infix == '-' || Infix == '*' || Infix == '/' ||
            Infix == '^' || Infix == '%' || Infix == '(' || Infix == ')');
}

int Precedence(char Infix) {
    switch (Infix) {
        case '+':
        case '-': return 1;
        case '*':
        case '%':
        case '/': return 2;
        case '^': return 3;
        case '(': return 0;
        default: return -1;
    }
}

void displayConversion(char symbol, char Postfix[], int j) {
    printf("%-15c", symbol);

    for (int i = 0; i <= top; i++) {
        printf("%c", stack_arr[i]); // Display operator part
        if (i < top) printf(",");
    }
    
    int stackLength = 15 - top * 2 - 1; // Adjust spacing based on operator size
    for (int k = 0; k < stackLength; k++) {
        printf(" ");
    }

    for (int i = 0; i < j; i++) {
        printf("%c", Postfix[i]);
    }
    printf("\n");
}

char* infixtopostfix(char Infix[], char Postfix[]) {
    int i = 0, j = 0;

    printf("\n%-15s%-15s%-15s\n", "Symbol", "Stack", "Postfix");
    printf("%-15s%-15s%-15s\n", "------", "------", "-------");

    while (Infix[i] != '\0') {
        if (!isOperator(Infix[i])) {
            Postfix[j++] = Infix[i++];
        } else if (Infix[i] == '(') {
            Push(Infix[i++]);
        } else if (Infix[i] == ')') {
            while (!isEmpty() && stack_arr[top] != '(') {
                Postfix[j++] = Pop();
            }
            Pop(); // Remove '(' from stack
            i++;
        } else {
            while (!isEmpty() && Precedence(Infix[i]) <= Precedence(stack_arr[top])) {
                if (stack_arr[top] == '(') {
                    break;
                }
                Postfix[j++] = Pop();
            }
            Push(Infix[i++]);
        }
        displayConversion(Infix[i - 1], Postfix, j);
    }
    while (!isEmpty()) {
        Postfix[j++] = Pop();
        displayConversion(' ', Postfix, j);
    }
    Postfix[j] = '\0';
    return Postfix;
}

void displayEvaluation(char symbol, float result, int intResult) {
    // Print the symbol (operator or operand)
    printf("%-15c", symbol);

    // Print the float stack
    for (int i = 0; i <= top; i++) {
        printf("%6.2f", float_stack[i]); // Ensure consistent spacing
    }

    // Calculate the necessary spacing for alignment
    int floatStackLength = 15 - (top + 1) * 6; // Adjust spacing based on float size
    for (int k = 0; k < floatStackLength; k++) {
        printf(" ");
    }
    printf("      ");
    for (int i = 0; i <= top; i++) {
        printf("%4d", (int)float_stack[i]); // Ensure consistent spacing for integers
    }

    printf("\n");
}

float evaluatePostfix(char *Postfix, float values[]) {
    int i = 0;

    printf("\n%-15s%-30s%-30s\n", "Symbol", "Float Stack", "Int Eval");
    printf("%-15s%-30s%-30s\n", "------", "------------------------------", "------------------------------");

    while (Postfix[i] != '\0') {
        if (Postfix[i] >= 'A' && Postfix[i] <= 'Z') {
            floatPush(values[Postfix[i] - 'A']);
            displayEvaluation(Postfix[i], float_stack[top], (int)float_stack[top]);
        } else {
            float val1 = floatPop();
            float val2 = floatPop();
            float result;
            switch (Postfix[i]) {
                case '+': result = val2 + val1; break;
                case '-': result = val2 - val1; break;
                case '*': result = val2 * val1; break;
                case '/': result = val2 / val1; break;
                case '^': result = pow(val2, val1); break;
                case '%': result = fmod(val2, val1); break;
            }
            floatPush(result);
            displayEvaluation(Postfix[i], result, (int)result);
        }
        i++;
    }
    return float_stack[top];
}

int main() {
        printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    char Infix[MAX];
    char Postfix[MAX];

    printf("Enter the Infix Expression: ");
    scanf("%s", Infix);

    infixtopostfix(Infix, Postfix);
    printf("\nThe Postfix Expression is %s\n", Postfix);

    float values[26];
    values['A' - 'A'] = 3;   // A = 3
    values['B' - 'A'] = 2;   // B = 2
    values['C' - 'A'] = 2;   // C = 2
    values['D' - 'A'] = 2;   // D = 2
    values['E' - 'A'] = 2;   // E = 2
    values['F' - 'A'] = 1;   // F = 1

    float result = evaluatePostfix(Postfix, values);
    printf("\nThe evaluated result of the postfix expression is %.2f (float) and %d (int)\n", result, (int)result);

    return 0;
}
