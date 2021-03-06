EESchema Schematic File Version 2
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
LIBS:nucléof303k8
LIBS:motordriverpolulu8835
LIBS:motordrivertb6612fng
LIBS:carte electronique-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L NucléoF303K8 F303K81
U 1 1 5936A3C9
P 8200 4700
F 0 "F303K81" H 5950 6400 60  0000 C CNN
F 1 "NucléoF303K8" H 5900 6500 60  0000 C CNN
F 2 "" H 5900 6500 60  0001 C CNN
F 3 "" H 5900 6500 60  0001 C CNN
	1    8200 4700
	1    0    0    -1  
$EndComp
$Comp
L +9V #PWR01
U 1 1 5936A492
P 9300 2200
F 0 "#PWR01" H 9300 2050 50  0001 C CNN
F 1 "+9V" H 9300 2340 50  0000 C CNN
F 2 "" H 9300 2200 50  0001 C CNN
F 3 "" H 9300 2200 50  0001 C CNN
	1    9300 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5936A4A9
P 9250 2550
F 0 "#PWR02" H 9250 2300 50  0001 C CNN
F 1 "GND" H 9250 2400 50  0000 C CNN
F 2 "" H 9250 2550 50  0001 C CNN
F 3 "" H 9250 2550 50  0001 C CNN
	1    9250 2550
	1    0    0    -1  
$EndComp
Text Notes 7000 3900 0    60   ~ 0
coté capteurs \nentrées analogiques
Text Notes 4850 4850 0    60   ~ 0
coté moteur \n sorties PWM
Text GLabel 4550 3900 2    60   Input ~ 0
PWM1
Text GLabel 4550 4500 2    60   Input ~ 0
PWM2
Text GLabel 3450 4200 0    60   Output ~ 0
MA1
Text GLabel 3450 4300 0    60   Output ~ 0
MA2
Text GLabel 3450 4400 0    60   Output ~ 0
MB1
Text GLabel 3450 4500 0    60   Output ~ 0
MB2
Text GLabel 5300 3100 0    60   Output ~ 0
UART_TX
Text GLabel 5300 3200 0    60   Input ~ 0
UART_RX
Text GLabel 5350 3900 0    60   Output ~ 0
PWM1
Text GLabel 5350 4500 0    60   Output ~ 0
PWM2
$Comp
L MotordriverTB6612FNG U1
U 1 1 5937A4FB
P 6850 6300
F 0 "U1" H 4000 8850 60  0000 C CNN
F 1 "MotordriverTB6612FNG" H 4000 8850 60  0000 C CNN
F 2 "" H 4000 8850 60  0001 C CNN
F 3 "" H 4000 8850 60  0001 C CNN
	1    6850 6300
	1    0    0    -1  
$EndComp
Text GLabel 4550 4200 2    60   Input ~ 0
STBY
Text GLabel 5350 4400 0    60   Output ~ 0
BIN2
Text GLabel 5350 4300 0    60   Output ~ 0
BIN1
Text GLabel 5350 4200 0    60   Output ~ 0
STBY
Text GLabel 5350 4100 0    60   Output ~ 0
AIN1
Text GLabel 5350 4000 0    60   Output ~ 0
AIN2
Text GLabel 4550 4000 2    60   Input ~ 0
AIN2
Text GLabel 4550 4100 2    60   Input ~ 0
AIN1
Text GLabel 4550 4400 2    60   Input ~ 0
BIN2
Text GLabel 4550 4300 2    60   Input ~ 0
BIN1
Text GLabel 6500 4000 2    60   Input ~ 0
SHARP1
Text GLabel 6500 3900 2    60   Input ~ 0
SHARP2
Text GLabel 6500 3800 2    60   Input ~ 0
SHARP3
Text GLabel 6500 3700 2    60   Input ~ 0
SHARP4
$Comp
L C C2
U 1 1 5937AF01
P 7650 2400
F 0 "C2" H 7675 2500 50  0000 L CNN
F 1 "C" H 7675 2300 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W4.5mm_P5.00mm" H 7688 2250 50  0001 C CNN
F 3 "" H 7650 2400 50  0001 C CNN
	1    7650 2400
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5937AF9F
P 8550 2400
F 0 "C3" H 8575 2500 50  0000 L CNN
F 1 "C" H 8575 2300 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W4.5mm_P5.00mm" H 8588 2250 50  0001 C CNN
F 3 "" H 8550 2400 50  0001 C CNN
	1    8550 2400
	1    0    0    -1  
