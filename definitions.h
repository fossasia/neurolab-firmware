#ifndef ____definitions__
#define ____definitions__


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

#endif