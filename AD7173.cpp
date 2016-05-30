/*
=================================
library to control the AD7173 ADC
=================================
*/
#include "AD7173.h"

AD7173Class AD7173;

void AD7173Class::init() {
	/* initiate SPI communication */
	SPI.begin();
	/* use SPI mode 3 */
	SPI.setDataMode(SPI_MODE3);
}

void AD7173Class::reset() {
	/* sending at least 64 high bits returns ADC to default state */
	for (int i = 0; i < 8; i++) {
		SPI.transfer(0xFF);
	}
}

void AD7173Class::sync() {
	/* toggle the chip select */
	digitalWrite(SS, HIGH);
	delay(10);
	digitalWrite(SS, LOW);
}

void AD7173Class::print_byte(byte value) {
	char format[10];
	sprintf(format, "0x%.2X ", value);
	Serial.print(format);
}

int AD7173Class::set_register(register_t reg, byte *value, int value_len) {
	/* send communication register id 0x00 */
	SPI.transfer(0x00);
	/* send write command to the desired register 0x00 - 0xFF */
	SPI.transfer(0x00 | reg);
	/* send the desired amount of bytes */
	for (int i = 0; i < value_len; i++) {
		SPI.transfer(value[i]);
	}
	/* when debug enabled */
	if (DEBUG_ENABLED) {
		Serial.print("set_register: set [ ");
		for (int i = 0; i < value_len; i++) {
			this->print_byte(value[i]);
		}
		Serial.print("] to reg [ ");
		this->print_byte(reg);
		Serial.println("]");
	}
	/* TODO: find out correct delay */
	delay(READ_WRITE_DELAY);
	/* return error code */
	return 0;
}

int AD7173Class::get_register(register_t reg, byte *value, int value_len) {
	/* send communication register id 0x00 */
	SPI.transfer(0x00);
	/* send read command to the desired register 0x00 - 0xFF */
	SPI.transfer(0x40 | reg);
	/* receive the desired amount of bytes */
	for (int i = 0; i < value_len; i++) {
		value[i] = SPI.transfer(0x00);
	}
	/* when debug enabled */
	if (DEBUG_ENABLED) {
		Serial.print("get_register: got [ ");
		for (int i = 0; i < value_len; i++) {
			this->print_byte(value[i]);
		}
		Serial.print("] from reg [ ");
		this->print_byte(reg);
		Serial.println(" ]");
	}
	/* TODO: find out correct delay */
	delay(READ_WRITE_DELAY);
	/* return error code */
	return 0;
}

int AD7173Class::get_current_data_channel(register_t &channel) {
	byte value[1];
	/* read ADC status register */
	this->get_register(STATUS_REG, value, 1);
	/* assign to return channel register value */
	channel = (register_t) (value[0] & 0x0F);
	/* return error code */
	return 0;
}

int AD7173Class::set_adc_mode_config(data_mode_t data_mode, clock_mode_t clock_mode) {
	/* prepare the configuration value */
	/* REF_EN [15], RESERVED [14], SING_CYC [13], RESERVED [12:11], DELAY [10:8], RESERVED [7], MODE [6:4], CLOCKSEL [3:2], RESERED [1:0] */
	byte value[2];
	value[0] = 0x00;
	value[1] = (data_mode << 4) | (clock_mode << 2);

	/* update the desired adc_mode configuration */
	this->set_register(ADCMODE_REG, value, 2);

	/* update the data mode */
	this->m_data_mode = data_mode;

	/* return error code */
	return 0;
}

int AD7173Class::set_interface_mode_config(bool continuous_read) {
	/* prepare the configuration value */
	/* RESERVED [15:13], ALT_SYNC [12], IOSTRENGTH [11], HIDE_DELAY [10], RESERVED [9], DOUT_RESET [8], CONTREAD [7], DATA_STAT [6], REG_CHECK [5], RESERVED [4], CRC_EN [3:2], RESERVED [1], WL16 [0] */
	byte value[2];
	value[0] = 0x00;
	value[1] = (continuous_read << 7);

	/* update the desired interface_mode configuration */
	this->set_register(IFMODE_REG, value, 2);

	/* update the data mode */
	this->m_data_mode = CONTINUOUS_READ_MODE;

	/* return error code */
	return 0;
}

int AD7173Class::get_data(byte *value) {
	/* when not in continuous read mode, send the read command */
	if (this->m_data_mode != CONTINUOUS_READ_MODE) {
		/* send communication register id 0x00 */
		SPI.transfer(0x00);
		/* send read command 0x40 to the data register 0x04 */
		SPI.transfer(0x40 | DATA_REG);
	}
	/* get the ADC conversion result (24 bits) */
	value[0] = SPI.transfer(0x00);
	value[1] = SPI.transfer(0x00);
	value[2] = SPI.transfer(0x00);

	/* when debug enabled */
	if (DEBUG_ENABLED) {
		Serial.print("get_data: read [ ");
		this->print_byte(value[0]);
		this->print_byte(value[1]);
		this->print_byte(value[2]);
		Serial.println("] from reg [ 0x04 ]");
	}
	/* return error code */
	return 0;
}

bool AD7173Class::is_valid_id() {
	byte id[2];
	 /* read the ADC device ID */
	this->get_register(ID_REG, id, 2);
	/* check if the id matches 0x30DX, where X is don't care */
	id[1] &= 0xF0;
	bool valid_id = id[0] == 0x30 && id[1] == 0xD0;

	/* when debug enabled */
	if (DEBUG_ENABLED) {
		if (valid_id) {
			Serial.println("init: ADC device ID is valid :)");
		} else {
			Serial.print("init: ADC device ID is invalid :( [ ");
			this->print_byte(id[0]);
			this->print_byte(id[1]);
			Serial.print(" ]");
			Serial.println();
		}
	}
	/* return validity of ADC device ID */
	return valid_id;
}

int AD7173Class::set_channel_config(register_t channel, bool enable, register_t setup, analog_input_t ain_pos, analog_input_t ain_neg) {
	/* prepare the configuration value */
	/* CH_EN0 [15], SETUP_SEL0 [14:12], RESERVED [11:10], AINPOS0 [9:5], AINNEG0 [4:0] */
	byte value[2];
	value[0] = (enable << 7) | (setup << 4) | (ain_pos >> 3);
	value[1] = (ain_pos << 5) | ain_neg;

	/* update the desired channel configuration */
	this->set_register(channel, value, 2);

	/* return error code */
	return 0;
}

int AD7173Class::set_setup_config(register_t setup, coding_mode_t coding_mode) {
	/* prepare the configuration value */
	byte value[2];
	value[0] = (coding_mode << 4);
	value[1] = 0x00;

	/* update the desired setup configuration */
	this->set_register(setup, value, 2);

	/* update the coding mode */
	this->m_coding_mode = coding_mode;

	/* return error code */
	return 0;
}

int AD7173Class::set_filter_config(register_t filter, bool ac_rejection, data_rate_t data_rate) {
	/* prepare the configuration value */
	byte value[2];
	/* SINC3_MAP0 [15], RESERVED [14:12], ENHFILTEN0 [11], ENHFILT0 [10:8], RESERVED [7], ORDER0 [6:5], ORD0 [4:0] */
	value[0] = (ac_rejection << 3);
	value[1] = data_rate;

	/* update the desired filter configuration */
	this->set_register(filter, value, 2);

	/* return error code */
	return 0;
}