#include "rng/prng.h"
#include "print/print.h"
#include "debug/debug.h"
#include "sysproc/sysinfo.h"

uint64_t seed = PRNG_SEED;

uint64_t prng_get(){
    uint64_t ticks = sysinfo_get_ticks();
    if (ticks == 0 || ticks == seed){
        seed++;
    } else {
        seed = ticks;
    }
    uint64_t a = seed * 15485863;
    return (a * a * a % 2038074743);
}