
#include <stdio.h>
#include <string.h>

char stack[50] = "$";
char input[50];
int top = 0, i = 0;

void display(char *action) {
    stack[top + 1] = '\0';
    printf("%-12s %-12s %s\n", stack, input + i, action);
}

int main() {
    printf("Enter expression (use i for identifiers): ");
    scanf("%49s", input);
    strcat(input, "$");

    printf("\nStack       Input        Action\n");

    while (input[i] != '$') {
        if (input[i] == 'i') {
            stack[++top] = 'i';
            display("Shift");
            i++;

            stack[top] = 'E';
            display("Reduce E->i");
        }
        else if (input[i] == '+' || input[i] == '*') {
            stack[++top] = input[i];
            display("Shift");
            i++;
        }
        else {
            printf("Rejected\n");
            return 0;
        }

        if (top >= 3 && stack[top] == 'E' &&
            (stack[top - 1] == '+' || stack[top - 1] == '*') &&
            stack[top - 2] == 'E') {
            char op = stack[top - 1];

            top -= 2;
            stack[top] = 'E';

            if (op == '+')
                display("Reduce E->E+E");
            else
                display("Reduce E->E*E");
        }
    }

    if (top >= 2 && stack[top] == 'E' &&
        (stack[top - 1] == '+' || stack[top - 1] == '*') &&
        stack[top - 2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        display("Reduce E->E op E");
    }

    if (top == 1 && stack[top] == 'E')
        display("Accepted");
    else
        printf("Rejected\n");

    return 0;
}