$EndComp
$Comp
L CP1 C4
U 1 1 5937B08C
P 8800 2400
F 0 "C4" H 8825 2500 50  0000 L CNN
F 1 "CP1" H 8825 2300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P5.00mm" H 8800 2400 50  0001 C CNN
F 3 "" H 8800 2400 50  0001 C CNN
	1    8800 2400
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 5937B0CD
P 7450 2400
F 0 "C1" H 7475 2500 50  0000 L CNN
F 1 "CP1" H 7475 2300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_Tantal_D4.5mm_P5.00mm" H 7450 2400 50  0001 C CNN
F 3 "" H 7450 2400 50  0001 C CNN
	1    7450 2400
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 5937B2F6
P 9000 2250
F 0 "D1" H 9000 2350 50  0000 C CNN
F 1 "D" H 9000 2150 50  0000 C CNN
F 2 "Diodes_THT:D_5KPW_P12.70mm_Horizontal" H 9000 2250 50  0001 C CNN
F 3 "" H 9000 2250 50  0001 C CNN
	1    9000 2250
	1    0    0    -1  
$EndComp
$Comp
L 7805 U2
U 1 1 5937B47F
P 8100 2300
F 0 "U2" H 8250 2104 50  0000 C CNN
F 1 "7805" H 8100 2500 50  0000 C CNN
F 2 "" H 8100 2300 50  0001 C CNN
F 3 "" H 8100 2300 50  0001 C CNN
	1    8100 2300
	1    0    0    -1  
$EndComp
Text GLabel 8750 3450 0    60   Output ~ 0
SHARP4
Text GLabel 8750 3850 0    60   Output ~ 0
SHARP3
Text GLabel 8750 4250 0    60   Output ~ 0
SHARP2
Text GLabel 8750 4750 0    60   Output ~ 0
SHARP1
$Comp
L R R2
U 1 1 5937C337
P 9100 5050
F 0 "R2" V 9180 5050 50  0000 C CNN
F 1 "R" V 9100 5050 50  0000 C CNN
F 2 "" V 9030 5050 50  0001 C CNN
F 3 "" H 9100 5050 50  0001 C CNN
	1    9100 5050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5937C364
P 9300 5050
F 0 "R3" V 9380 5050 50  0000 C CNN
F 1 "R" V 9300 5050 50  0000 C CNN
F 2 "" V 9230 5050 50  0001 C CNN
F 3 "" H 9300 5050 50  0001 C CNN
	1    9300 5050
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5937C395
P 9500 5050
F 0 "R4" V 9580 5050 50  0000 C CNN
F 1 "R" V 9500 5050 50  0000 C CNN
F 2 "" V 9430 5050 50  0001 C CNN
F 3 "" H 9500 5050 50  0001 C CNN
	1    9500 5050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 SHARP4
U 1 1 5937C9C2
P 10050 3350
F 0 "SHARP4" H 10050 3550 50  0000 C CNN
F 1 "CONN_01X03" V 10150 3350 50  0000 C CNN
F 2 "" H 10050 3350 50  0001 C CNN
F 3 "" H 10050 3350 50  0001 C CNN
	1    10050 3350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 SHARP3
U 1 1 5937CA31
P 10050 3750
F 0 "SHARP3" H 10050 3950 50  0000 C CNN
F 1 "CONN_01X03" V 10150 3750 50  0000 C CNN
F 2 "" H 10050 3750 50  0001 C CNN
F 3 "" H 10050 3750 50  0001 C CNN
	1    10050 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 SHARP2
U 1 1 5937CA6A
P 10050 4150
F 0 "SHARP2" H 10050 4350 50  0000 C CNN
F 1 "CONN_01X03" V 10150 4150 50  0000 C CNN
F 2 "" H 10050 4150 50  0001 C CNN
F 3 "" H 10050 4150 50  0001 C CNN
	1    10050 4150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 SHARP1
