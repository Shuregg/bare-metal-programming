#include "flash_writer.h"

// Internal functions
int disable_irq();
int enable_irq();

int unlock_flash_cr(uint8_t bank) {
    int status = 0;

    switch(bank) {
    case 1: {
        FLASH->KEYR1 = 0x45670123;
        FLASH->KEYR1 = 0xCDEF89AB;
        break;
    }
    case 2: {
        FLASH->KEYR2 = 0x45670123;
        FLASH->KEYR2 = 0xCDEF89AB;
        break;
    }
    default: {
        status = 1;
        break;
    }
    }
    return status;
}

int enable_write_op(uint8_t bank) {
    int status = 0;

    switch(bank) {
    case 1: {
        FLASH->CR1 |= FLASH_CR_PG;
        status = (FLASH->CR1 & FLASH_CR_LOCK_Msk) || !(FLASH->CR1 & FLASH_CR_PG_Msk);
        break;
    }
    case 2: {
        FLASH->CR2 |= FLASH_CR_PG;
        status = (FLASH->CR2 & FLASH_CR_LOCK_Msk) || !(FLASH->CR2 & FLASH_CR_PG_Msk);
        break;
    }
    default: {
        status = 1;
        break;
    }
    }
    return status;
}

#if 0
int lock_flash(uint8_t bank) {
    int status = 0;
    switch(bank) {
    case 1: {
        FLASH->CR1
        status = !(FLASH->CR1 & FLASH_CR_LOCK_Msk);
        break;
    }
    case 2: {
        FLASH->KEYR2 = 0x45670123;
        FLASH->KEYR2 = 0xCDEF89AB;
        status = FLASH->CR2 & FLASH_CR_LOCK_Msk;
        break;
    }
    default: {
        status = 1;
        break;
    }
    }

    return status;
}
#endif

int single_write_seq(uint8_t bank, uint32_t* addr, uint32_t wdata) {
    int status = 0;
    uint32_t rdata;
    if(unlock_flash_cr(bank)) {
        status |= 1; 
    }

    if(enable_write_op(bank)) {
        status |= 2;
    }

    printf("Write 0x%x to 0x%x.\n", wdata, addr);
    *(addr) = wdata;
    rdata = *(addr);
    if(rdata != wdata) {
        status |= 4;
    }
    printf("Read 0x%x: 0x%x.\n", addr, rdata);

    return status;
}