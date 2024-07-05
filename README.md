# linearScale
Read a Linear (Glass) Scale from Raspberry Pi

This is proof-of-concept code to investigate reading from a glass scale. The code will 
eventually be incorporated into the latheControl repository.

Please note that usage of the pigpio library (which appears to come pre-installed on
Raspberry Pis) requires root, so the application needs to be run with `sudo`

##Connection

The glass scales (at least mine) have four connections, +5.0v, GND, pin A and pin B.

The code assumes pinA is connected to GPIO pin 20 and pinB to GPIO pin 21.
