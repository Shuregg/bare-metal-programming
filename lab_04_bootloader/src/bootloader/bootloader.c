#include <stm32h7xx.h>
// #include "cmsis_os2.h"
#include <stdio.h>
#include <stdint.h>
#include <user_leds.h>
#include <vterm.h>
#include <flash_writer.h>

__attribute__((optimize("-O0"))) static void delay(int ms) {
    volatile int counter = SystemCoreClock / 1000 / 6 * ms ;
    while (counter > 0) counter -= 1;
}

int main() {
    int status; 

    vterm_init(115200);

    status = single_write_seq(2, (uint32_t *)(0x08100000), 0xBEEF);

    if(status & 1) {
        printf("Erorr 1\n");
        led_enable(led_red);
        led_on(led_red);
    }
    if(status & 2) {
        printf("Erorr 2\n");
        led_enable(led_yellow);
        led_on(led_yellow);
    }
    if(status & 4) {
        printf("Erorr 3\n");
        led_enable(led_green);
        led_on(led_green);
    }
    if(!status) {
        printf("All ok!\n");
        while(1) {
            led_toggle(led_green);
            delay(1000000);
        };
    } else {
        while(1) {};
    }
    while(1) {};
}
