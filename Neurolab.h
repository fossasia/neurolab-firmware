#ifndef ____Neurolab__
#define ____Neurolab__

#include "AD7173.h"
#include "definitions.h"
class Neurolab{

public:
  
    AD7173Class ads;
  
    /* VARIABLES */
    int outputType;

    /* BOARD WIDE FUNCTIONS
       TO-DO list           */
    void initialize(void);
    void updateChannelSettings(void);
    void writeChannelSettings(void);
    void setChannelsToDefault(void);
    void sendChannelData(byte);
    void reportDefaultChannelSettings(void);
    void startStreaming(void);
    void stopStreaming(void);

    /*  ADS1299 FUNCITONS */
	/*
	============================================
	initializes the SPI connection with the ADC
	============================================
	*/
    void initialize_adc(void);

	/*
	==============================================
	resets the ADC registers to the default state
	==============================================
	*/
	void reset_adc(void);

	/*
	==================================================
	cancels the current transaction to resync the ADC
	==================================================
	*/
    void sync_adc(void);

	/*
	=============================================
	gets the current conversion results channel
	@param byte - current data channel
	@return int - error code
	=============================================
	*/
    void get_current_adc_data_channel(adc7173_register_t &);

	/*
	================================
	sets the ADC mode configuration
	@param clock_mode_t - clock mode
	@return int - error code
	================================
	*/
    void set_adc_mode_config(data_mode_t, clock_mode_t);

	/*
	==================================================
	sets the ADC interface mode configuration
	@param bool - ensable/disable continuous read mode
	@return int - error code
	==================================================
	*/
    void set_adc_interface_mode_config(bool, bool);

	/*
	==========================================
	gets the ADC conversion result
	@return byte[] - the ADC conversion result
	==========================================
	*/
    void get_adc_data(byte *);

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
    void set_adc_channel_config(adc7173_register_t, bool, adc7173_register_t, analog_input_t, analog_input_t);

	/*
	==================================
	sets the ADC setups coding mode
	@param byte - setup register
	@param condig_mode_t - coding mode
	@return int - error code
	==================================
	*/
    void set_adc_setup_config(adc7173_register_t, coding_mode_t);

	/*
	==========================================
	sets the ADC filters data conversion rate
	@param byte - filter register
	@param byte - data rate
	@return int - error code
	==========================================
	*/
    void set_adc_filter_config(adc7173_register_t, data_rate_t);

	/*
	======================================
	sets the ADC offset compensation value
	@param byte - offset register
	@param uint32_t - offset value
	@return int - error code
	======================================
	*/
    void set_adc_gain_registers(adc7173_register_t, uint32_t);

    /* 
      Here you can implement other functions related to Neurolab like
      accelerometer, sdcard, wifi module etc..

    */
    
};

#endif