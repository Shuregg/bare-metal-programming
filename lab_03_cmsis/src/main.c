#include <stm32h7xx.h>
// #include "cmsis_os2.h"
#include <stdio.h>
#include <main.h>
#include <user_leds.h>

extern volatile uint32_t delay_timer_value;

// __attribute__((optimize("-O0"))) static void delay(int ms) {
//     volatile int counter = SystemCoreClock / 1000 / 6 * ms ;
//     while (counter > 0) counter -= 1;
// }

void delay_ms(uint32_t delay) {
	delay_timer_value = delay;

	while(delay_timer_value) {
        /* // */ delay_timer_value--;
    };
}

void main() {
    led_enable(led_yellow);
    led_enable(led_green);
    led_enable(led_red);
    while(1) {
        static int counter = 0;
        led_toggle(led_yellow);
        led_toggle(led_green);
        led_toggle(led_red);
        delay_ms(1000000);
    };
}
