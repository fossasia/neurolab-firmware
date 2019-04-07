#ifndef ____Neurolab__
#define ____Neurolab__

#include "AD7173.h"
#include "definitions.h"
class Neurolab{

  public:
  
    AD7173Class ads;
  
    // VARIABLES
    int outputType;
    int auxData[3];
    boolean useAux;

    // BOARD WIDE FUNCTIONS
    void initialize(void);
    void updateChannelSettings(void);
    void writeChannelSettings(void);
    void setChannelsToDefault(void);
    void sendChannelData(byte);
    void reportDefaultChannelSettings(void);
    void startStreaming(void);
    void stopStreaming(void);


    //  ADS1299 FUNCITONS
    void initialize_adc(void);
    void reset_adc(void);
    void sync_adc(void);
    void get_current_adc_data_channel(adc7173_register_t &);
    void set_adc_mode_config(data_mode_t , clock_mode_t );
    void set_adc_interface_mode_config(bool , bool );
    void get_adc_data(byte *);
    void set_adc_channel_config(adc7173_register_t,bool,adc7173_register_t ,analog_input_t ,analog_input_t );
    void set_adc_setup_config(adc7173_register_t , coding_mode_t );
    void set_adc_filter_config(adc7173_register_t , data_rate_t );
    void set_adc_gain_registers(adc7173_register_t , uint32_t );


    /* 
      Here you can implement other functions related to Neurolab like
      accelerometer, sdcard, wifi module etc..

    */
    
};



#endif
