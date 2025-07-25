#ifndef QUEST_TICKS_H_
#define QUEST_TICKS_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern QUEST_API uint32 QUEST_DECL quest_ticks_init(void);
    extern QUEST_API void QUEST_DECL quest_ticks_shutdown(void);

    extern QUEST_API uint64 QUEST_DECL quest_get_ticks(void);
    extern QUEST_API void QUEST_DECL quest_sleep(uint64 time);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#include <quest/quest_footer.h>

#endif /* QUEST_TICKS_H_ */
