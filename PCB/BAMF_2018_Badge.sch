EESchema Schematic File Version 4
LIBS:BAMF_2018_Badge-cache
EELAYER 26 0
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
L BAMF_2018_Badge:BAMF_2018_Badge U1
U 1 1 5A8B7115
P 6550 3700
F 0 "U1" H 6600 4800 50  0000 C CNN
F 1 "BAMF_2018_Badge" H 6550 4700 50  0000 C CNN
F 2 "FeatherWing:FeatherWing_NoOutline_WithAnt" H 6550 3700 50  0001 C CNN
F 3 "DOCUMENTATION" H 6550 3700 50  0001 C CNN
	1    6550 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR04
U 1 1 5AA0AB81
P 7400 3350
F 0 "#PWR04" H 7400 3200 50  0001 C CNN
F 1 "+BATT" H 7400 3490 50  0000 C CNN
F 2 "" H 7400 3350 50  0001 C CNN
F 3 "" H 7400 3350 50  0001 C CNN
	1    7400 3350
	1    0    0    -1  
$EndComp
Text GLabel 7300 3950 2    31   Input ~ 0
BTN_R
Text GLabel 7300 3750 2    31   Input ~ 0
BTN_G
Text GLabel 7300 4050 2    31   Input ~ 0
BTN_B
Text GLabel 7300 3850 2    31   Input ~ 0
BTN_Y
Text GLabel 5800 3350 0    31   Input ~ 0
LED_R
Text GLabel 5800 3450 0    31   Input ~ 0
LED_G
Text GLabel 5800 3550 0    31   Input ~ 0
LED_B
Text GLabel 5800 3650 0    31   Input ~ 0
LED_Y
Text GLabel 5800 3250 0    31   Input ~ 0
GND
$Comp
L switches:SW_Push_LED SW1
U 1 1 5ACAE2C6
P 3400 3450
F 0 "SW1" H 3400 3835 50  0000 C CNN
F 1 "RED" H 3400 3744 50  0000 C CNN
F 2 "Custom:SW_PUSH_LED" H 3400 3750 50  0001 C CNN
F 3 "" H 3400 3750 50  0001 C CNN
	1    3400 3450
	1    0    0    -1  
$EndComp
Text GLabel 2950 3350 0    31   Input ~ 0
GND
$Comp
L device:R_Small R1
U 1 1 5ACAE376
P 3100 3450
F 0 "R1" V 3000 3400 50  0000 C CNN
F 1 "90" V 3000 3550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" H 3100 3450 50  0001 C CNN
F 3 "" H 3100 3450 50  0001 C CNN
	1    3100 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 3350 3000 3350
Wire Wire Line
	3000 3450 3000 3350
Connection ~ 3000 3350
Wire Wire Line
	3000 3350 3200 3350
Text GLabel 3600 3350 2    31   Input ~ 0
BTN_R
Text GLabel 3600 3450 2    31   Input ~ 0
LED_R
$Comp
L switches:SW_Push_LED SW3
U 1 1 5ACAE6B9
P 3400 4000
F 0 "SW3" H 3400 4385 50  0000 C CNN
F 1 "BLUE" H 3400 4294 50  0000 C CNN
F 2 "Custom:SW_PUSH_LED" H 3400 4300 50  0001 C CNN
F 3 "" H 3400 4300 50  0001 C CNN
	1    3400 4000
	1    0    0    -1  
$EndComp
Text GLabel 2950 3900 0    31   Input ~ 0
GND
$Comp
L device:R_Small R3
U 1 1 5ACAE6C0
P 3100 4000
F 0 "R3" V 3000 3950 50  0000 C CNN
F 1 "30" V 3000 4100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" H 3100 4000 50  0001 C CNN
F 3 "" H 3100 4000 50  0001 C CNN
	1    3100 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 3900 3000 3900
Wire Wire Line
	3000 4000 3000 3900
Connection ~ 3000 3900
Wire Wire Line
	3000 3900 3200 3900
