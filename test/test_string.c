#include <quest/quest.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    // Memory
    char buf[32] = {0};
    quest_memset(buf, 'A', 5);
    if (memcmp(buf, "AAAAA", 5) != 0) return 1;

    // String builder
    quest_string_builder_t sb = {0};
    if (!quest_string_builder_init(&sb, 16)) return 2;

    quest_string_builder_append_cstr(&sb, "Hello ");
    quest_string_builder_append_char(&sb, 'Q');

    quest_string_view_t view;
    quest_string_view_from_cstr(&view, "uest");
    quest_string_builder_append_view(&sb, &view);

    if (strcmp(quest_string_builder_cstr(&sb), "Hello Quest") != 0) return 3;

    quest_string_builder_clear(&sb);
    if (quest_string_builder_length(&sb) != 0) return 4;

    quest_string_builder_cleanup(&sb);
    return 0;
}
