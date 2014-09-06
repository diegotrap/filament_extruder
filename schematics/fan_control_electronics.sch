EESchema Schematic File Version 2
LIBS:power
LIBS:74xgxx
LIBS:74xx
LIBS:ac-dc
LIBS:actel
LIBS:adc-dac
LIBS:analog_switches
LIBS:atmel
LIBS:audio
LIBS:brooktre
LIBS:cmos_ieee
LIBS:cmos4000
LIBS:conn
LIBS:contrib
LIBS:cypress
LIBS:dc-dc
LIBS:device
LIBS:digital-audio
LIBS:display
LIBS:dsp
LIBS:elec-unifil
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:intel
LIBS:interface
LIBS:ir
LIBS:linear
LIBS:logo
LIBS:memory
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip
LIBS:microchip1
LIBS:microcontrollers
LIBS:motorola
LIBS:msp430
LIBS:noname-cache
LIBS:nxp_armmcu
LIBS:opto
LIBS:philips
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:regul
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:siliconi
LIBS:special
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:texas
LIBS:transf
LIBS:transistors
LIBS:ttl_ieee
LIBS:valves
LIBS:video
LIBS:xilinx
LIBS:heater_module_electronics-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Fan Control Electronics"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR?
U 1 1 540A0112
P 6150 4800
F 0 "#PWR?" H 6150 4800 30  0001 C CNN
F 1 "GND" H 6150 4730 30  0001 C CNN
F 2 "" H 6150 4800 60  0000 C CNN
F 3 "" H 6150 4800 60  0000 C CNN
	1    6150 4800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 540A042E
P 6350 2750
F 0 "P2" H 6350 2550 50  0000 C CNN
F 1 "Fan connector" H 6500 2950 50  0000 C CNN
F 2 "" H 6350 2750 60  0000 C CNN
F 3 "" H 6350 2750 60  0000 C CNN
	1    6350 2750
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 540A04D1
P 5750 4400
F 0 "R2" V 5830 4400 40  0000 C CNN
F 1 "10K" V 5757 4401 40  0000 C CNN
F 2 "" V 5680 4400 30  0000 C CNN
F 3 "" H 5750 4400 30  0000 C CNN
	1    5750 4400
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q1
U 1 1 540A05F4
P 6050 3850
F 0 "Q1" H 6000 3800 60  0000 R CNN
F 1 "MOSFET" H 6100 4100 60  0000 R CNN
F 2 "" H 6050 3850 60  0000 C CNN
F 3 "" H 6050 3850 60  0000 C CNN
	1    6050 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2800 6150 3650
$Comp
L +24V #PWR?
U 1 1 540A063A
P 6150 2400
F 0 "#PWR?" H 6150 2350 20  0001 C CNN
F 1 "+24V" H 6150 2550 47  0000 C CNN
F 2 "" H 6150 2400 60  0000 C CNN
F 3 "" H 6150 2400 60  0000 C CNN
	1    6150 2400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 540A0656
P 5450 3850
F 0 "R1" V 5530 3850 40  0000 C CNN
F 1 "100" V 5457 3851 40  0000 C CNN
F 2 "" V 5380 3850 30  0000 C CNN
F 3 "" H 5450 3850 30  0000 C CNN
	1    5450 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 3850 5850 3850
Wire Wire Line
	5750 4150 5750 3850
Connection ~ 5750 3850
$Comp
L CONN_01X01 P1
U 1 1 540A06F7
P 4700 3850
F 0 "P1" H 4700 3950 50  0000 C CNN
F 1 "Fan Pin" H 4700 3700 50  0000 C CNN
F 2 "" H 4700 3850 60  0000 C CNN
F 3 "" H 4700 3850 60  0000 C CNN
	1    4700 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3850 5200 3850
$Comp
L GND #PWR?
U 1 1 540A071E
P 5750 4800
F 0 "#PWR?" H 5750 4800 30  0001 C CNN
F 1 "GND" H 5750 4730 30  0001 C CNN
F 2 "" H 5750 4800 60  0000 C CNN
F 3 "" H 5750 4800 60  0000 C CNN
	1    5750 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4650 5750 4800
Wire Wire Line
	6150 4050 6150 4800
Wire Wire Line
	6150 2400 6150 2700
Connection ~ 6150 2550
Connection ~ 6150 2950
$EndSCHEMATC
