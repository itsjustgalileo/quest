#ifndef QUEST_WINDOWS_H_
#define QUEST_WINDOWS_H_

#ifdef QUEST_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif /* WIN32_LEAN_AND_MEAN */

#ifndef STRICT
#define STRICT 1
#endif /* STRICT */

#ifndef UNICODE
#define UNICODE 1
#endif /* UNICODE */

#endif /* QUEST_PLATFORM_WINDOWS */

#include <windows.h>

#endif /* QUEST_WINDOWS_H_ */
