//ref to LostWakeup of 杭州电子科技大学
//gitlab:https://gitlab.eduxiji.net/202310336101112/LostWakeup

#include "../include/fs/fat32_stack.h"
#include "../include/type.h"
#include "../include/usr/lib.h"

// 初始化栈
void stack_init(Stack_t *stack) {
    stack->data = (elemtype *)malloc(30 * 32);
    if (stack->data == NULL) {
        panic("stack_init : there is no free space\n");
    }
    stack->top = -1;
}

// 判断栈是否为空
int stack_is_empty(Stack_t *stack) {
    return stack->top == -1;
}

// 判断栈是否已满
int stack_is_full(Stack_t *stack) {
    return stack->top == CAPACITY - 1;
}

// 入栈操作
void stack_push(Stack_t *stack, elemtype item) {
    if (stack_is_full(stack)) {
        panic("Stack Overflow!");
    }
    stack->data[++stack->top] = item;
}

// 出栈操作
elemtype stack_pop(Stack_t *stack) {
    if (stack_is_empty(stack)) {
        panic("Stack Underflow!");
    }
    return stack->data[stack->top--];
}

// 获取栈顶元素
elemtype stack_peek(Stack_t *stack) {
    if (stack_is_empty(stack)) {
        panic("Stack is empty!");
    }
    return stack->data[stack->top];
}

void stack_free(Stack_t *stack) {
    free(stack->data);
}
