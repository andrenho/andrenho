EESchema Schematic File Version 2  date 31/10/2013 17:14:51
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:kicad
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Power Supply AW401"
Date "31 oct 2013"
Rev "1"
Comp "Imperial Engeneering"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AC_POWER P?
U 1 1 5272A003
P 1150 3150
F 0 "P?" H 1150 3700 60  0000 C CNN
F 1 "AC_POWER" H 1200 2550 60  0000 C CNN
F 2 "" H 1150 3150 60  0000 C CNN
F 3 "" H 1150 3150 60  0000 C CNN
F 4 "220V" H 1650 3100 60  0000 C CNN "VOLTAGE"
	1    1150 3150
	-1   0    0    1   
$EndComp
$Comp
L FUSE F?
U 1 1 5272A04C
P 2950 2950
F 0 "F?" H 3050 3000 40  0000 C CNN
F 1 "1A" H 2850 2900 40  0000 C CNN
F 2 "~" H 2950 2950 60  0000 C CNN
F 3 "~" H 2950 2950 60  0000 C CNN
	1    2950 2950
	1    0    0    -1  
$EndComp
$Comp
L DPST SW?
U 1 1 5272A076
P 2200 3150
F 0 "SW?" H 2200 3250 70  0000 C CNN
F 1 "DPST" H 2200 3050 70  0000 C CNN
F 2 "~" H 2200 3150 60  0000 C CNN
F 3 "~" H 2200 3150 60  0000 C CNN
	1    2200 3150
	1    0    0    -1  
$EndComp
$Comp
L SWITCH_INV SW?
U 1 1 5272A090
P 3700 3050
F 0 "SW?" H 3500 3200 50  0000 C CNN
F 1 "V_SELECT" H 3550 2900 50  0000 C CNN
F 2 "~" H 3700 3050 60  0000 C CNN
F 3 "~" H 3700 3050 60  0000 C CNN
	1    3700 3050
	1    0    0    1   
$EndComp
Text Notes 3950 3500 0    60   ~ 0
BLACK
$Comp
L DIODE D?
U 1 1 5272A437
P 5450 2500
F 0 "D?" H 5450 2600 40  0000 C CNN
F 1 "DIODE" H 5450 2400 40  0000 C CNN
F 2 "~" H 5450 2500 60  0000 C CNN
F 3 "~" H 5450 2500 60  0000 C CNN
	1    5450 2500
	1    0    0    -1  
$EndComp
$Comp
L DIODE D?
U 1 1 5272A5A6
P 5650 2700
F 0 "D?" H 5650 2800 40  0000 C CNN
F 1 "DIODE" H 5650 2600 40  0000 C CNN
F 2 "~" H 5650 2700 60  0000 C CNN
F 3 "~" H 5650 2700 60  0000 C CNN
	1    5650 2700
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 5272A5B1
P 5250 2700
F 0 "D?" H 5250 2800 40  0000 C CNN
F 1 "DIODE" H 5250 2600 40  0000 C CNN
F 2 "~" H 5250 2700 60  0000 C CNN
F 3 "~" H 5250 2700 60  0000 C CNN
	1    5250 2700
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 5272A5B7
P 5450 2900
F 0 "D?" H 5450 3000 40  0000 C CNN
F 1 "DIODE" H 5450 2800 40  0000 C CNN
F 2 "~" H 5450 2900 60  0000 C CNN
F 3 "~" H 5450 2900 60  0000 C CNN
	1    5450 2900
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5272A64E
P 6200 3000
F 0 "C?" H 6200 3100 40  0000 L CNN
F 1 "2000uF" H 6206 2915 40  0000 L CNN
F 2 "~" H 6238 2850 30  0000 C CNN
F 3 "~" H 6200 3000 60  0000 C CNN
	1    6200 3000
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5272A6A0
P 6550 3000
F 0 "C?" H 6550 3100 40  0000 L CNN
F 1 "2000uF" H 6556 2915 40  0000 L CNN
F 2 "~" H 6588 2850 30  0000 C CNN
F 3 "~" H 6550 3000 60  0000 C CNN
	1    6550 3000
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5272A6CA
P 6950 3000
F 0 "R?" V 7030 3000 40  0000 C CNN
F 1 "1K" V 6957 3001 40  0000 C CNN
F 2 "~" V 6880 3000 30  0000 C CNN
F 3 "~" H 6950 3000 30  0000 C CNN
	1    6950 3000
	1    0    0    -1  
