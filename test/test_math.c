#include <quest/quest.h>
#include <math/quest_math.h>

int main(void) {
    int in[1] = {69};
    int out[1];
    quest_fft(in, out, QUEST_ARRAY_LENGTH(in));
    return 0;
}
