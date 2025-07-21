#include <math/quest_math.h>

#include <math.h>
#include <complex.h>

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

void dft(double *in, double complex *out, size_t n) {
    for (size_t k = 0; k < n / 2.0; ++k) {
        out[k] = 0;
        for (size_t i = 0; i < n; ++i) {
            out[k] += in[i] * exp(2.0 * I * QUEST_PI * k / n);
        }
    }
}

void quest_fft(double *in, double complex *out, size_t length) {
    assert(in && out);
    assert((length & (length - 1)) == 0);
    if (length == 1) {
        out[0] = in[0];
        return;
    }

    double even[length / 2];
    double odd[length / 2];
    
    for (size_t i = 0; i < length / 2; ++i) {
            even[i] = in[2*i];
            odd[i] = in[2*i + 1];
    }

    double complex evens[length / 2];
    double complex odds[length / 2];

    quest_fft(even, evens, length / 2);
    quest_fft(odd, odds, length / 2);    
    
    for (size_t k = 0; k < length / 2; ++k) {
        double twiddle = exp(-2.0 * I * QUEST_PI * k / length);
        out[k] = evens[k] + twiddle * odds[k];
        out[k + length / 2] = evens[k] - twiddle * odds[k];
    }
    
    return;
}
