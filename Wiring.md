# Wiring between Teensy 3.0 and ADIS16460 breakout board

## Links (working as of 30 November 2017)

[ADIS16460 Website](http://www.analog.com/en/products/mems/inertial-measurement-units/adis16460.html)

[ADIS16460 Datasheet](http://www.analog.com/media/en/technical-documentation/data-sheets/ADIS16460.pdf)

[ADIS16460 Breakout Board](https://wiki.analog.com/resources/eval/user-guides/inertial-mems/imu/adis16imu4-pcb)

[Teensy 3.2](https://www.pjrc.com/store/teensy32.html)

## Teensy Layout

![Layout of Teensy 3.2](https://www.pjrc.com/store/teensy32b.jpg)

## ADIS16460 Breakout Board Layout

![Layout of Breakout Board](https://wiki.analog.com/_media/resources/eval/user-guides/inertial-mems/imu/adis16imu4_pcb_wikiguide_design_00.png?w=500&tok=26e7e5)

## ADIS16460 Breakout Schematic

![Schematic of Breakout Board](https://wiki.analog.com/_media/resources/eval/user-guides/inertial-mems/imu/adis16imu4_pcb_wikiguide_design_01.png?w=500&tok=4d070c)

## Connection Table 

| Teensy Pin <br> (Solder Direct) | ADIS16460 <br> (2x7 socket, 1mm spacing)  | ADIS16460 Breakout <br>(2×8 socket, 2mm spacing)|
| ---------- | ------------- | ------------------ |
| 10 (CS)    | 6 (SS_B)      | 3  |
| 13 (SCK)   | 3 (SCK)       | 2  |
| 11 (MOSI)  | 5 (DIN)       | 6  |
| 12 (MISO)  | 4 (DOUT)      | 4  |
| 21 (A7)    | 1 (DR)        | 13 | 
| 22 (A8)    | 2 (SYNC)      | 14 |
| 23 (A9)    | 8 (RST)       | 1  |
| Ground     | 13 (GND)	     | 7, 8, 9 |
| 3.3V       | 11 (VDD)      | 10, 11, 12 |

