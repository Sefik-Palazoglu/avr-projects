#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <sys/types.h>
#include "small_boot.h"
#include "uart.h"
#include "command.h"
#include "wdt_unsafe.h"

void _Noreturn Go_To_Application_Start(void);
void synchronize_with_stk500();
void Read_N_Characters(uint8_t count);

uint8_t* ram_buffer = (uint8_t*) RAMSTART;

__attribute__ ((used))
__attribute__ ((section(".text.my_bootloader")))
void bootloader_func(void)
{
  asm volatile ("eor r1, r1");
  uint8_t mcusr = MCUSR;
  uint16_t cursor;
  MCUSR = 0x00;

  if (mcusr & _BV(EXTRF))
  {
    Init_UART();
    enable_wdt_timeout1s_unsafe();
    wdt_reset();

    while (1)
    {
      uint8_t command = Read_USART();
      if (command == Cmnd_STK_GET_PARAMETER) {

        uint8_t parameter = Read_USART();
        synchronize_with_stk500();
        if (parameter == Parm_STK_SW_MAJOR || parameter == Parm_STK_SW_MINOR)
          Write_USART(0x04);
        else
          Write_USART(0x03);
      }
      else if (command == Cmnd_STK_SET_DEVICE) {

        Read_N_Characters(0x14);
        synchronize_with_stk500();
      }
      else if (command == Cmnd_SET_DEVICE_EXT) {

        Read_N_Characters(0x05);
        synchronize_with_stk500();
        }
      else if (command == Cmnd_STK_LOAD_ADDRESS) {

        cursor = Read_USART() | ((uint16_t) Read_USART() << 8);
        cursor *= 2;
        synchronize_with_stk500();
      }
      else if (command == Cmnd_STK_UNIVERSAL) {

        Read_N_Characters(0x04);
        synchronize_with_stk500();
        Write_USART(0x00);
      }
      else if (command == Cmnd_STK_PROG_PAGE) {

        uint8_t __attribute ((unused)) bytes_high = Read_USART();
        uint8_t bytes_low = Read_USART();
        uint8_t __attribute ((unused)) memtype = Read_USART();

        boot_page_erase_small(cursor);

        for (uint8_t i = 0; i < bytes_low; i++)
        {
          ram_buffer[i] = Read_USART();
        }

        synchronize_with_stk500();
        boot_spm_busy_wait();

        for (uint8_t i = 0; i < SPM_PAGESIZE; i += 2)
        {
          uint16_t data = ram_buffer[i] | ((uint16_t) ram_buffer[i + 1] << 8);
          boot_page_fill_small(cursor + i, data);
        }

        boot_page_write_small(cursor);
        boot_spm_busy_wait();
        boot_rww_enable_small();
      }
      else if (command == Cmnd_STK_READ_PAGE) {

        Read_USART();
        uint8_t program_byte_count = Read_USART();
        Read_USART();
        synchronize_with_stk500();

        do {
          Write_USART(pgm_read_byte_near(cursor++));
          program_byte_count--;
        } while (0 != program_byte_count);
      }
      else if (command == Cmnd_STK_READ_SIGN) {

        synchronize_with_stk500();
        Write_USART(0x1E);
        Write_USART(0x95);
        Write_USART(0x0F);
      }
      else if (command == Cmnd_STK_LEAVE_PROGMODE) {

        enable_wdt_timeout15ms_unsafe();
        synchronize_with_stk500();
      }
      else {

        synchronize_with_stk500();
      }

      Write_USART(Resp_STK_OK);
    }
  }
  else {

    Go_To_Application_Start();
  }
}

void _Noreturn Go_To_Application_Start(void)
{
  disable_wdt_unsafe();
  asm volatile 
  (
    "ijmp\n\t"
    :
    : "z" ((uint16_t)(0x0000))
  );

  __builtin_unreachable();
}

void synchronize_with_stk500()
{
  uint8_t data = Read_USART();
  if (data == Sync_CRC_EOP)
  {
    Write_USART(Resp_STK_INSYNC);
  }
  else
  {
    enable_wdt_timeout15ms_unsafe();
    while (1) ;
    __builtin_unreachable();
  }
}

void Read_N_Characters(uint8_t count)
{
  while (count)
  {
    Read_USART();
    count -= 1;
  }
}
