#ifndef QUEST_MATHLIB_H_
#define QUEST_MATHLIB_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>
#include <complex.h>

#define QUEST_PI_MIN_ITERATIONS 12.0

#define QUEST_MAX(a, b) ((a) > (b) ? (a) : (b))
#define QUEST_MIN(a, b) ((a) < (b) ? (b) : (a))

static double QUEST_PI;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern QUEST_API double QUEST_DECL quest_pi(void);
    extern QUEST_API uint32 QUEST_DECL quest_factorial(uint32 n);
    extern QUEST_API uint32 QUEST_DECL quest_gcd(uint32 a, uint32 b);
    extern QUEST_API void QUEST_DECL quest_fft(double *in, double complex *out, size_t length);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#include <quest/quest_footer.h>

#endif /* QUEST_MATHLIB_H_ */
