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
#include "definitions.h"

/* enable or disable debug */
#define DEBUG_ENABLED 0

/* delay for reading and writing registers  */
#define READ_WRITE_DELAY 1

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
	int set_interface_mode_config(bool, bool);

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
	
	/*
	======================================
	sets the ADC gain compensation value
	@param byte - gain register
	@param uint32_t - gain value
	@return int - error code
	======================================
	*/
	int set_gain_registers(adc7173_register_t, uint32_t);
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
