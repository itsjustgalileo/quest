#include <quest/quest.h>
#include <stdio.h>

int main(void) {
    quest_ticks_init();

    uint64 before = quest_get_ticks();
    quest_sleep(100); // sleep 100ms
    uint64 after = quest_get_ticks();

    if (after <= before) return 1;

    quest_ticks_shutdown();
    return 0;
}
