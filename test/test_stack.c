#include <quest/quest.h>
#include <stdio.h>

int main(void) {
    quest_stack_t *stack = quest_stack_init(sizeof(int), 10);
    if (!stack) return 1;

    int x = 42;
    quest_stack_push(stack, &x);

    if (quest_stack_is_empty(stack)) return 2;
    if (quest_stack_size(stack) != 1) return 3;

    int out = 0;
    quest_stack_top(stack);
    quest_stack_pop(stack, &out);
    if (out != 42) return 4;

    if (!quest_stack_is_empty(stack)) return 5;

    quest_stack_reset(stack);
    quest_stack_cleanup(stack);
    return 0;
}
