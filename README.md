# AD7173-Arduino
Analog Devices AD7173 analog digital converter Arduino library

This library is developed for AD7173 to be used with Brain-Duino and therefore implements only basic functionality. Find more information @ http://brain-duino.com

For Brain-Duino we use the following setup, meaning this is the most tested setup for this library:

* 1007 data rate
* internal clock
* continuous conversion mode
* 4 analog inputs, 2 bipolar channels

```c
AD7173.set_clock_mode(INTERNAL_CLOCK);
AD7173.set_data_rate(FILTER0, SPS_1007);
AD7173.setup_channel(CH0, true, AIN8, AIN9);
AD7173.setup_channel(CH1, true, AIN10, AIN11); 
AD7173.set_data_mode(CONTINUOUS_CONVERSION_MODE);
```