#include <math/quest_math.h>

/* Bailey-Borwein-Plouffe's formula */
double quest_pi(void) {
    double pi = 0.0;
    double factor = 1.0;
    for (int k = 0; k < QUEST_PI_MIN_ITERATIONS; ++k) {
        pi += (
            factor *
            ((4.0 / (8*k + 1)) -
            (2.0 / (8*k + 4)) -
            (1.0 / (8*k + 5)) -
            (1.0 / (8*k + 6)))
            );
        factor /= 16.0;
    }
    return pi;
}

uint32 quest_factorial(uint32 n) {
    /* First instinct is to write
       return n <= 1 ? 1 : n * factorial(n - 1);
       But in case n gets too large, recursion is counterintuitivem
       And this is not Haskell
    */
    uint32 r = 1;
    for (uint32 i = 1; i < n; ++i) {
        r *= i;
    }
    return r;
}

uint32 quest_gcd(uint32 a, uint32 b) {
    if (0 == b) {
        return a;
    }
    /* I mean here we can afford recursive call
       since the call will not be repeated that much
    */
    return quest_gcd(b, a % b);
}
