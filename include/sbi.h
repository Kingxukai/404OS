#ifndef _SBI_H__
#define _SBI_H__

#include "platform.h"
#include "timer.h"

#define EXTENSION_BASE 1
#define FUNCTION_BASE_GET_SPEC_VERSION 1
#define LEGACY_SET_TIMER 0x00L
#define TIMER_EXT 0x54494D45

#define SBI_CALL(ext, funct, arg0, arg1, arg2, arg3) ({        \
    register reg64_t a0 asm("a0") = (reg64_t)(arg0);       \
    register reg64_t a1 asm("a1") = (reg64_t)(arg1);       \
    register reg64_t a2 asm("a2") = (reg64_t)(arg2);       \
    register reg64_t a3 asm("a3") = (reg64_t)(arg3);       \
    register reg64_t a6 asm("a6") = (reg64_t)(funct);      \
    register reg64_t a7 asm("a7") = (reg64_t)(ext);        \
    asm volatile("ecall"                                       \
                 : "+r"(a0), "+r"(a1)                          \
                 : "r"(a1), "r"(a2), "r"(a3), "r"(a6), "r"(a7) \
                 : "memory");                                  \
    (struct sbiret){a0, a1};                                   \
})

#define SBI_CALL_0(ext, funct) SBI_CALL(ext, funct, 0, 0, 0, 0)
#define SBI_CALL_1(ext, funct, arg0) SBI_CALL(ext, funct, arg0, 0, 0, 0)
#define SBI_CALL_2(ext, funct, arg0, arg1) SBI_CALL(ext, funct, arg0, arg1, 0, 0)
#define SBI_CALL_3(ext, funct, arg0, arg1, arg2) SBI_CALL(ext, funct, arg0, arg1, arg2, 0)
#define SBI_CALL_4(ext, funct, arg0, arg1, arg2, arg3) SBI_CALL(ext, funct, arg0, arg1, arg2, arg3)

#define SET_TIMER() sbi_legacy_set_timer(*(uint64_t *)CLIENT_MTIMER + CLOCK_PIECE)

struct sbiret {
    long error;
    long value;
};

static inline struct sbiret sbi_set_timer(uint64_t stime_value) 
{
    // stime_value is in absolute time.
    return SBI_CALL_1(TIMER_EXT, 0, stime_value);
}

static inline struct sbiret sbi_legacy_set_timer(uint64_t stime_value) 
{
    return SBI_CALL_1(LEGACY_SET_TIMER, 0, stime_value);
}

#endif
