#include <stdint.h>
#include <main.h>

#define STACK_INIT (0x20020000)

extern uint8_t ldata;
extern uint8_t sdata;
extern uint8_t edata;
extern uint8_t sbss;
extern uint8_t ebss;

void reset_handler(void);
void init_data(void);
void init_bss(void);

volatile uint32_t delay_timer_value = 0;

__attribute__((weak, alias("default_handler"))) void nmi_handler(void);
__attribute__((weak, alias("default_handler"))) void hard_fault_handler(void);
__attribute__((weak, alias("default_handler"))) void memory_management_fault_handler(void);
__attribute__((weak, alias("default_handler"))) void bus_fault_handler(void);
__attribute__((weak, alias("default_handler"))) void usage_fault_handler(void);
__attribute__((weak, alias("default_handler"))) void svcall_handler(void);
__attribute__((weak, alias("default_handler"))) void pendsv_handler(void);
__attribute__((weak, alias("default_handler"))) void systick_handler(void);
