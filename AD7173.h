/*
===================================================================================
library to control the AD7173 ADC

							  G    A    A    A    A    A    A
					R    R    P    I    I    I    I    I    I    A
					E    E    I    N    N    N    N    N    N    I
					F    F    O    1    1    1    1    1    1    N
					+    -    3    5    4    3    2    1    0    9
					|    |    |    |    |    |    |    |    |    |
				_________________________________________________________
			  /    40.  39.  38.  37.  36.  35.  34.  33.  32.  31.     |
			 |                                                          |
	 AIN16 --| 1.                                                   30. |-- AIN8
AIN0/REF2- --| 2.                                                   29. |-- AIN7
AIN1/REF2+ --| 3.                                                   28. |-- AIN6
	  AIN2 --| 4.                                                   27. |-- AIN5
	  AIN3 --| 5.                                                   26. |-- AIN4
	REFOUT --| 6.                                                   25. |-- GPIO2
   REGCAPA --| 7.                                                   24. |-- GPIO1
	  AVSS --| 8.                                                   23. |-- GPIO0
	 AVDD1 --| 9.                                                   22. |-- REGCAPD
	 AVDD2 --| 10.                                                  21. |-- DGND
			 |                                                          |
			 |     11.  12.  13.  14.  15.  16.  17.  18.  19.  20.     |
			 |__________________________________________________________|
					|    |    |    |    |    |    |    |    |    |
					P    X    X    D    D    S    C    E    S    I
					D    T    T    O    I    C    S    R    Y    O
					S    A    A    U    N    L         R    N    V
					W    L    L    T         K         O    C    D
					1    2                             R         D
						 /
						 C
						 L
						 K
						 I
						 O
===================================================================================
*/

#ifndef _AD7173_H_INCLUDED
#define _AD7173_H_INCLUDED

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SPI.h"

/* enable or disable debug */
#define DEBUG_ENABLED 0

/* delay for reading and writing registers  */
#define READ_WRITE_DELAY 1

/* registers */
typedef enum {
	/* other ADC registers */
	COMMS_REG = 0x00,
	STATUS_REG = 0x00,
	ADCMODE_REG = 0x01,
	IFMODE_REG = 0x02,
	REGCHECK_REG = 0x03,
	DATA_REG = 0x04,
	GPIOCON_REG = 0x06,
	ID_REG = 0x07,
	/* ADC channel registers */
	CH0 = 0x10,
	CH1 = 0x11,
	CH2 = 0x12,
	CH3 = 0x13,
	CH4 = 0x14,
	CH5 = 0x15,
	CH6 = 0x16,
	CH7 = 0x17,
	CH8 = 0x18,
	CH9 = 0x19,
	CH10 = 0x1A,
	CH11 = 0x1B,
	CH12 = 0x1C,
	CH13 = 0x1D,
	CH14 = 0x1E,
	CH15 = 0x1F,
	/* ADC setup config register */
	SETUP0 = 0x20,
	SETUP1 = 0x21,
	SETUP2 = 0x22,
	SETUP3 = 0x23,
	SETUP4 = 0x24,
	SETUP5 = 0x25,
	SETUP6 = 0x26,
	SETUP7 = 0x27,
	/* ADC filter config registers */
	FILTER0 = 0x28,
	FILTER1 = 0x29,
	FILTER2 = 0x2A,
	FILTER3 = 0x2B,
	FILTER4 = 0x2C,
	FILTER5 = 0x2D,
	FILTER6 = 0x2E,
	FILTER7 = 0x2F,
	/* ADC offset registers */
	OFFSET0 = 0x30,
	OFFSET1 = 0x31,
	OFFSET2 = 0x32,
	OFFSET3 = 0x33,
	OFFSET4 = 0x34,
	OFFSET5 = 0x35,
	OFFSET6 = 0x36,
	OFFSET7 = 0x37,
	/* ADC gain registers */
	GAIN0 = 0x38,
	GAIN1 = 0x39,
	GAIN2 = 0x3A,
	GAIN3 = 0x3B,
	GAIN4 = 0x3C,
	GAIN5 = 0x3D,
	GAIN6 = 0x3E,
	GAIN7 = 0x3F
} adc7173_register_t;

/* ADC analog inputs */
typedef enum {
	AIN0 = 0x00,
	AIN1 = 0x01,
	AIN2 = 0x02,
	AIN3 = 0x03,
	AIN4 = 0x04,
	AIN5 = 0x05,
	AIN6 = 0x06,
	AIN7 = 0x07,
	AIN8 = 0x08,
	AIN9 = 0x09,
	AIN10 = 0x0A,
	AIN11 = 0x0B,
	AIN12 = 0x0C,
	AIN13 = 0x0D,
	AIN14 = 0x0E,
	AIN15 = 0x0F,
	AIN16 = 0x10,
	/* other ADC analog inputs */
	TEMP_SENSOR_POS = 0x11,
	TEMP_SENSOR_NEG = 0x12,
	REF_POS = 0x15,
	REF_NEG = 0x16
} analog_input_t;

