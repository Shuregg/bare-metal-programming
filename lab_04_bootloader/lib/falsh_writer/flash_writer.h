#pragma once

#include <stm32h7xx.h>
// #include <stdbool.h>

// TODO remove protected functions from header file
int unlock_flash_cr(uint8_t bank);
int enable_write_op(uint8_t bank);
int lock_flash(uint8_t bank);
int single_write_seq(uint8_t bank, uint32_t* addr, uint32_t wdata);

int flash_clear_sector(uint8_t bank, uint8_t sector);
int flash_write_word(uint32_t addr, uint32_t data);
int flash_write_data(uint32_t addr, uint32_t size, uint8_t data[]);