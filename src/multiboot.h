#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    // (biz şimdilik sadece bu ikisini kullanıyoruz)
} __attribute__((packed)) multiboot_info_t;

#endif
