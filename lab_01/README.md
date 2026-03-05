# Lab 1. LED Blinking 

## 1. Run OpenOCD

```bash
    openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c init -c "reset halt"
```

## 2. Connnect to MCU

In other terminal session:

```bash
telnel localhost 4444
```

## 3. Reading registers


### pc

```bash
reg pc
```

```log
pc (/32): 0x0800631c
```

### sp

```bash
reg sp
```

```log
sp (/32): 0x24080000
```

### r0

```bash
reg r0
```

```log
r0 (/32): 0x00000000
```

## 4. Run MCU program

```bash
resume
```

## 5. Compare current firmware 

### With startup.bin

```bash
verify_image ./startup.bin
```

### With final.elf

```bash
verify_image ./final.elf
```

## 6. Dump current firmware

```bash
dump_image ./dumped_image.bin 0x08000000 256
```

## 7. Read first 2 words of firmware

```bash
mdw 0x08000000 2
```

```log
0x08000000: 24080000 0800631d
```

## 8. Reset MCU

```bash
reset run
```

## 9. GPIO

### GPIOB addresses

* `GPIOB` addresses from Memory map from reference manual: `0x58020400` - `0x580207FF` 

* Read all GPIOB addresses

```bash
read_memory 0x58020400 32 256
```
```log
0xdffffebe 0x0 0xc0 0x102 0x10 0x0 0x0 0x0 0x2 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0
```

## 10. Turn on LED


### LEDs info

_User LD1: a green user LED is connected to the STM32H7 I/O PB0 (SB65 OFF and SB54
ON) or PA5 (SB65 ON and SB54 OFF) corresponding to the ST Zio D13.
User LD2: a yellow user LED is connected to PE1.
User LD3: a red user LED is connected to PB14._

### Turn off clocking for GPIOB (GPIOBEN)

> read_memory 0x580244E0 32 1

> write_memory 0x580244E0 32 0xed0e81e2

### Set output mode for PB14 (MODER14[1:0])

```bash
read_memory 0x58020400 32 1
```

0xdffffebe


```bash
write_memory 0x58020400 32 0xdffffebe
```

### Set push/pull mode to port 14



### Set Ouput Data Register (ODR)

```bash
read_memory 0x58020414 32 1 
```


0x10

```bash
write_memory 0x58020410 32 0x00004000
```

## User button

### Push-buttons info

_B1 user (Blue button): the user button is connected to the I/O PC13 by default (Tamper
support, SB82 ON and SB81 OFF) or PA0 (Wakeup support, SB81 ON and SB82 OFF) of
the STM32H7 microcontroller.
B2 reset (Black button): this push-button is connected to NRST and is used to reset the
STM32H7 microcontroller._


### Turn on clocking for GPIOC (RCC_AHB4ENR)

```bash
write_memory 0x580244E0 32 0xffffffff
```

### Turn on push-pull mode for PC13 (GPIOX_OTYPER)

```bash
read_memory 0x58020404 32 1;         
```

0x0

### Set Input mode for PC13 (GPIOx_MODER)

```bash
write_memory 0x58020400 32 0x50000000
```

### Read Input Data Register (GPIOx_IDR)

```bash
read_memory 0x58020810 32 1
```

0x0

```bash
read_memory 0x58020810 32 1
```

0x2000

## Upload other firmware

### Upload

```bash
openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c init -c "reset halt" -c "flash write_image erase final.elf" -c reset -c exit
``` 

```log
Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : clock speed 1800 kHz
Info : STLINK V3J7M2 (API v3) VID:PID 0483:374E
Info : Target voltage: 3.281275
Info : [stm32h7x.cpu0] Cortex-M7 r1p1 processor detected
Info : [stm32h7x.cpu0] target has 8 breakpoints, 4 watchpoints
Info : starting gdb server for stm32h7x.cpu0 on 3333
Info : Listening on port 3333 for gdb connections
[stm32h7x.cpu0] halted due to breakpoint, current mode: Thread 
xPSR: 0x01000000 pc: 0x0800631c msp: 0x24080000
[stm32h7x.cpu0] halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x0800631c msp: 0x24080000
Info : Device: STM32H74x/75x
Info : flash size probed value 2048k
Info : STM32H7 flash has dual banks
Info : Bank (0) size is 1024 kb, base address is 0x08000000
Info : Padding image section 1 at 0x08001634 with 12 bytes (bank write end alignment)
Warn : Adding extra erase range, 0x08001640 .. 0x0801ffff
auto erase enabled
wrote 5696 bytes from file final.elf in 0.977707s (5.689 KiB/s)
```

### Upload and verify

```bash
openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c init -c "reset halt" -c "flash write_image erase final.elf" -c "verify_image final.elf" -c reset -c exit
```

```log
Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : clock speed 1800 kHz
Info : STLINK V3J7M2 (API v3) VID:PID 0483:374E
Info : Target voltage: 3.281275
Info : [stm32h7x.cpu0] Cortex-M7 r1p1 processor detected
Info : [stm32h7x.cpu0] target has 8 breakpoints, 4 watchpoints
Info : starting gdb server for stm32h7x.cpu0 on 3333
Info : Listening on port 3333 for gdb connections
[stm32h7x.cpu0] halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x08000e44 msp: 0x20020000
Info : Device: STM32H74x/75x
Info : flash size probed value 2048k
Info : STM32H7 flash has dual banks
Info : Bank (0) size is 1024 kb, base address is 0x08000000
Info : Padding image section 1 at 0x08001634 with 12 bytes (bank write end alignment)
Warn : Adding extra erase range, 0x08001640 .. 0x0801ffff
auto erase enabled
wrote 5696 bytes from file final.elf in 0.978227s (5.686 KiB/s)

verified 5684 bytes in 0.105425s (52.651 KiB/s)
```

