
#ifdef USE_HEADERS
    #include <startup.h>
#else
    #include <stdint.h>

    #define STACK_INIT (0x20020000)

    extern uint8_t ldata;
    extern uint8_t sdata;
    extern uint8_t edata;
    extern uint8_t sbss;
    extern uint8_t ebss;

    void reset_handler(void);
    void init_data(void);
    void init_bss(void);

    __attribute__((weak, alias("default_handler"))) void nmi_handler(void);
    __attribute__((weak, alias("default_handler"))) void hard_fault_handler(void);
    __attribute__((weak, alias("default_handler"))) void memory_management_fault_handler(void);
    __attribute__((weak, alias("default_handler"))) void bus_fault_handler(void);
    __attribute__((weak, alias("default_handler"))) void usage_fault_handler(void);
    __attribute__((weak, alias("default_handler"))) void reserved_handler(void);
    __attribute__((weak, alias("default_handler"))) void svcall_handler(void);
    __attribute__((weak, alias("default_handler"))) void reserved_for_debug_handler(void);
    __attribute__((weak, alias("default_handler"))) void pendsv_handler(void);
    __attribute__((weak, alias("default_handler"))) void systick_handler(void);
#endif

#ifdef USE_VOID_PTR_FOR_ISR
    __attribute__((section(".isr_vectors"))) void* uint32_t isr_vectors[] = {
        (void*)STACK_INIT                   // 0x0000
        ,&reset_handler                     // 0x0004
        ,&nmi_handler                       // 0x0008
        ,&hard_fault_handler                // 0x000C
        ,&memory_management_fault_handler   // 0x0010
        ,&bus_fault_handler                 // 0x0014
        ,&usage_fault_handler               // 0x0018
        ,&reserved_handler                  // 0x0020
        ,&reserved_handler                  // 0x0024
        ,&reserved_handler                  // 0x0028
        ,&svcall_handler                    // 0x002C
        ,&reserved_for_debug_handler        // 0x0030
        ,&reserved_handler                  // 0x0034
        ,&pendsv_handler                    // 0x0038
        ,&systick_handler                   // 0x003C
    };
#else
    __attribute__((section(".isr_vectors"))) uint32_t isr_vectors[] = {
        STACK_INIT                                    // 0x0000
        ,(uint32_t)&reset_handler                     // 0x0004
        ,(uint32_t)&nmi_handler                       // 0x0008
        ,(uint32_t)&hard_fault_handler                // 0x000C
        ,(uint32_t)&memory_management_fault_handler   // 0x0010
        ,(uint32_t)&bus_fault_handler                 // 0x0014
        ,(uint32_t)&usage_fault_handler               // 0x0018
        ,(uint32_t)0                                  // 0x0020
        ,(uint32_t)0                                  // 0x0024
        ,(uint32_t)0                                  // 0x0028
        ,(uint32_t)&svcall_handler                    // 0x002C
        ,(uint32_t)0                                  // 0x0030
        ,(uint32_t)0                                  // 0x0034
        ,(uint32_t)&pendsv_handler                    // 0x0038
        ,(uint32_t)&systick_handler                   // 0x003C
    };
#endif

void default_handler(void) {
    while(1);
}

#ifdef USE_INIT_FUNC
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
#endif

void reset_handler(void) {
    #ifdef USE_INIT_FUNC
        init_data();
        init_bss();
    #else
        // Init .data section
        uint8_t* ldata_ptr = &ldata;
        uint8_t* sdata_ptr = &sdata;
        uint8_t* edata_ptr = &sdata;
        uint8_t* sbss_ptr = &sbss;
        uint8_t* ebss_ptr = &ebss;

        while(sdata_ptr != edata_ptr) {
            *sdata_ptr = *ldata_ptr;
            ++sdata_ptr;
            ++ldata_ptr;
        }

        // Init .bss section
        while(sbss_ptr != ebss_ptr) {
            // Init by 0
            *sbss_ptr = 0;
            ++sbss_ptr;
        }        
    #endif
    main();
    while(1);
}
