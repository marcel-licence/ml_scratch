<h1 align="center">ml_scratch</h1>
<h3 align="center">scratch disc Arduino project</h3>  
<p align="center"> 
  <img src="img/splash.jpg" alt="project picture" width="480px" height="270px"><br>
  <a href="https://youtu.be/Ml6VrlV3hvk">link to the video of the origin</a>
</p>

## Introduction

This example demonstrates a simple scratch controller using the AS5600 sensor for rotational input (a disc or similar mechanism is recommended) via I2C. It allows direct control over the playback of a selected audio sample for scratching. The example does not require additional RAM, as all samples are stored and played back directly from flash memory, ensuring maximum compatibility.

## Supported Platforms

Currently, only the ESP32 platform is supported. Other platforms may be added in the future.

## Features

-   Sample storage and playback directly from flash memory
-   16-bit audio playback
-   Precise control using the AS5600 sensor

## Future Improvements

-   Support for stereo playback
-   Enhanced audio quality by reducing aliasing
-   Integration of control buttons
-   ADC input as a fader for a better scratching experience

## Support & Donations

If you appreciate the work done on this project and would like to support its development, I would be more than happy to accept donations!

For more information on how to donate, please send an email to:

📧 **marcel.licence.o@gmail.com**

Thank you for your support!