$EndComp
$Comp
L LM317 U?
U 1 1 5272A7D2
P 7750 2650
F 0 "U?" H 7750 2950 60  0000 C CNN
F 1 "LM317" H 7800 2400 60  0000 L CNN
F 2 "~" H 7750 2650 60  0000 C CNN
F 3 "~" H 7750 2650 60  0000 C CNN
	1    7750 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2500 5000 2950
Wire Wire Line
	5000 2500 5250 2500
Wire Wire Line
	5650 2900 5650 3350
Wire Wire Line
	5650 3350 5000 3350
Wire Wire Line
	5650 2500 7350 2500
Wire Wire Line
	5250 2900 5250 3500
Wire Wire Line
	5250 3500 9350 3500
Wire Wire Line
	6200 2800 6200 2500
Connection ~ 6200 2500
Wire Wire Line
	6200 3200 6200 3500
Connection ~ 6200 3500
Wire Wire Line
	6550 2800 6550 2500
Connection ~ 6550 2500
Wire Wire Line
	6550 3200 6550 3500
Connection ~ 6550 3500
Wire Wire Line
	6950 2150 6950 2750
Connection ~ 6950 2500
Wire Wire Line
	6950 3250 6950 3500
Connection ~ 6950 3500
$Comp
L POT RV?
U 1 1 5272A84F
P 7750 3250
F 0 "RV?" H 7750 3150 50  0000 C CNN
F 1 "POT" H 7750 3250 50  0000 C CNN
F 2 "~" H 7750 3250 60  0000 C CNN
F 3 "~" H 7750 3250 60  0000 C CNN
	1    7750 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7750 3500 7750 3500
Connection ~ 7750 3500
$Comp
L R R?
U 1 1 5272A87C
P 8250 2750
F 0 "R?" V 8330 2750 40  0000 C CNN
F 1 "R" V 8257 2751 40  0000 C CNN
F 2 "~" V 8180 2750 30  0000 C CNN
F 3 "~" H 8250 2750 30  0000 C CNN
	1    8250 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3000 8250 3000
Wire Wire Line
	8150 2500 9900 2500
Connection ~ 8250 2500
$Comp
L TRANSFO4 T?
U 1 1 5272A9B8
P 4600 3150
F 0 "T?" H 4600 3400 70  0000 C CNN
F 1 "TRANSFO4" H 4600 2850 70  0000 C CNN
F 2 "~" H 4600 3150 60  0000 C CNN
F 3 "~" H 4600 3150 60  0000 C CNN
	1    4600 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3350 4200 3350
Wire Wire Line
	3200 3050 3200 2950
$Comp
L VOLT-AMP U?
U 1 1 5272ABE9
P 9000 2950
F 0 "U?" H 9200 3350 60  0000 C CNN
F 1 "VOLT-AMP" H 9000 2500 60  0000 C CNN
F 2 "" H 9000 2950 60  0000 C CNN
F 3 "" H 9000 2950 60  0000 C CNN
	1    9000 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2750 9450 2750
Wire Wire Line
	9450 2750 9450 2500
Connection ~ 9450 2500
Wire Wire Line
	6950 2150 8650 2150
Wire Wire Line
	8650 2150 8650 2850
Wire Wire Line
	9350 3500 9350 3150
Wire Wire Line
	9350 2950 9900 2950
Text GLabel 9900 2950 2    60   Input ~ 0
GND
Text GLabel 9900 2500 2    60   Input ~ 0
VCC
$EndSCHEMATC
