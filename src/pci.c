#include "os.h"

static inline uint32_t pciRead(uint8_t bus, uint8_t slot, uint8_t func, uint8_t off){
    uint32_t addr = (1u<<31) | (bus<<16) | (slot<<11) | (func<<8) | (off & 0xFC);
    __asm__ volatile("outl %0, %1"::"a"(addr),"d"(0xCF8));
    uint32_t data;
    __asm__ volatile("inl %1, %0":"=a"(data):"d"(0xCFC));
    return data;
}

static const char* vendor_name(uint16_t v){
    if(v==0x10DE) return "NVIDIA";
    if(v==0x1002) return "AMD";
    if(v==0x8086) return "Intel";
    return "Bilinmeyen";
}

void pci_scan_and_print(void){
    print("PCI taramasi:\n");
    for(int bus=0; bus<256; bus++){
        for(int slot=0; slot<32; slot++){
            for(int func=0; func<1; func++){ // basit: func0
                uint32_t id = pciRead(bus,slot,func,0x00);
                uint16_t vendor = id & 0xFFFF;
                if(vendor == 0xFFFF) continue;
                uint16_t device = (id>>16)&0xFFFF;

                uint32_t classreg = pciRead(bus,slot,func,0x08);
                uint8_t base = (classreg>>24)&0xFF;
                uint8_t sub  = (classreg>>16)&0xFF;

                // Sadece display controller'ları yaz
                if(base==0x03){
                    print("  GPU: "); print(vendor_name(vendor));
                    print(" ("); print_hex16(vendor); print(":"); print_hex16(device); print(")");
                    print(" class "); print_hex16((base<<8)|sub);
                    print("\n");
                }
            }
        }
    }
}
