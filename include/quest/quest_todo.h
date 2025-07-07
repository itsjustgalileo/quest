#ifndef QUEST_TODO_H_
#define QUEST_TODO_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#define quest_todo(msg) quest_todo_impl(__FILE__, __FUNCTION__, __LINE__, msg)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern QUEST_API void QUEST_DECL quest_todo_impl(const char *file, const char *func, int line, const char *msg);
#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#include <quest/quest_footer.h>

#endif /* QUEST_TODO_H_ */
