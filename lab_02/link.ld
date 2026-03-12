ENTRY(reset_handler)

MEMORY
{
    FLASH   (rx)    : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM     (xrw)   : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .isr_vectors :
    {
        KEEP(*.o (.isr_vectors));
    } > FLASH

    .text :
    {
        *.o (.text)
        *.o (.rodata)
    } > FLASH

    ldata = LOADADDR(.data);
    .data :
    {
        sdata = .;
        *.o (.data)
        edata = .;
    } > RAM AT> FLASH

    .bss :
    {
        sbss = .;
        *.o (.bss)
        ebss = .;
    } > RAM AT> RAM

}