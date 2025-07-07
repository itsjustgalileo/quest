#include <quest/quest_todo.h>

#include <stdio.h>

void quest_todo_impl(const char *file, const char *func, int line, const char *msg) {
    fprintf(stderr, "\x1b[;31m[QUEST - TODO] - In file: %s | In function: %s | On line: %d\n\t***%s\n\x1b[;0m", file, func, line, msg);
    exit(1);
}
