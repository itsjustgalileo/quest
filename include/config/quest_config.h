#ifndef QUEST_CONFIG_H_
#define QUEST_CONFIG_H_

#include <quest/quest_platforms.h>

#if defined(WIN32)
#include <build/win32_config.h>
#elif defined(__linux__)
#include <build/generic_config.h>
#else
#error "Platform configuration non existant!"
#endif

#endif /* QUEST_CONFIG_H_ */
