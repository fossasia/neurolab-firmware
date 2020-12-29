# Neurolab Firmware

Repository for firmware of Neurolab Open Hardware Platform.

[![Build Status](https://travis-ci.org/fossasia/neurolab-firmware.svg?branch=master)](https://travis-ci.org/fossasia/neurolab-firmware)
[![Gitter](https://badges.gitter.im/fossasia/neurolab.svg)](https://gitter.im/fossasia/neurolab?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Mailing List](https://img.shields.io/badge/Mailing%20List-FOSSASIA-blue.svg)](https://groups.google.com/forum/#!forum/pslab-fossasia)
[![Twitter Follow](https://img.shields.io/twitter/follow/pslabio.svg?style=social&label=Follow&maxAge=2592000?style=flat-square)](https://twitter.com/pslabio)

We are developing a neuro-device as a headband with integrated electronics. This repository holds the firmware for the Neurolab Hardware. The initial version of the firmware is based on the original AD7173-Arduino library of the Brain-Duino project.

## Buy

* You can get the device in future from the [FOSSASIA Shop](https://fossasia.com).
* More resellers will be listed on the [PSLab website](https://pslab.io/shop/).

## Communication

* The Neurolab [chat channel is on Gitter](https://gitter.im/fossasia/neurolab).
* Please also join us on the [Mailing List](https://groups.google.com/forum/#!forum/pslab-fossasia).

## Goals of Neurolab

The goal of the Neurolab project is to develop an easy to use open hardware measurement headset device for brain waves that can be plugged into an Android smartphone and a software application and enables us to understand our brains better.

Our brains communicate through neurotransmitters and their activity emits electricity. The neuroheadset measures that electricity on the skin of the forehead and the software processes the signal so that it can translated into a visual or auditory representation. The data that can be collected can be analysed to identify mental health, stress, relaxation and even diseases like Alzheimer. 

Current devices in the medical industry are usually not accessible by doctors due to their high pricing. They are also complicated to use. The idea of the device is to integrate it into a headband and focus and focus on signals that can be obtained through the frontal lobe.

A difference to existing projects like OpenBCI is that it will not be necessary to 3D print large headsets. Instead we are focusing on creating a device that collects as much data as possible through the forehead. To achieve this goal we are using high-grade sensors and flexible electronics.

## Setup

* 1007 Data Rate
* External Crystal
* Continuous Conversion Mode
* 4 Analog Inputs, 2 Bipolar Channels

```c
AD7173.set_channel_config(CH0, true, SETUP0, AIN8, AIN9);
AD7173.set_channel_config(CH1, true, SETUP0, AIN10, AIN11);
AD7173.set_setup_config(SETUP0, BIPOLAR);
AD7173.set_filter_config(FILTER0, SPS_1007);
AD7173.set_adc_mode_config(CONTINUOUS_CONVERSION_MODE, EXTERNAL_CRYSTAL);
```

## License

This development of the files in this project are licensed under the Apache License 2.0 license. Some older files are under a Creative Commons license, other specific licenses are mentioned in the respective files. A copy of the [LICENSE Agreement](LICENSE) is to be present along with the source code. To obtain the software under a different license, please contact FOSSASIA or the relevant contributors.
