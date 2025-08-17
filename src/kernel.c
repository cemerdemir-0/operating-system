#include "os.h"

typedef struct {
  uint32_t flags;
  uint32_t mem_lower;   // KB
  uint32_t mem_upper;   // KB
} multiboot_info_t;

void kernel_main(uint32_t magic, multiboot_info_t* mb) {
    (void)magic;
    vga_clear();

    #define yazdir print

    yazdir("Merhaba! \n");

    // CPU
    char brand[49] = {0};
    cpu_brand(brand);
    if (brand[0]) { yazdir("CPU : "); yazdir(brand); yazdir("\n"); }
    else { yazdir("CPU : (brand yok)\n"); }

    // RAM
    if (mb && (mb->flags & 1)) {
        uint64_t total_kb = (uint64_t)mb->mem_lower + (uint64_t)mb->mem_upper;
        yazdir("RAM : ~"); print_uint(total_kb / 1024ull); yazdir(" MB\n");
    } else {
        yazdir("RAM : (bilgi yok)\n");
    }

    // GPU
    pci_scan_and_print();

    yazdir("\nMini-OS calisiyor. Komut bekleniyor...\n");
    yazdir("\n> ");  // prompt

    char buffer[64];
    int idx = 0;

    while (1) {
        char c = kbd_getchar();   // Klavyeden karakter oku (interrupt tabanlı)
        if (c) {
            if (c == '\n') {
                buffer[idx] = '\0';

                if (!strcmp(buffer, "yardim")) {
                    yazdir("\nKomutlar:\n");
                    yazdir("  yardim - bu menuyu gosterir\n");
                    yazdir("  ram    - RAM bilgisini gosterir\n");
                } 
                else if (!strcmp(buffer, "ram")) {
                    yazdir("\nRAM tekrar: ");
                    if (mb && (mb->flags & 1)) {
                        uint64_t total_kb = (uint64_t)mb->mem_lower + (uint64_t)mb->mem_upper;
                        print_uint(total_kb / 1024ull);
                        yazdir(" MB\n");
                    } else {
                        yazdir("(bilgi yok)\n");
                    }
                } 
                else {
                    yazdir("\nBilinmeyen komut.\n");
                }

                yazdir("\n> "); // yeni prompt
                idx = 0;
            } else {
                if (idx < 63) buffer[idx++] = c;
                print_char(c); // ekrana anında yaz
            }
        }

        __asm__ volatile("hlt"); // CPU'yu boşta beklet
    }
}



extern void yazdir(const char* s);

void yardim() {
    yazdir("\nKomutlar:\n");
    yazdir(" - yardim : bu menuyu gosterir\n");
    yazdir(" - ram    : RAM miktarini gosterir\n");
    yazdir(" - uptime : sistem acilisindan beri gecen saniyeleri gosterir\n");
}



