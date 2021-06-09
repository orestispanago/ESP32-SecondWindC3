### ESP32-SecondWindC3

Reads [Second Wind C3 anemometer](http://www.smewind.com/wb/media/rsrc/Anemometer%20Second%20Wind_eng.pdf) using the built-in ADC.

The anemometer output is a sine wave with a frequency proportional to cup rotational speeed. 

The board's ADC cannot measure negative values, so the AC wave is clipped.

Non-zero ```analogRead()``` values are counted as pulses. A 20 millis delay is necessary to avoid mulitple counts that may occur on one pulse.

The task runs in parallel with the main loop, on the second core. 