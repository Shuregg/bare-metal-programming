#include <startup.h>

__attribute__((section(".isr_vectors"))) void* isr_vectors[] = {
    (void*)STACK_INIT                   // 0x0000
    ,&reset_handler                     // 0x0004
    ,&nmi_handler                       // 0x0008
    ,&hard_fault_handler                // 0x000C
    ,&memory_management_fault_handler   // 0x0010
    ,&bus_fault_handler                 // 0x0014
    ,&usage_fault_handler               // 0x0018
    ,0                                  // 0x0020
    ,0                                  // 0x0024
    ,0                                  // 0x0028
    ,&svcall_handler                    // 0x002C
    ,0                                  // 0x0030
    ,0                                  // 0x0034
    ,&pendsv_handler                    // 0x0038
    ,&systick_handler                   // 0x003C
};

void default_handler(void) {
    while(1);
}

void init_data(void) {
    // Inita .data section
    uint8_t* ldata_ptr = &ldata;
    uint8_t* sdata_ptr = &sdata;
    uint8_t* edata_ptr = &edata;
    while(sdata_ptr != edata_ptr) {
        *sdata_ptr = *ldata_ptr;
        ++sdata_ptr;
        ++ldata_ptr;
    }
}

void init_bss(void) {
    uint8_t* sbss_ptr = &sbss;
    uint8_t* ebss_ptr = &ebss;
    while(sbss_ptr != ebss_ptr) {
        // Init by 0
        *sbss_ptr = 0;
        ++sbss_ptr;
    }
}

void reset_handler(void) {
    init_data();
    init_bss();
    main();
    while(1);
}

// void systick_handler(void) {
    // delay_timer_value--;
// }