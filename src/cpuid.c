#include "os.h"

void cpu_brand(char out[49]){
    // 0x80000000 desteği var mı kontrol
    unsigned int eax, ebx, ecx, edx;
    __asm__ volatile("cpuid":"=a"(eax):"a"(0x80000000):"ebx","ecx","edx");
    if(eax < 0x80000004){ out[0]='\0'; return; }
    unsigned int* p=(unsigned int*)out;
    for(unsigned i=0;i<3;i++){
        __asm__ volatile("cpuid"
            : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
            : "a"(0x80000002+i));
        *p++=eax; *p++=ebx; *p++=ecx; *p++=edx;
    }
    out[48]='\0';
}
