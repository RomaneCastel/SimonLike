#include "lpc17xx_i2c.h"
#include "constantes.h"

void init_i2c_eeprom(LPC_I2C_TypeDef* I2Cx);
Status i2c_eeprom_write(uint16_t, uint8_t *, int);
Status i2c_eeprom_read(uint16_t, uint8_t* data, int);
