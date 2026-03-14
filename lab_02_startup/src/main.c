#if USE_HEADERS
    #include <main.h>
#else
    #include <stdint.h>
    void main(void);
#endif

uint32_t x;
uint32_t y = 0x11223344;

void main(void) {
    while(1) {
        x++;
        y--;
    }
}