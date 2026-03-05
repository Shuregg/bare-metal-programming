prog:
	openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c init -c "reset halt" -c "flash write_image erase startup.bin" -c "verify_image final.elf" -c reset -c exit

disable_led:
	openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c init -c "reset halt" -c "write_memory 0x58020414 8 0x01" -c exit