U 1 1 5937CAA1
P 10050 4650
F 0 "SHARP1" H 10050 4850 50  0000 C CNN
F 1 "CONN_01X03" V 10150 4650 50  0000 C CNN
F 2 "" H 10050 4650 50  0001 C CNN
F 3 "" H 10050 4650 50  0001 C CNN
	1    10050 4650
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5937D63A
P 8900 5050
F 0 "R1" V 8980 5050 50  0000 C CNN
F 1 "R" V 8900 5050 50  0000 C CNN
F 2 "" V 8830 5050 50  0001 C CNN
F 3 "" H 8900 5050 50  0001 C CNN
	1    8900 5050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 capteurUS1
U 1 1 5937E422
P 10050 5600
F 0 "capteurUS1" H 10050 5850 50  0000 C CNN
F 1 "CONN_01X04" V 10150 5600 50  0000 C CNN
F 2 "" H 10050 5600 50  0001 C CNN
F 3 "" H 10050 5600 50  0001 C CNN
	1    10050 5600
	1    0    0    -1  
$EndComp
Text GLabel 9750 5550 0    60   Output ~ 0
TRIGGER
Text GLabel 9750 5650 0    60   Output ~ 0
CAPTEUR
Text GLabel 6500 4200 2    60   Input ~ 0
CAPTEUR
Text GLabel 6500 4100 2    60   Input ~ 0
TRIGGER
$Comp
L CONN_01X03_MALE servo1
U 1 1 5937FF38
P 3700 3300
F 0 "servo1" H 3700 3575 50  0000 C CNN
F 1 "CONN_01X03_MALE" H 3725 3025 50  0000 C CNN
F 2 "" H 3700 3500 50  0001 C CNN
F 3 "" H 3700 3500 50  0001 C CNN
	1    3700 3300
	1    0    0    -1  
$EndComp
Text GLabel 4100 3050 2    60   Input ~ 0
SERVCMD
Text GLabel 5350 3800 0    60   Output ~ 0
SERVCMD
NoConn ~ 5450 3700
NoConn ~ 5450 3600
NoConn ~ 5450 3500
NoConn ~ 5450 3300
NoConn ~ 6400 4400
NoConn ~ 6400 4300
NoConn ~ 6400 3600
NoConn ~ 6400 3500
NoConn ~ 6400 3300
NoConn ~ 6400 4500
$Comp
L +5V #PWR03
U 1 1 59381D80
P 6600 3100
F 0 "#PWR03" H 6600 2950 50  0001 C CNN
F 1 "+5V" H 6600 3240 50  0000 C CNN
F 2 "" H 6600 3100 50  0001 C CNN
F 3 "" H 6600 3100 50  0001 C CNN
	1    6600 3100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 59381DCA
P 7100 2250
F 0 "#PWR04" H 7100 2100 50  0001 C CNN
F 1 "+5V" H 7100 2390 50  0000 C CNN
F 2 "" H 7100 2250 50  0001 C CNN
F 3 "" H 7100 2250 50  0001 C CNN
	1    7100 2250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 59381E38
P 4200 3300
F 0 "#PWR05" H 4200 3150 50  0001 C CNN
F 1 "+5V" H 4200 3440 50  0000 C CNN
F 2 "" H 4200 3300 50  0001 C CNN
F 3 "" H 4200 3300 50  0001 C CNN
	1    4200 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 59381F24
P 7100 2550
F 0 "#PWR06" H 7100 2300 50  0001 C CNN
F 1 "GND" H 7100 2400 50  0000 C CNN
F 2 "" H 7100 2550 50  0001 C CNN
F 3 "" H 7100 2550 50  0001 C CNN
	1    7100 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 59381F6E
P 6800 3200
F 0 "#PWR07" H 6800 2950 50  0001 C CNN
F 1 "GND" H 6800 3050 50  0000 C CNN
F 2 "" H 6800 3200 50  0001 C CNN
F 3 "" H 6800 3200 50  0001 C CNN
	1    6800 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 59381FB8
P 4200 3500
F 0 "#PWR08" H 4200 3250 50  0001 C CNN
F 1 "GND" H 4200 3350 50  0000 C CNN
F 2 "" H 4200 3500 50  0001 C CNN
F 3 "" H 4200 3500 50  0001 C CNN
	1    4200 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 59382002
