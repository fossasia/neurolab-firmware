/*
=================================================
example to configure and get data from AD7173 ADC
=================================================
*/
#include <SPI.h>
#include <AD7173.h>

void setup() {
	/* initiate serial communication */
	Serial.begin(115200);

	/* initialize SPI connection to the ADC */
	AD7173.init();

	/* sync the ADC */
	AD7173.sync();

	/* check the ID register of the ADC */
	boolean validId = AD7173.checkId();
	if (validId) Serial.println("AD7173 ID is valid");
	else Serial.println("AD7173 ID is invalid");

	/* set ADC input channel configuration */
	/* enable channel 0 and channel 1 and connect each to 2 analog inputs for bipolar input */
	/* CH0 - CH15 */
	/* AIN0 - AIN16, REF_POS, REF_NEG, TEMP_SENSOR_POS, TEMP_SENSOR_NEG */
	AD7173.setup_channel(CH0, true, AIN0, AIN1);
	AD7173.setup_channel(CH1, true, AIN2, AIN3);

	/* set the ADC filter samplingrate to 1007 Hz */
	/* FILTER0 - FILTER7 */
	/* SPS_1, SPS_2, SPS_5, SPS_10, SPS_16, SPS_20, SPS_50, SPS_60, SPS_100, SPS_200 */
	/* SPS_381, SPS_504, SPS_1007, SPS_2597, SPS_5208, SPS_10417, SPS_15625, SPS_31250 */
	AD7173.set_data_rate(FILTER0, SPS_1007);

	/* set the ADC setup coding mode to BIPLOAR output */
	/* SETUP0 - SETUP7 */
	/* BIPOLAR, UNIPOLAR */
	AD7173.set_coding_mode(SETUP0, BIPOLAR);

	/* set the ADC data mode */
	/* CONTINUOUS_READ_MODE, SINGLE_CONVERSION_MODE, CONTINUOUS_CONVERSION_MODE */
	AD7173.set_data_mode(CONTINUOUS_CONVERSION_MODE);

	/* set the ADC clock mode */
	/* INTERNAL_CLOCK, INTERNAL_CLOCK_OUTPUT, EXTERNAL_CLOCK_INPUT, EXTERNAL_CRYSTAL */
	AD7173.set_clock_mode(INTERNAL_CLOCK);

	/* wait for ADC */
	delay(10);
}

/* ADC conversion data */
byte data[3];

void loop() {
	/* when ADC conversion is finished */
	if (DATA_READY) {
		/* get ADC conversion result */
		AD7173.get_data(data);

		/* send result via serial */
		Serial.print(data[0], HEX);
		Serial.print(data[1], HEX);
		Serial.println(data[2], HEX);
		delay(100);
	}
}