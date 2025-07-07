#ifndef QUEST_INIT_H_
#define QUEST_INIT_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern QUEST_API int32 QUEST_DECL quest_init(void);
    extern QUEST_API void QUEST_DECL quest_shutdown(void);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <quest/quest_footer.h>

#endif /* QUEST_INIT_H_ */