P 4650 4600
F 0 "#PWR09" H 4650 4350 50  0001 C CNN
F 1 "GND" H 4650 4450 50  0000 C CNN
F 2 "" H 4650 4600 50  0001 C CNN
F 3 "" H 4650 4600 50  0001 C CNN
	1    4650 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5938204C
P 3350 4600
F 0 "#PWR010" H 3350 4350 50  0001 C CNN
F 1 "GND" H 3350 4450 50  0000 C CNN
F 2 "" H 3350 4600 50  0001 C CNN
F 3 "" H 3350 4600 50  0001 C CNN
	1    3350 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 593820CC
P 3100 4100
F 0 "#PWR011" H 3100 3850 50  0001 C CNN
F 1 "GND" H 3100 3950 50  0000 C CNN
F 2 "" H 3100 4100 50  0001 C CNN
F 3 "" H 3100 4100 50  0001 C CNN
	1    3100 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 59382182
P 5200 3400
F 0 "#PWR012" H 5200 3150 50  0001 C CNN
F 1 "GND" H 5200 3250 50  0000 C CNN
F 2 "" H 5200 3400 50  0001 C CNN
F 3 "" H 5200 3400 50  0001 C CNN
	1    5200 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5938224A
P 8650 5200
F 0 "#PWR013" H 8650 4950 50  0001 C CNN
F 1 "GND" H 8650 5050 50  0000 C CNN
F 2 "" H 8650 5200 50  0001 C CNN
F 3 "" H 8650 5200 50  0001 C CNN
	1    8650 5200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 59382294
P 9150 5450
F 0 "#PWR014" H 9150 5200 50  0001 C CNN
F 1 "GND" H 9150 5300 50  0000 C CNN
F 2 "" H 9150 5450 50  0001 C CNN
F 3 "" H 9150 5450 50  0001 C CNN
	1    9150 5450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR015
U 1 1 593830C4
P 9000 5750
F 0 "#PWR015" H 9000 5600 50  0001 C CNN
F 1 "+5V" H 9000 5890 50  0000 C CNN
F 2 "" H 9000 5750 50  0001 C CNN
F 3 "" H 9000 5750 50  0001 C CNN
	1    9000 5750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR016
U 1 1 593832F8
P 8650 3250
F 0 "#PWR016" H 8650 3100 50  0001 C CNN
F 1 "+5V" H 8650 3390 50  0000 C CNN
F 2 "" H 8650 3250 50  0001 C CNN
F 3 "" H 8650 3250 50  0001 C CNN
	1    8650 3250
	1    0    0    -1  
$EndComp
NoConn ~ 6400 3400
$Comp
L CONN_01X02 J3
U 1 1 59383BA5
P 1750 4600
F 0 "J3" H 1750 4750 50  0000 C CNN
F 1 "CONN_01X02" V 1850 4600 50  0000 C CNN
F 2 "" H 1750 4600 50  0001 C CNN
F 3 "" H 1750 4600 50  0001 C CNN
	1    1750 4600
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 J2
U 1 1 59383C37
P 1750 4000
F 0 "J2" H 1750 4150 50  0000 C CNN
F 1 "CONN_01X02" V 1850 4000 50  0000 C CNN
F 2 "" H 1750 4000 50  0001 C CNN
F 3 "" H 1750 4000 50  0001 C CNN
	1    1750 4000
	-1   0    0    1   
$EndComp
Text GLabel 2050 3950 2    60   Input ~ 0
MA1
Text GLabel 2050 4050 2    60   Input ~ 0
MA2
Text GLabel 2050 4550 2    60   Input ~ 0
MB1
Text GLabel 2050 4650 2    60   Input ~ 0
MB2
$Comp
L CONN_01X02 J1
U 1 1 593842C1
P 1750 3300
F 0 "J1" H 1750 3450 50  0000 C CNN
F 1 "CONN_01X02" V 1850 3300 50  0000 C CNN
F 2 "" H 1750 3300 50  0001 C CNN
F 3 "" H 1750 3300 50  0001 C CNN
	1    1750 3300
	-1   0    0    1   
