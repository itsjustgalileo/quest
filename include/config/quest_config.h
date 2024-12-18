#ifndef QUEST_CONFIG_H_
#define QUEST_CONFIG_H_

#include <quest/quest_platforms.h>

#if defined(QUEST_PLATFORM_WINDOWS)
#include <config/quest_config_windows.h>
#elif defined(QUEST_PLATFORM_LINUX)
#include <config/quest_config_generic.h>
#else
#error "Define you platform"
#include <config/quest_config_generic.h>
#endif

#endif /* QUEST_CONFIG_H_ */
