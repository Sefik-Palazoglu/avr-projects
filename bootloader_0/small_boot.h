#ifndef SMALL_BOOT_H
#define SMALL_BOOT_H

#include <avr/boot.h>

#define boot_page_erase_small(address)        \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),        \
          "r" ((uint8_t)(__BOOT_PAGE_ERASE)),    \
          "z" ((uint16_t)(address))              \
    );                                           \
}))

#define boot_page_write_small(address)        \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),        \
          "r" ((uint8_t)(__BOOT_PAGE_WRITE)),    \
          "z" ((uint16_t)(address))              \
    );                                           \
}))

#define boot_rww_enable_small()                      \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),        \
          "r" ((uint8_t)(__BOOT_RWW_ENABLE))     \
    );                                           \
}))

#define boot_page_fill_small(address, data)   \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "movw  r0, %3\n\t"                       \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        "clr  r1\n\t"                            \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),        \
          "r" ((uint8_t)(__BOOT_PAGE_FILL)),     \
          "z" ((uint16_t)(address)),             \
          "r" ((uint16_t)(data))                 \
        : "r0"                                   \
    );                                           \
}))

#endif // SMALL_BOOT_H