$EndComp
Text GLabel 2100 3250 2    60   Input ~ 0
UART_TX
Text GLabel 2100 3350 2    60   Output ~ 0
UART_RX
$Comp
L CONN_01X02 J4
U 1 1 5938475C
P 10050 2350
F 0 "J4" H 10050 2500 50  0000 C CNN
F 1 "CONN_01X02" V 10150 2350 50  0000 C CNN
F 2 "" H 10050 2350 50  0001 C CNN
F 3 "" H 10050 2350 50  0001 C CNN
	1    10050 2350
	1    0    0    -1  
$EndComp
$Comp
L +9V #PWR017
U 1 1 593847CF
P 9800 2300
F 0 "#PWR017" H 9800 2150 50  0001 C CNN
F 1 "+9V" H 9800 2440 50  0000 C CNN
F 2 "" H 9800 2300 50  0001 C CNN
F 3 "" H 9800 2300 50  0001 C CNN
	1    9800 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5938480F
P 9800 2400
F 0 "#PWR018" H 9800 2150 50  0001 C CNN
F 1 "GND" H 9800 2250 50  0000 C CNN
F 2 "" H 9800 2400 50  0001 C CNN
F 3 "" H 9800 2400 50  0001 C CNN
	1    9800 2400
	1    0    0    -1  
$EndComp
$Comp
L +9V #PWR019
U 1 1 59384FAE
P 3350 3900
F 0 "#PWR019" H 3350 3750 50  0001 C CNN
F 1 "+9V" H 3350 4040 50  0000 C CNN
F 2 "" H 3350 3900 50  0001 C CNN
F 3 "" H 3350 3900 50  0001 C CNN
	1    3350 3900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR020
U 1 1 59384FEE
P 3150 4000
F 0 "#PWR020" H 3150 3850 50  0001 C CNN
F 1 "+5V" H 3150 4140 50  0000 C CNN
F 2 "" H 3150 4000 50  0001 C CNN
F 3 "" H 3150 4000 50  0001 C CNN
	1    3150 4000
	1    0    0    -1  
$EndComp
Text Notes 8850 5650 2    60   ~ 0
Entrée capteurs\n
Text Notes 2250 3100 2    60   ~ 0
UART
Text Notes 2400 4350 2    60   ~ 0
Sorties Moteurs
Wire Wire Line
	5200 3400 5450 3400
Wire Wire Line
	5450 3200 5300 3200
Wire Wire Line
	5300 3100 5450 3100
Wire Notes Line
	6950 3450 6950 4250
Wire Wire Line
	3100 4100 3550 4100
Wire Wire Line
	3550 4200 3450 4200
Wire Wire Line
	3350 4600 3550 4600
Wire Wire Line
	4450 4600 4650 4600
Wire Wire Line
	4450 4400 4550 4400
Wire Wire Line
	4450 4200 4550 4200
Wire Wire Line
	4450 4000 4550 4000
Wire Wire Line
	6400 4000 6500 4000
Wire Wire Line
	6500 3900 6400 3900
Wire Wire Line
	6400 3800 6500 3800
Wire Wire Line
	6500 3700 6400 3700
Connection ~ 7650 2250
Connection ~ 7650 2550
Connection ~ 8100 2550
Connection ~ 8550 2550
Connection ~ 8800 2550
Connection ~ 8800 2250
Connection ~ 8550 2250
Wire Wire Line
	7100 2550 9250 2550
Connection ~ 7450 2250
Connection ~ 7450 2550
Wire Wire Line
	6400 3100 6600 3100
Wire Wire Line
	6400 3200 6800 3200
Wire Wire Line
	8750 3850 9850 3850
Wire Wire Line
	8750 4250 9850 4250
Wire Wire Line
	9850 4750 8750 4750
Connection ~ 8900 3450
Connection ~ 9100 3850
Connection ~ 9300 4250
Wire Wire Line
	9500 4750 9500 4900
Connection ~ 9500 4750
Wire Wire Line
	8650 5200 9600 5200
Connection ~ 8900 5200
Connection ~ 9100 5200
Connection ~ 9300 5200
Wire Wire Line
	9850 3350 9600 3350
Connection ~ 9500 5200
Wire Wire Line
	9850 3750 9600 3750
Connection ~ 9600 3750
Wire Wire Line
	9850 4150 9600 4150
Connection ~ 9600 4150
Wire Wire Line
	9850 4650 9600 4650
