#ifndef COMMAND_H
#define COMMAND_H

/**
 * @brief Get the value of a valid parameter from the STK500 starterkit.
 * If the parameter is not used, the same parameter will be returned 
 * together with a Resp_STK_FAILED response to indicate the error. 
 * See the parameters section for valid parameters and their meaning.
 */
#define Cmnd_STK_GET_PARAMETER 0x41

/**
 * @brief Set the device Programming parameters for the current device.
 * These parameters must be set before the starterkit can enter 
 * Programming mode.
 */
#define Cmnd_STK_SET_DEVICE 0x42

/**
 * @brief Set extended programming parameters for the current device.
 */
#define Cmnd_SET_DEVICE_EXT 0x45

/**
 * @brief Load 16-bit address down to starterkit. This command is used to 
 * set the address for the next read or write operation to FLASH or EEPROM. 
 * Must always be used prior to Cmnd_STK_PROG_PAGE or Cmnd_STK_READ_PAGE.
 */
#define Cmnd_STK_LOAD_ADDRESS 0x55

/**
 * @brief Universal command is used to send a generic 32-bit data/command 
 * stream directly to the SPI interface of the current device.
 * Shifting data into the SPI interface at the same time shifts data 
 * out of the SPI interface. The response of the last eight bits that are
 * shifted out are returned.
 */
#define Cmnd_STK_UNIVERSAL 0x56

/**
 * @brief Load 16-bit address down to starterkit.
 * This command is used to set the address for the
 * next read or write operation to FLASH or EEPROM. 
 * Must always be used prior to Cmnd_STK_PROG_PAGE or Cmnd_STK_READ_PAGE.
 */
#define Cmnd_STK_PROG_PAGE 0x64

/**
 * @brief Read a block of data from FLASH or EEPROM 
 * of the current device.
 * The data block size should not be larger than 256 bytes.
 */
#define Cmnd_STK_READ_PAGE 0x74

/**
 * @brief Read signature bytes.
 */
#define Cmnd_STK_READ_SIGN 0x75

/**
 * @brief Leave programming mode.
 */
#define Cmnd_STK_LEAVE_PROGMODE 0x51


#define Resp_STK_OK 0x10
#define Resp_STK_INSYNC 0x14
#define Resp_STK_NOSYNC 0x15
#define Resp_STK_FAILED 0x11

#define Sync_CRC_EOP 0x20

#define Parm_STK_SW_MAJOR 0x81
#define Parm_STK_SW_MINOR 0x82

#endif // COMMAND_H