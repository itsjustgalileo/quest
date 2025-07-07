#ifndef QUEST_TODO_INTERNAL_H_
#define QUEST_TODO_INTERNAL_H_

#include <quest/quest_todo.h>

typedef struct {
    void (*QUEST_DECL _todo)(const char *restrict msg);
} quest_todo_vtable;

#endif /* QUEST_TODO_INTERNAL_H_ */