Connection ~ 9600 4650
Wire Wire Line
	8650 3250 9850 3250
Wire Wire Line
	9850 3650 9700 3650
Connection ~ 9700 3250
Connection ~ 9700 3650
Wire Wire Line
	9150 5450 9850 5450
Wire Wire Line
	9850 5550 9750 5550
Wire Wire Line
	9750 5650 9850 5650
Wire Wire Line
	9000 5750 9850 5750
Wire Wire Line
	9600 3350 9600 5200
Wire Wire Line
	9300 4900 9300 4250
Wire Wire Line
	9100 3850 9100 4900
Wire Wire Line
	8900 3450 8900 4900
Wire Wire Line
	9700 3250 9700 4550
Wire Wire Line
	9700 4550 9850 4550
Wire Wire Line
	6400 4200 6500 4200
Wire Wire Line
	6500 4100 6400 4100
Wire Wire Line
	5350 3800 5450 3800
Wire Wire Line
	4000 3500 4200 3500
Wire Wire Line
	4000 3300 4200 3300
Wire Wire Line
	4100 3100 4000 3100
Wire Wire Line
	9850 4050 9700 4050
Connection ~ 9700 4050
Wire Wire Line
	3350 3900 3550 3900
Wire Wire Line
	3150 4000 3550 4000
Wire Wire Line
	3450 4300 3550 4300
Wire Wire Line
	3550 4400 3450 4400
Wire Wire Line
	3450 4500 3550 4500
Wire Wire Line
	4450 4500 4550 4500
Wire Wire Line
	4550 4300 4450 4300
Wire Wire Line
	4100 3100 4100 3050
Wire Wire Line
	1950 3950 2050 3950
Wire Wire Line
	2050 4050 1950 4050
Wire Wire Line
	2050 4550 1950 4550
Wire Wire Line
	1950 4650 2050 4650
Wire Wire Line
	2100 3250 1950 3250
Wire Wire Line
	1950 3350 2100 3350
Wire Wire Line
	9800 2300 9850 2300
Wire Wire Line
	9850 2400 9800 2400
Wire Wire Line
	7100 2250 7700 2250
Wire Wire Line
	8750 3450 9850 3450
Wire Wire Line
	4550 4100 4450 4100
Wire Wire Line
	5350 4500 5450 4500
Wire Wire Line
	5450 4400 5350 4400
Wire Wire Line
	5350 4300 5450 4300
Wire Wire Line
	5450 4200 5350 4200
Wire Wire Line
	5350 4100 5450 4100
Wire Wire Line
	5450 4000 5350 4000
Wire Wire Line
	5350 3900 5450 3900
$Comp
L PWR_FLAG #FLG021
U 1 1 59389377
P 7150 2500
F 0 "#FLG021" H 7150 2575 50  0001 C CNN
F 1 "PWR_FLAG" H 7150 2650 50  0000 C CNN
F 2 "" H 7150 2500 50  0001 C CNN
F 3 "" H 7150 2500 50  0001 C CNN
	1    7150 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2550 7150 2500
Connection ~ 7150 2550
$Comp
L PWR_FLAG #FLG022
U 1 1 59389662
P 7350 2200
F 0 "#FLG022" H 7350 2275 50  0001 C CNN
F 1 "PWR_FLAG" H 7350 2350 50  0000 C CNN
F 2 "" H 7350 2200 50  0001 C CNN
F 3 "" H 7350 2200 50  0001 C CNN
	1    7350 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 2250 7350 2200
Connection ~ 7350 2250
$Comp
L PWR_FLAG #FLG023
U 1 1 593897D5
P 9550 2250
F 0 "#FLG023" H 9550 2325 50  0001 C CNN
F 1 "PWR_FLAG" H 9550 2400 50  0000 C CNN
F 2 "" H 9550 2250 50  0001 C CNN
F 3 "" H 9550 2250 50  0001 C CNN
	1    9550 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 2250 9150 2250
Wire Wire Line
	9300 2250 9300 2200
Connection ~ 9300 2250
Wire Wire Line
	4450 3900 4550 3900
Wire Wire Line
	8500 2250 8850 2250
Text Notes 8600 1950 2    60   ~ 0
Alimentation
$EndSCHEMATC
