#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *data;
    int sp;
} Stack;

Stack *createStack(int size);

void push(Stack *stack, int i);

int pop(Stack *stack);

int main() {
    Stack *stack = createStack(100);
    push(stack, 0);
    push(stack, 1);
    push(stack, 2);
    int x = pop(stack);
    assert(x == 2);
    return 0;
}

int pop(Stack *stack) {
    return stack->data[--stack->sp];
}

void push(Stack *stack, int item) {
    stack->data[stack->sp++] = item;
}

Stack *createStack(int size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->sp = 0;
    stack->data = (int *) malloc(sizeof(int) * size);
    return stack;
}
