#include <quest/quest.h>
#include <stdio.h>

int main(void) {
    if (!quest_logger_init()) return 1;

    QUEST_LOG_TRACE("Trace message");
    QUEST_LOG_DEBUG("Debug message");
    QUEST_LOG_INFO("Info message");
    QUEST_LOG_WARN("Warn message");
    QUEST_LOG_ERROR("Error message");
    // QUEST_LOG_FATAL("Fatal message"); // Will abort. Uncomment only to test fatal behavior.

    QUEST_TODO("This feature is not yet implemented");

    return 0;
}
