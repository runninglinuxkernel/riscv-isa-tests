OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY
{
  rom (rxa) :   ORIGIN = 0x00000000, LENGTH = 32K
  ram (rwxa) :   ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
  . = 0x0000000;
  .text.init : {
	  *(.text.init)
  } AT>rom
  . = ALIGN(0x1000);

  .tohost : {
	  *(.tohost)
   } AT>rom
  . = ALIGN(0x1000);

  .text : {
	  *(.text)
  } AT>rom
  . = ALIGN(0x1000);

  .data : {
	  *(.data)
  } >ram AT>rom

  .bss : {
	  *(.bss)
  } >ram AT>ram
  _end = .;
}

