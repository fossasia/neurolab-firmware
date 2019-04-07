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
          AD7173.init();

        /* sync the ADC */
          AD7173.sync();
      }

    // TO-DO list
    void Neurolab:: updateChannelSettings(void){
      }
    void Neurolab::writeChannelSettings(void){
      }
    void Neurolab::setChannelsToDefault(void){
      }
    void Neurolab::sendChannelData(byte){
      }
    void Neurolab::reportDefaultChannelSettings(void){
      }
    void Neurolab::startStreaming(void){
      }
    void Neurolab::stopStreaming(void){
      }


    //  ADS1299 FUNCITONS
    void Neurolab::initialize_ad(void){
      }
    void Neurolab::printAllRegisters(void){
      }
    void Neurolab::updateADchannelSettings(void){
      }
    void Neurolab::writeADchannelSettings(void){
      }
    void Neurolab::writeADchannelSettings(int){
      }
    void Neurolab::activateChannel(int){
      }
    void Neurolab::activateChannel(int, byte, byte, boolean){
      }
    void Neurolab::deactivateChannel(int){
      }
    void Neurolab::configureInternalTestSignal(byte,byte){
      }
    void Neurolab::reset_ad(void){
      }
    boolean Neurolab::isDataAvailable(void){
      }
    void Neurolab::updateChannelData(void){
      }
    long Neurolab::getChannel(int){
      }
    void Neurolab::putChannel(int, long){
      }
    void Neurolab::update24bitData(void){
      }

    /* 
      Here you can implement other functions related to Neurolab like
      accelerometer, sdcard, wifi module etc..

    */