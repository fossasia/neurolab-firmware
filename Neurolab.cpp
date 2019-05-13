#include "Neurolab.h"

AD7173Class ads;
  
// VARIABLES
int  outputType;
int auxData[3];
boolean useAux;

// BOARD WIDE FUNCTIONS
void Neurolab::initialize(void){
    /* initiate serial communication */
    Serial.begin(230400);
        
    /* initialize SPI connection to the ADC */
    initialize_adc();

    /* sync the ADC */
    sync_adc();
}

/*
==================================================
TO-DO list
==================================================
*/     
void Neurolab::updateChannelSettings(void){
  /* ... */
}

void Neurolab::writeChannelSettings(void){
  /* ... */
}

void Neurolab::setChannelsToDefault(void){
  /* ... */
}

void Neurolab::sendChannelData(byte){
  /* ... */
}

void Neurolab::reportDefaultChannelSettings(void){
  /* ... */
}

void Neurolab::startStreaming(void){
  /* ... */
}

void Neurolab::stopStreaming(void){
  /* ... */
}

/*
==================================================
AD7173 functions
==================================================
*/
void Neurolab::initialize_adc(void){
    /* initialize SPI connection to the ADC */
    AD7173.init();
}

void Neurolab::reset_adc(void){
    /* reset ADC to default */
    AD7173.reset();
}
      
void Neurolab::sync_adc(void){
    /* sync the ADC */
    AD7173.sync();
}

void Neurolab::get_current_adc_data_channel(adc7173_register_t &channel){
    /*gets the current conversion results channel*/
    AD7173.get_current_data_channel(channel);
}
      
void Neurolab::set_adc_mode_config(data_mode_t data_mode, clock_mode_t clock_mode){
    /*sets the ADC mode configuration*/
    AD7173.set_adc_mode_config(data_mode, clock_mode);
}
    
void Neurolab::set_adc_interface_mode_config(bool continuous_read, bool append_status_reg){
    /* sets the ADC interface mode configuration */
    AD7173.set_interface_mode_config(continuous_read, append_status_reg);
}
      
void Neurolab::get_adc_data(byte *value){
    /*gets the ADC conversion result*/
    AD7173.get_data(value);
}

void Neurolab::set_adc_channel_config(adc7173_register_t channel, bool enable, adc7173_register_t setupc, analog_input_t ain_pos, analog_input_t ain_neg){
    /* configures ADC channels */
    AD7173.set_channel_config(channel,enable, setupc, ain_pos, ain_neg);
}
      
void Neurolab::set_adc_setup_config(adc7173_register_t setupc, coding_mode_t coding_mode){
    /*sets the ADC setups coding mode*/
    AD7173.set_setup_config(setupc ,coding_mode);
}
      
void Neurolab::set_adc_filter_config(adc7173_register_t filter, data_rate_t data_rate){
    /*sets the ADC filters data conversion rate*/
    AD7173.set_filter_config(filter, data_rate);
}
      
void Neurolab::set_adc_gain_registers(adc7173_register_t gain, uint32_t gain_value){
    /*sets the ADC gain compensation value*/
    AD7173.set_gain_registers( gain ,gain_value);
}