Text GLabel 3600 3900 2    31   Input ~ 0
BTN_B
Text GLabel 3600 4000 2    31   Input ~ 0
LED_B
$Comp
L switches:SW_Push_LED SW2
U 1 1 5ACAE817
P 4450 3450
F 0 "SW2" H 4450 3835 50  0000 C CNN
F 1 "GREEN" H 4450 3744 50  0000 C CNN
F 2 "Custom:SW_PUSH_LED" H 4450 3750 50  0001 C CNN
F 3 "" H 4450 3750 50  0001 C CNN
	1    4450 3450
	1    0    0    -1  
$EndComp
Text GLabel 4000 3350 0    31   Input ~ 0
GND
$Comp
L device:R_Small R2
U 1 1 5ACAE81E
P 4150 3450
F 0 "R2" V 4050 3400 50  0000 C CNN
F 1 "30" V 4050 3550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" H 4150 3450 50  0001 C CNN
F 3 "" H 4150 3450 50  0001 C CNN
	1    4150 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 3350 4050 3350
Wire Wire Line
	4050 3450 4050 3350
Connection ~ 4050 3350
Wire Wire Line
	4050 3350 4250 3350
Text GLabel 4650 3350 2    31   Input ~ 0
BTN_G
Text GLabel 4650 3450 2    31   Input ~ 0
LED_G
$Comp
L switches:SW_Push_LED SW4
U 1 1 5ACAE82A
P 4450 4000
F 0 "SW4" H 4450 4385 50  0000 C CNN
F 1 "YELLOW" H 4450 4294 50  0000 C CNN
F 2 "Custom:SW_PUSH_LED" H 4450 4300 50  0001 C CNN
F 3 "" H 4450 4300 50  0001 C CNN
	1    4450 4000
	1    0    0    -1  
$EndComp
Text GLabel 4000 3900 0    31   Input ~ 0
GND
$Comp
L device:R_Small R4
U 1 1 5ACAE831
P 4150 4000
F 0 "R4" V 4050 3950 50  0000 C CNN
F 1 "90" V 4050 4100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" H 4150 4000 50  0001 C CNN
F 3 "" H 4150 4000 50  0001 C CNN
	1    4150 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 3900 4050 3900
Wire Wire Line
	4050 4000 4050 3900
Connection ~ 4050 3900
Wire Wire Line
	4050 3900 4250 3900
Text GLabel 4650 3900 2    31   Input ~ 0
BTN_Y
Text GLabel 4650 4000 2    31   Input ~ 0
LED_Y
$Comp
L device:Speaker_Crystal LS1
U 1 1 5ACAEF73
P 7950 4150
F 0 "LS1" H 8125 4146 50  0000 L CNN
F 1 "Piezo" H 8125 4055 50  0000 L CNN
F 2 "Custom:PS1240_Piezo" H 7915 4100 50  0001 C CNN
F 3 "" H 7915 4100 50  0001 C CNN
	1    7950 4150
	1    0    0    -1  
$EndComp
Text GLabel 7750 4250 0    31   Input ~ 0
GND
Wire Wire Line
	7300 4150 7750 4150
$Comp
L conn:Conn_01x02 J1
U 1 1 5ACAF28A
P 8000 3350
F 0 "J1" H 8080 3342 50  0000 L CNN
F 1 "Conn_01x02" H 8080 3251 50  0000 L CNN
F 2 "Custom:BATT_CONN" H 8000 3350 50  0001 C CNN
F 3 "~" H 8000 3350 50  0001 C CNN
	1    8000 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3350 7400 3350
Text GLabel 7800 3450 0    31   Input ~ 0
GND
Connection ~ 7400 3350
Wire Wire Line
	7400 3350 7800 3350
NoConn ~ 5800 2950
NoConn ~ 5800 3050
NoConn ~ 5800 3150
NoConn ~ 5800 3750
NoConn ~ 5800 3850
NoConn ~ 5800 3950
NoConn ~ 5800 4050
NoConn ~ 5800 4150
NoConn ~ 5800 4250
NoConn ~ 5800 4350
NoConn ~ 5800 4450
NoConn ~ 7300 4450
NoConn ~ 7300 4350
NoConn ~ 7300 4250
NoConn ~ 7300 3650
NoConn ~ 7300 3550
NoConn ~ 7300 3450
NoConn ~ 6700 2450
$EndSCHEMATC