/* ADC filter data rates (samples per second) */
/* some are are rounded down, the data rates are for sinc5 + sinc1 */
typedef enum {
	SPS_31250 = 0x00,
	SPS_15625 = 0x06,
	SPS_10417 = 0x07,
	SPS_5208 = 0x08,
	SPS_2597 = 0x09,
	SPS_1007 = 0x0A,
	SPS_503 = 0x0B,
	SPS_381 = 0x0C,
	SPS_200 = 0x0D,
	SPS_100 = 0x0E,
	SPS_59 = 0x0F,
	SPS_49 = 0x10,
	SPS_20 = 0x11,
	SPS_16 = 0x12,
	SPS_10 = 0x13,
	SPS_5 = 0x14,
	SPS_2 = 0x15,
	SPS_1 = 0x16
} data_rate_t;

/* ADC setup coding modes */
typedef enum {
	UNIPOLAR = 0x00,
	BIPOLAR = 0x01
} coding_mode_t;

/* ADC data conversion modes */
typedef enum {
	CONTINUOUS_CONVERSION_MODE = 0x00,
	SINGLE_CONVERSION_MODE = 0x01,
	CONTINUOUS_READ_MODE
} data_mode_t;

/* clock mode */
/*
	00 Internal oscillator
	01 Internal oscillator output on XTAL2/CLKIO pin
	10 External clock input on XTAL2/CLKIO pin
	11 External crystal on XTAL1 and XTAL2/CLKIO pins
*/
typedef enum {
	INTERNAL_CLOCK = 0x00,
	INTERNAL_CLOCK_OUTPUT = 0x01,
	EXTERNAL_CLOCK_INPUT = 0x02,
	EXTERNAL_CRYSTAL = 0x03
} clock_mode_t;

/* ADC data ready indicator */
#define DATA_READY digitalRead(MISO) == LOW

class AD7173Class {
public:
	/*
	=====================================
	constructor
	set default ADC setup coding mode
	set default ADC data conversion mode
	=====================================
	*/
	AD7173Class() : m_data_mode(CONTINUOUS_CONVERSION_MODE) {
		/* ... */
	}

	/*
	============================================
	initializes the SPI connection with the ADC
	============================================
	*/
	void init();

	/*
	==================================================
	cancels the current transaction to resync the ADC
	==================================================
	*/
	void sync();

	/*
	==============================================
	resets the ADC registers to the default state
	==============================================
	*/
	void reset();

	/*
	=============================================
	gets the current conversion results channel
	@param byte - current data channel
	@return int - error code
	=============================================
	*/
	int get_current_data_channel(adc7173_register_t &);

	/*
	================================
	sets the ADC mode configuration
	@param clock_mode_t - clock mode
	@return int - error code
	================================
	*/
	int set_adc_mode_config(data_mode_t, clock_mode_t);

	/*
	==================================================
	sets the ADC interface mode configuration
	@param bool - ensable/disable continuous read mode
	@return int - error code
	==================================================
	*/
	int set_interface_mode_config(bool);

	/*
	==========================================
	gets the ADC conversion result
	@return byte[] - the ADC conversion result
	==========================================
	*/
	int get_data(byte *);

	/*
	============================================
	checks the ID register of the ADC
	@return bool - true if the ADC ID valid
	============================================
	*/
	bool is_valid_id();

	/*
	=====================================
	configures ADC channels
	@param byte - channel register
	@param bool - enable/disable channel
	@param byte - setup register
	@param byte - analog input positive
	@param byte - analog input negative
	@return int - error code
	=====================================
	*/
	int set_channel_config(adc7173_register_t, bool, adc7173_register_t, analog_input_t, analog_input_t);

	/*
	==================================
	sets the ADC setups coding mode
	@param byte - setup register
	@param condig_mode_t - coding mode
	@return int - error code
	==================================
	*/
	int set_setup_config(adc7173_register_t, coding_mode_t);

	/*
	==========================================
	sets the ADC filters data conversion rate
	@param byte - filter register
	@param byte - data rate
	@return int - error code
	==========================================
	*/
	int set_filter_config(adc7173_register_t, data_rate_t);

	/*
	======================================
	sets the ADC offset compensation value
	@param byte - offset register
	@param uint32_t - offset value
	@return int - error code
	======================================
	*/
	int set_offset_config(adc7173_register_t, uint32_t);

private:
	/* ADC data mode */
	data_mode_t m_data_mode;

	/*
	===========================
	print bytes in nice format
	@param byte - byte to print
	===========================
	*/
	void print_byte(byte);

	/*
	=======================================
	set a desired ADC register value
	@param byte - the register to set
	@param  byte[] - the bytes to set
	@param int - the length of bytes to set
	=======================================
	*/
	int set_register(adc7173_register_t, byte *, int);

	/*
	=======================================
	get a desired ADC register value
	@param byte - the register to get
	@param int - the length of bytes to get
	@return byte[] - the ADC register value
	=======================================
	*/
	int get_register(adc7173_register_t, byte *, int);
};

extern AD7173Class AD7173;

#endif
