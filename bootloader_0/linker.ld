SECTIONS
{
	.text :
	{
		*(.text)
	}
	
	.bootloader 0x7E00 :
	{
		KEEP(boot_init.o (.bootloader))
		KEEP(boot.o (.bootloader))
	}
}
