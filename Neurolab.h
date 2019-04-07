#ifndef ____Neurolab__
#define ____Neurolab__

#include "AD7173.h"

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
    void initialize_ad(void);
    void printAllRegisters(void); 
    void updateADchannelSettings(void);
    void writeADchannelSettings(void); 
    void writeADchannelSettings(int);
    void activateChannel(int);
    void activateChannel(int, byte, byte, boolean);
    void deactivateChannel(int);
    void configureInternalTestSignal(byte,byte);
    void reset_ad(void);
    boolean isDataAvailable(void);
    void updateChannelData(void);
    long getChannel(int);
    void putChannel(int, long);
    void update24bitData(void);
    
    /* 
      Here you can implement other functions related to Neurolab like
      accelerometer, sdcard, wifi module etc..

    */
};



#endif