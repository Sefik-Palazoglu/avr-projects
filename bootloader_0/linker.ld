SECTIONS
{
	.text :
	{
		*(.vectors)
    		KEEP(*(.vectors))
    		/* For data that needs to reside in the lower 64k of progmem.  */
    		 *(.progmem.gcc*)
    		/* PR 13812: Placing the trampolines here gives a better chance
    		   that they will be in range of the code that uses them.  */
    		. = ALIGN(2);
    		 __trampolines_start = . ;
    		/* The jump trampolines for the 16-bit limited relocs will reside here.  */
    		*(.trampolines)
    		 *(.trampolines*)
    		 __trampolines_end = . ;
    		/* avr-libc expects these data to reside in lower 64K. */
    		 *libprintf_flt.a:*(.progmem.data)
    		 *libc.a:*(.progmem.data)
    		 *(.progmem*)
    		. = ALIGN(2);
    		/* For future tablejump instruction arrays for 3 byte pc devices.
    		   We don't relax jump/call instructions within these sections.  */
    		*(.jumptables)
    		 *(.jumptables*)
    		/* For code that needs to reside in the lower 128k progmem.  */
    		*(.lowtext)
    		 *(.lowtext*)
    		 __ctors_start = . ;
    		 *(.ctors)
    		 __ctors_end = . ;
    		 __dtors_start = . ;
    		 *(.dtors)
    		 __dtors_end = . ;
		KEEP(SORT(*)(.ctors))
    		KEEP(SORT(*)(.dtors))
    		/* From this point on, we don't bother about wether the insns are
    		   below or above the 16 bits boundary.  */
    		*(.init0)  /* Start here after reset.  */
    		KEEP (*(.init0))
    		*(.init1)
    		KEEP (*(.init1))
    		*(.init2)  /* Clear __zero_reg__, set up stack pointer.  */
    		KEEP (*(.init2))
    		*(.init3)
    		KEEP (*(.init3))
    		*(.init4)  /* Initialize data and BSS.  */
    		KEEP (*(.init4))
    		*(.init5)
    		KEEP (*(.init5))
    		*(.init6)  /* C++ constructors.  */
    		KEEP (*(.init6))
    		*(.init7)
    		KEEP (*(.init7))
    		*(.init8)
    		KEEP (*(.init8))
    		*(.init9)  /* Call main().  */
    		KEEP (*(.init9))
    		*(.text)
    		. = ALIGN(2);
    		 *(.text.*)
    		. = ALIGN(2);
    		*(.fini9)  /* _exit() starts here.  */
    		KEEP (*(.fini9))
    		*(.fini8)
    		KEEP (*(.fini8))
    		*(.fini7)
    		KEEP (*(.fini7))
    		*(.fini6)  /* C++ destructors.  */
    		KEEP (*(.fini6))
    		*(.fini5)
    		KEEP (*(.fini5))
    		*(.fini4)
    		KEEP (*(.fini4))
    		*(.fini3)
    		KEEP (*(.fini3))
    		*(.fini2)
    		KEEP (*(.fini2))
    		*(.fini1)
    		KEEP (*(.fini1))
    		*(.fini0)  /* Infinite loop after program termination.  */
    		KEEP (*(.fini0))
    		 _etext = . ;
	}
	
	. = 0x7E00;
	.bootloader :
	{
		boot_init.o (.bootloader)
		boot.o (.bootloader)
	}
}

ENTRY(my_bootloader);
