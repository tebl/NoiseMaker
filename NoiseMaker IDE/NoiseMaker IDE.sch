EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "NoiseMaker"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 "34-pin floppy alternatives."
Comment4 "NoiseMaker module for use with 40-pin IDE, alternatively it can be built for use with"
$EndDescr
$Comp
L mounting:Mounting M1
U 1 1 604E62DD
P 10750 550
F 0 "M1" H 10750 650 50  0001 C CNN
F 1 "Mounting" H 10750 475 50  0001 C CNN
F 2 "mounting:M3_pin" H 10750 550 50  0001 C CNN
F 3 "~" H 10750 550 50  0001 C CNN
	1    10750 550 
	1    0    0    -1  
$EndComp
$Comp
L mounting:Mounting M2
U 1 1 604E7421
P 10875 550
F 0 "M2" H 10875 650 50  0001 C CNN
F 1 "Mounting" H 10875 475 50  0001 C CNN
F 2 "mounting:M3_pin" H 10875 550 50  0001 C CNN
F 3 "~" H 10875 550 50  0001 C CNN
	1    10875 550 
	1    0    0    -1  
$EndComp
$Comp
L mounting:Mounting M3
U 1 1 604E78AD
P 11000 550
F 0 "M3" H 11000 650 50  0001 C CNN
F 1 "Mounting" H 11000 475 50  0001 C CNN
F 2 "mounting:M3_pin" H 11000 550 50  0001 C CNN
F 3 "~" H 11000 550 50  0001 C CNN
	1    11000 550 
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano:Arduino_Nano A1
U 1 1 634CBE7C
P 5575 3125
F 0 "A1" H 5225 4075 50  0000 C CNN
F 1 "Arduino_Nano" V 5575 3125 50  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 5725 2175 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5575 2125 50  0001 C CNN
	1    5575 3125
	1    0    0    -1  
$EndComp
$Comp
L DFPlayer_Mini:DFPlayer_Mini A2
U 1 1 634CC848
P 9350 2525
F 0 "A2" H 9000 2875 50  0000 C CNN
F 1 "DFPlayer_Mini" H 9350 2875 50  0000 C CNN
F 2 "DFPlayer_Mini:DFPlayer_Mini" H 9275 2525 50  0001 C CNN
F 3 "" H 9275 2525 50  0001 C CNN
	1    9350 2525
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 3000 8775 3000
Wire Wire Line
	8775 3000 8775 3350
Wire Wire Line
	8775 3350 9925 3350
Wire Wire Line
	9925 3350 9925 3000
Wire Wire Line
	9925 3000 9850 3000
Wire Wire Line
	9925 3350 9925 3425
Connection ~ 9925 3350
$Comp
L power:GND #PWR0101
U 1 1 634CFBE0
P 9925 3425
F 0 "#PWR0101" H 9925 3175 50  0001 C CNN
F 1 "GND" H 9930 3252 50  0000 C CNN
F 2 "" H 9925 3425 50  0001 C CNN
F 3 "" H 9925 3425 50  0001 C CNN
	1    9925 3425
	1    0    0    -1  
$EndComp
NoConn ~ 5675 2125
$Comp
L Device:D_Small D1
U 1 1 634D2772
P 9025 4800
F 0 "D1" H 9025 5007 50  0000 C CNN
F 1 "1n4001" H 9025 4916 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P12.70mm_Horizontal" V 9025 4800 50  0001 C CNN
F 3 "~" V 9025 4800 50  0001 C CNN
	1    9025 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 634D40D7
P 9400 4800
F 0 "J3" H 9480 4792 50  0000 L CNN
F 1 "PWR" H 9480 4701 50  0000 L CNN
F 2 "noisemaker:Power" H 9400 4800 50  0001 C CNN
F 3 "~" H 9400 4800 50  0001 C CNN
	1    9400 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 634D5854
P 9125 4975
F 0 "#PWR0102" H 9125 4725 50  0001 C CNN
F 1 "GND" H 9130 4802 50  0000 C CNN
F 2 "" H 9125 4975 50  0001 C CNN
F 3 "" H 9125 4975 50  0001 C CNN
	1    9125 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	9125 4975 9125 4900
Wire Wire Line
	9125 4900 9200 4900
Wire Wire Line
	9125 4800 9200 4800
NoConn ~ 5475 2125
NoConn ~ 9850 3100
Wire Wire Line
	8925 4800 8775 4800
Wire Wire Line
	8775 4800 8775 4725
$Comp
L power:VCC #PWR03
U 1 1 634DC01A
P 8775 4725
F 0 "#PWR03" H 8775 4575 50  0001 C CNN
F 1 "VCC" H 8790 4898 50  0000 C CNN
F 2 "" H 8775 4725 50  0001 C CNN
F 3 "" H 8775 4725 50  0001 C CNN
	1    8775 4725
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 634DD196
P 5775 2050
F 0 "#PWR01" H 5775 1900 50  0001 C CNN
F 1 "VCC" H 5790 2223 50  0000 C CNN
F 2 "" H 5775 2050 50  0001 C CNN
F 3 "" H 5775 2050 50  0001 C CNN
	1    5775 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5775 2050 5775 2125
Wire Wire Line
	8850 2400 8775 2400
Wire Wire Line
	8775 2400 8775 2325
$Comp
L power:VCC #PWR02
U 1 1 634DF221
P 8775 2325
F 0 "#PWR02" H 8775 2175 50  0001 C CNN
F 1 "VCC" H 8790 2498 50  0000 C CNN
F 2 "" H 8775 2325 50  0001 C CNN
F 3 "" H 8775 2325 50  0001 C CNN
	1    8775 2325
	1    0    0    -1  
$EndComp
Text GLabel 5000 3625 0    50   Output ~ 0
SS_TX
Wire Wire Line
	5000 3625 5075 3625
Text GLabel 8375 2500 0    50   Input ~ 0
SS_TX
$Comp
L Device:R_Small R1
U 1 1 634E2B5C
P 8550 2500
F 0 "R1" V 8354 2500 50  0000 C CNN
F 1 "1k" V 8445 2500 50  0000 C CNN
F 2 "resistor:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8550 2500 50  0001 C CNN
F 3 "~" H 8550 2500 50  0001 C CNN
	1    8550 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	8375 2500 8450 2500
Wire Wire Line
	8650 2500 8850 2500
Text GLabel 5000 3525 0    50   Input ~ 0
SS_RX
Text GLabel 8375 2600 0    50   Output ~ 0
SS_RX
Wire Wire Line
	5000 3525 5075 3525
Wire Wire Line
	8375 2600 8850 2600
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 634E99A6
P 8375 3425
F 0 "J4" V 8475 3375 50  0000 C CNN
F 1 "SPK" V 8575 3375 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 8375 3425 50  0001 C CNN
F 3 "~" H 8375 3425 50  0001 C CNN
	1    8375 3425
	0    -1   1    0   
$EndComp
Wire Wire Line
	8275 2950 8100 2950
Wire Wire Line
	8275 2950 8275 3225
Wire Wire Line
	8275 2950 8275 2900
Wire Wire Line
	8275 2900 8850 2900
Connection ~ 8275 2950
Wire Wire Line
	8100 3050 8575 3050
Wire Wire Line
	8575 3050 8575 3100
Wire Wire Line
	8850 3100 8575 3100
Connection ~ 8575 3100
Wire Wire Line
	8575 3100 8575 3225
NoConn ~ 8375 3225
NoConn ~ 8475 3225
$Comp
L Device:Speaker LS1
U 1 1 634E7B91
P 7900 2950
F 0 "LS1" H 7863 3267 50  0000 C CNN
F 1 "Speaker" H 7863 3176 50  0000 C CNN
F 2 "Buzzer_Beeper:Buzzer_12x9.5RM7.6" H 7900 2750 50  0001 C CNN
F 3 "~" H 7890 2900 50  0001 C CNN
	1    7900 2950
	-1   0    0    -1  
$EndComp
NoConn ~ 9850 2900
NoConn ~ 9850 2800
NoConn ~ 9850 2700
NoConn ~ 9850 2600
NoConn ~ 9850 2500
Text GLabel 9925 2400 2    50   Output ~ 0
BUSY
Wire Wire Line
	9925 2400 9850 2400
Wire Wire Line
	5675 4125 5675 4200
$Comp
L power:GND #PWR0103
U 1 1 634F94AB
P 5675 4275
F 0 "#PWR0103" H 5675 4025 50  0001 C CNN
F 1 "GND" H 5680 4102 50  0000 C CNN
F 2 "" H 5675 4275 50  0001 C CNN
F 3 "" H 5675 4275 50  0001 C CNN
	1    5675 4275
	1    0    0    -1  
$EndComp
Wire Wire Line
	5575 4125 5575 4200
Wire Wire Line
	5575 4200 5675 4200
Connection ~ 5675 4200
Wire Wire Line
	5675 4275 5675 4200
NoConn ~ 6075 2525
NoConn ~ 6075 2625
NoConn ~ 6075 2925
NoConn ~ 5075 3825
Text GLabel 5000 3725 0    50   Input ~ 0
BUSY
Wire Wire Line
	5075 3725 5000 3725
NoConn ~ 5075 2525
NoConn ~ 5075 2625
NoConn ~ 5075 2925
NoConn ~ 5075 3225
NoConn ~ 5075 3325
NoConn ~ 5075 3425
NoConn ~ 6075 3225
NoConn ~ 6075 3325
NoConn ~ 6075 3425
NoConn ~ 6075 3525
NoConn ~ 6075 3825
NoConn ~ 6075 3725
NoConn ~ 8850 2700
NoConn ~ 8850 2800
$Comp
L ide_40:IDE J1
U 1 1 6351B81B
P 2025 3375
F 0 "J1" H 2025 4542 50  0000 C CNN
F 1 "IDE_OUT" H 2025 4451 50  0000 C CNN
F 2 "noisemaker:PinSocket_2x20_P2.54mm_Vertical" H 2025 3375 50  0001 C CNN
F 3 "~" H 2025 3375 50  0001 C CNN
	1    2025 3375
	1    0    0    -1  
$EndComp
Text Label 1750 2425 2    50   ~ 0
P1
Text Label 2300 2425 0    50   ~ 0
P2
Text Label 1750 2525 2    50   ~ 0
P3
Text Label 2300 2525 0    50   ~ 0
P4
Text Label 1750 2625 2    50   ~ 0
P5
Text Label 2300 2625 0    50   ~ 0
P6
Text Label 1750 2725 2    50   ~ 0
P7
Text Label 2300 2725 0    50   ~ 0
P8
Text Label 1750 2825 2    50   ~ 0
P9
Text Label 2300 2825 0    50   ~ 0
P10
Text Label 1750 2925 2    50   ~ 0
P11
Text Label 2300 2925 0    50   ~ 0
P12
Text Label 1750 3025 2    50   ~ 0
P13
Text Label 2300 3025 0    50   ~ 0
P14
Text Label 1750 3125 2    50   ~ 0
P15
Text Label 2300 3125 0    50   ~ 0
P16
Text Label 1750 3225 2    50   ~ 0
P17
Text Label 2300 3225 0    50   ~ 0
P18
Text Label 1750 3325 2    50   ~ 0
P19
Text Label 1750 3425 2    50   ~ 0
P21
Text Label 2300 3425 0    50   ~ 0
P22
Text Label 1750 3525 2    50   ~ 0
P23
Text Label 2300 3525 0    50   ~ 0
P24
Text Label 1750 3625 2    50   ~ 0
P25
Text Label 2300 3625 0    50   ~ 0
P26
Text Label 1750 3725 2    50   ~ 0
P27
Text Label 2300 3725 0    50   ~ 0
P28
Text Label 1750 3825 2    50   ~ 0
P29
Text Label 2300 3825 0    50   ~ 0
P30
Text Label 1750 3925 2    50   ~ 0
P31
Text Label 2300 3925 0    50   ~ 0
P32
Text Label 1750 4025 2    50   ~ 0
P33
Text Label 2300 4025 0    50   ~ 0
P34
Text Label 1750 4125 2    50   ~ 0
P35
Text Label 2300 4125 0    50   ~ 0
P36
Text Label 1750 4225 2    50   ~ 0
P37
Text Label 2300 4225 0    50   ~ 0
P38
Text Label 1750 4325 2    50   ~ 0
P39
Text Label 2300 4325 0    50   ~ 0
P40
Wire Wire Line
	1500 2425 1775 2425
Wire Wire Line
	1500 2525 1775 2525
Wire Wire Line
	1500 2625 1775 2625
Wire Wire Line
	1500 2725 1775 2725
Wire Wire Line
	1500 2825 1775 2825
Wire Wire Line
	1500 2925 1775 2925
Wire Wire Line
	1500 3025 1775 3025
Wire Wire Line
	1500 3125 1775 3125
Wire Wire Line
	1500 3225 1775 3225
Wire Wire Line
	1500 3325 1775 3325
Wire Wire Line
	1500 3425 1775 3425
Wire Wire Line
	1500 3525 1775 3525
Wire Wire Line
	1500 3625 1775 3625
Wire Wire Line
	1500 3725 1775 3725
Wire Wire Line
	1500 3825 1775 3825
Wire Wire Line
	1500 3925 1775 3925
Wire Wire Line
	1500 4025 1775 4025
Wire Wire Line
	1500 4125 1775 4125
Wire Wire Line
	1500 4225 1775 4225
Wire Wire Line
	2275 2425 2550 2425
Wire Wire Line
	2275 2525 2550 2525
Wire Wire Line
	2275 2625 2550 2625
Wire Wire Line
	2275 2725 2550 2725
Wire Wire Line
	2275 2825 2550 2825
Wire Wire Line
	2275 2925 2550 2925
Wire Wire Line
	2275 3025 2550 3025
Wire Wire Line
	2275 3125 2550 3125
Wire Wire Line
	2275 3225 2550 3225
Wire Wire Line
	2275 3425 2550 3425
Wire Wire Line
	2275 3525 2550 3525
Wire Wire Line
	2275 3625 2550 3625
Wire Wire Line
	2275 3725 2550 3725
Wire Wire Line
	2275 3825 2550 3825
Wire Wire Line
	2275 3925 2550 3925
Wire Wire Line
	2275 4025 2550 4025
Wire Wire Line
	2275 4125 2550 4125
Wire Wire Line
	2275 4225 2550 4225
Wire Wire Line
	2275 4325 2550 4325
Entry Wire Line
	1400 2325 1500 2425
Entry Wire Line
	1400 2425 1500 2525
Entry Wire Line
	1400 2525 1500 2625
Entry Wire Line
	1400 2625 1500 2725
Entry Wire Line
	1400 3825 1500 3925
Entry Wire Line
	1400 3925 1500 4025
Entry Wire Line
	1400 4025 1500 4125
Entry Wire Line
	1400 4125 1500 4225
Entry Wire Line
	1400 4225 1500 4325
Entry Wire Line
	1400 3525 1500 3625
Entry Wire Line
	1400 3625 1500 3725
Entry Wire Line
	1400 3725 1500 3825
Entry Wire Line
	1400 3125 1500 3225
Entry Wire Line
	1400 3225 1500 3325
Entry Wire Line
	1400 3325 1500 3425
Entry Wire Line
	1400 3425 1500 3525
Entry Wire Line
	1400 2725 1500 2825
Entry Wire Line
	1400 2825 1500 2925
Entry Wire Line
	1400 2925 1500 3025
Entry Wire Line
	1400 3025 1500 3125
Entry Wire Line
	2650 2325 2550 2425
Entry Wire Line
	2650 2425 2550 2525
Entry Wire Line
	2650 2525 2550 2625
Entry Wire Line
	2650 2625 2550 2725
Entry Wire Line
	2650 3825 2550 3925
Entry Wire Line
	2650 3925 2550 4025
Entry Wire Line
	2650 4025 2550 4125
Entry Wire Line
	2650 4125 2550 4225
Entry Wire Line
	2650 4225 2550 4325
Entry Wire Line
	2650 3525 2550 3625
Entry Wire Line
	2650 3625 2550 3725
Entry Wire Line
	2650 3725 2550 3825
Entry Wire Line
	2650 3125 2550 3225
Entry Wire Line
	2650 3325 2550 3425
Entry Wire Line
	2650 3425 2550 3525
Entry Wire Line
	2650 2725 2550 2825
Entry Wire Line
	2650 2825 2550 2925
Entry Wire Line
	2650 2925 2550 3025
Entry Wire Line
	2650 3025 2550 3125
$Comp
L ide_40:IDE J2
U 1 1 636523B7
P 3550 3375
F 0 "J2" H 3550 4542 50  0000 C CNN
F 1 "IDE_IN" H 3550 4451 50  0000 C CNN
F 2 "noisemaker:IDC-Header_2x20_P2.54mm_Vertical" H 3550 3375 50  0001 C CNN
F 3 "~" H 3550 3375 50  0001 C CNN
	1    3550 3375
	1    0    0    -1  
$EndComp
Text Label 3275 2425 2    50   ~ 0
P1
Text Label 3825 2425 0    50   ~ 0
P2
Text Label 3275 2525 2    50   ~ 0
P3
Text Label 3825 2525 0    50   ~ 0
P4
Text Label 3275 2625 2    50   ~ 0
P5
Text Label 3825 2625 0    50   ~ 0
P6
Text Label 3275 2725 2    50   ~ 0
P7
Text Label 3825 2725 0    50   ~ 0
P8
Text Label 3275 2825 2    50   ~ 0
P9
Text Label 3825 2825 0    50   ~ 0
P10
Text Label 3275 2925 2    50   ~ 0
P11
Text Label 3825 2925 0    50   ~ 0
P12
Text Label 3275 3025 2    50   ~ 0
P13
Text Label 3825 3025 0    50   ~ 0
P14
Text Label 3275 3125 2    50   ~ 0
P15
Text Label 3825 3125 0    50   ~ 0
P16
Text Label 3275 3225 2    50   ~ 0
P17
Text Label 3825 3225 0    50   ~ 0
P18
Text Label 3275 3325 2    50   ~ 0
P19
Text Label 3275 3425 2    50   ~ 0
P21
Text Label 3825 3425 0    50   ~ 0
P22
Text Label 3275 3525 2    50   ~ 0
P23
Text Label 3825 3525 0    50   ~ 0
P24
Text Label 3275 3625 2    50   ~ 0
P25
Text Label 3825 3625 0    50   ~ 0
P26
Text Label 3275 3725 2    50   ~ 0
P27
Text Label 3825 3725 0    50   ~ 0
P28
Text Label 3275 3825 2    50   ~ 0
P29
Text Label 3825 3825 0    50   ~ 0
P30
Text Label 3275 3925 2    50   ~ 0
P31
Text Label 3825 3925 0    50   ~ 0
P32
Text Label 3275 4025 2    50   ~ 0
P33
Text Label 3825 4025 0    50   ~ 0
P34
Text Label 3275 4125 2    50   ~ 0
P35
Text Label 3825 4125 0    50   ~ 0
P36
Text Label 3275 4225 2    50   ~ 0
P37
Text Label 3825 4225 0    50   ~ 0
P38
Text Label 3275 4325 2    50   ~ 0
P39
Text Label 3825 4325 0    50   ~ 0
P40
Wire Wire Line
	3025 2425 3300 2425
Wire Wire Line
	3025 2525 3300 2525
Wire Wire Line
	3025 2625 3300 2625
Wire Wire Line
	3025 2725 3300 2725
Wire Wire Line
	3025 2825 3300 2825
Wire Wire Line
	3025 2925 3300 2925
Wire Wire Line
	3025 3025 3300 3025
Wire Wire Line
	3025 3125 3300 3125
Wire Wire Line
	3025 3225 3300 3225
Wire Wire Line
	3025 3325 3300 3325
Wire Wire Line
	3025 3425 3300 3425
Wire Wire Line
	3025 3525 3300 3525
Wire Wire Line
	3025 3625 3300 3625
Wire Wire Line
	3025 3725 3300 3725
Wire Wire Line
	3025 3825 3300 3825
Wire Wire Line
	3025 3925 3300 3925
Wire Wire Line
	3025 4025 3300 4025
Wire Wire Line
	3025 4125 3300 4125
Wire Wire Line
	3025 4225 3300 4225
Wire Wire Line
	3800 2425 4075 2425
Wire Wire Line
	3800 2525 4075 2525
Wire Wire Line
	3800 2625 4075 2625
Wire Wire Line
	3800 2725 4075 2725
Wire Wire Line
	3800 2825 4075 2825
Wire Wire Line
	3800 2925 4075 2925
Wire Wire Line
	3800 3025 4075 3025
Wire Wire Line
	3800 3125 4075 3125
Wire Wire Line
	3800 3225 4075 3225
Wire Wire Line
	3800 3425 4075 3425
Wire Wire Line
	3800 3525 4075 3525
Wire Wire Line
	3800 3625 4075 3625
Wire Wire Line
	3800 3725 4075 3725
Wire Wire Line
	3800 3825 4075 3825
Wire Wire Line
	3800 3925 4075 3925
Wire Wire Line
	3800 4025 4075 4025
Wire Wire Line
	3800 4125 4075 4125
Wire Wire Line
	3800 4225 4075 4225
Wire Wire Line
	3800 4325 4075 4325
Entry Wire Line
	2925 2325 3025 2425
Entry Wire Line
	2925 2425 3025 2525
Entry Wire Line
	2925 2525 3025 2625
Entry Wire Line
	2925 2625 3025 2725
Entry Wire Line
	2925 3825 3025 3925
Entry Wire Line
	2925 3925 3025 4025
Entry Wire Line
	2925 4025 3025 4125
Entry Wire Line
	2925 4125 3025 4225
Entry Wire Line
	2925 4225 3025 4325
Entry Wire Line
	2925 3525 3025 3625
Entry Wire Line
	2925 3625 3025 3725
Entry Wire Line
	2925 3725 3025 3825
Entry Wire Line
	2925 3125 3025 3225
Entry Wire Line
	2925 3225 3025 3325
Entry Wire Line
	2925 3325 3025 3425
Entry Wire Line
	2925 3425 3025 3525
Entry Wire Line
	2925 2725 3025 2825
Entry Wire Line
	2925 2825 3025 2925
Entry Wire Line
	2925 2925 3025 3025
Entry Wire Line
	2925 3025 3025 3125
Entry Wire Line
	4175 2325 4075 2425
Entry Wire Line
	4175 2425 4075 2525
Entry Wire Line
	4175 2525 4075 2625
Entry Wire Line
	4175 2625 4075 2725
Entry Wire Line
	4175 3825 4075 3925
Entry Wire Line
	4175 3925 4075 4025
Entry Wire Line
	4175 4025 4075 4125
Entry Wire Line
	4175 4125 4075 4225
Entry Wire Line
	4175 4225 4075 4325
Entry Wire Line
	4175 3525 4075 3625
Entry Wire Line
	4175 3625 4075 3725
Entry Wire Line
	4175 3725 4075 3825
Entry Wire Line
	4175 3125 4075 3225
Entry Wire Line
	4175 3325 4075 3425
Entry Wire Line
	4175 3425 4075 3525
Entry Wire Line
	4175 2725 4075 2825
Entry Wire Line
	4175 2825 4075 2925
Entry Wire Line
	4175 2925 4075 3025
Entry Wire Line
	4175 3025 4075 3125
Connection ~ 2650 2075
Wire Bus Line
	2650 2075 2925 2075
Connection ~ 2925 2075
Wire Bus Line
	2925 2075 4175 2075
Wire Wire Line
	1500 4325 1775 4325
Text GLabel 3350 5875 2    50   Output ~ 0
FLP_MOTOR
$Comp
L Jumper:SolderJumper_3_Bridged12 JP2
U 1 1 6372F928
P 1950 6650
F 0 "JP2" H 2050 6400 50  0000 L CNN
F 1 "DRV_SEL2" H 2050 6475 50  0000 L CNN
F 2 "solder_bridge:select2" H 1950 6650 50  0001 C CNN
F 3 "~" H 1950 6650 50  0001 C CNN
	1    1950 6650
	-1   0    0    1   
$EndComp
Text Label 1225 6750 0    50   ~ 0
P14
Text Notes 1400 6750 0    50   ~ 0
/DRVSA
Wire Wire Line
	1200 6650 1750 6650
Text Label 1225 6650 0    50   ~ 0
P12
Text Notes 1400 6650 0    50   ~ 0
/DRVSB
Entry Wire Line
	1100 6550 1200 6650
Entry Wire Line
	1100 6650 1200 6750
Wire Wire Line
	1950 6425 1950 6500
Wire Wire Line
	2225 6750 2225 6650
Wire Wire Line
	2225 6650 2150 6650
Wire Wire Line
	1200 6750 2225 6750
$Comp
L Jumper:SolderJumper_3_Bridged12 JP1
U 1 1 63797BFE
P 1950 6100
F 0 "JP1" H 2050 5850 50  0000 L CNN
F 1 "DRV_SEL1" H 2050 5925 50  0000 L CNN
F 2 "solder_bridge:select2" H 1950 6100 50  0001 C CNN
F 3 "~" H 1950 6100 50  0001 C CNN
	1    1950 6100
	-1   0    0    1   
$EndComp
Text Label 1225 6200 0    50   ~ 0
P10
Text Notes 1400 6200 0    50   ~ 0
/MOTEA
Wire Wire Line
	1200 6100 1750 6100
Text Label 1225 6100 0    50   ~ 0
P16
Text Notes 1400 6100 0    50   ~ 0
/MOTEB
Entry Wire Line
	1100 6000 1200 6100
Entry Wire Line
	1100 6100 1200 6200
Wire Wire Line
	1950 5875 1950 5950
Wire Wire Line
	2225 6200 2225 6100
Wire Wire Line
	2225 6100 2150 6100
Wire Wire Line
	1200 6200 2225 6200
Text GLabel 5000 2725 0    50   Input ~ 0
ARD_P2
Wire Wire Line
	5000 2725 5075 2725
Text GLabel 5000 2825 0    50   Input ~ 0
ARD_P3
Wire Wire Line
	5000 2825 5075 2825
Text Label 1225 7200 0    50   ~ 0
P39
Entry Wire Line
	1100 7100 1200 7200
Text Notes 1400 7200 0    50   ~ 0
/IDE_ACTIVE
Text GLabel 3350 6825 2    50   Output ~ 0
ARD_P2
$Comp
L Jumper:SolderJumper_3_Bridged12 JP3
U 1 1 637E8572
P 3075 6825
F 0 "JP3" V 3125 6925 50  0000 L CNN
F 1 "MODE_SEL2" V 3050 6925 50  0000 L CNN
F 2 "solder_bridge:select2" H 3075 6825 50  0001 C CNN
F 3 "~" H 3075 6825 50  0001 C CNN
	1    3075 6825
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3025 4325 3300 4325
Text Label 2225 6425 0    50   ~ 0
FLP_DRIVE_SEL
Text GLabel 3350 5550 2    50   Output ~ 0
ARD_P3
Wire Wire Line
	3075 7025 3075 7200
Wire Wire Line
	3350 6825 3225 6825
Wire Wire Line
	3075 6425 3075 6625
Text Label 1225 5550 0    50   ~ 0
P20
Text Notes 1400 5550 0    50   ~ 0
/STEP
Entry Wire Line
	1100 5450 1200 5550
Text Label 1225 5650 0    50   ~ 0
P34
Text Notes 1400 5650 0    50   ~ 0
/DSKCHG
Entry Wire Line
	1100 5550 1200 5650
Text GLabel 3350 5650 2    50   Output ~ 0
FLP_DSKCHG
Text GLabel 5000 3025 0    50   Input ~ 0
FLP_DSKCHG
Wire Wire Line
	5075 3025 5000 3025
Text GLabel 5000 3125 0    50   Input ~ 0
FLP_MOTOR
Wire Wire Line
	5000 3125 5075 3125
Text Label 2300 3325 0    50   ~ 0
P20
Entry Wire Line
	2650 3225 2550 3325
Wire Wire Line
	2250 3325 2550 3325
Text Label 3825 3325 0    50   ~ 0
P20
Entry Wire Line
	4175 3225 4075 3325
Wire Wire Line
	3775 3325 4075 3325
Wire Bus Line
	1100 2075 1400 2075
Connection ~ 1400 2075
Wire Bus Line
	1400 2075 2650 2075
Wire Wire Line
	3075 7200 1200 7200
Wire Wire Line
	1950 6425 3075 6425
Wire Wire Line
	3350 5875 1950 5875
Wire Wire Line
	1200 5650 3350 5650
Wire Wire Line
	3350 5550 1200 5550
Text Notes 1925 4550 0    50   ~ 0
* Pin 20 when used with IDE should be removed.
$Comp
L power:GND #PWR04
U 1 1 63AF688F
P 6900 3700
F 0 "#PWR04" H 6900 3450 50  0001 C CNN
F 1 "GND" H 6905 3527 50  0000 C CNN
F 2 "" H 6900 3700 50  0001 C CNN
F 3 "" H 6900 3700 50  0001 C CNN
	1    6900 3700
	1    0    0    -1  
$EndComp
Text Label 1225 5100 0    50   ~ 0
P2
Text Notes 1400 5100 0    50   ~ 0
IDE_GND
Wire Wire Line
	1200 5000 1750 5000
Text Label 1225 5000 0    50   ~ 0
P1
Text Notes 1400 5000 0    50   ~ 0
FLP_GND
Entry Wire Line
	1100 4900 1200 5000
Entry Wire Line
	1100 5000 1200 5100
Wire Wire Line
	1950 4775 1950 4850
Wire Wire Line
	2225 5100 2225 5000
Wire Wire Line
	2225 5000 2150 5000
Wire Wire Line
	1200 5100 2225 5100
$Comp
L power:GND #PWR05
U 1 1 63B7D998
P 2350 5100
F 0 "#PWR05" H 2350 4850 50  0001 C CNN
F 1 "GND" H 2355 4927 50  0000 C CNN
F 2 "" H 2350 5100 50  0001 C CNN
F 3 "" H 2350 5100 50  0001 C CNN
	1    2350 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5100 2350 4775
Wire Wire Line
	2350 4775 1950 4775
$Comp
L Jumper:SolderJumper_3_Bridged12 JP4
U 1 1 63BB5A15
P 6625 3625
F 0 "JP4" H 6675 3375 50  0000 L CNN
F 1 "MODE_SEL3" H 6675 3450 50  0000 L CNN
F 2 "solder_bridge:select2" H 6625 3625 50  0001 C CNN
F 3 "~" H 6625 3625 50  0001 C CNN
	1    6625 3625
	-1   0    0    1   
$EndComp
NoConn ~ 6825 3625
$Comp
L Jumper:SolderJumper_3_Bridged12 JP5
U 1 1 63B6D0B3
P 1950 5000
F 0 "JP5" H 2000 4750 50  0000 L CNN
F 1 "MODE_SEL1" H 2000 4825 50  0000 L CNN
F 2 "solder_bridge:select2" H 1950 5000 50  0001 C CNN
F 3 "~" H 1950 5000 50  0001 C CNN
	1    1950 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 3400 6625 3400
Wire Wire Line
	6625 3400 6625 3475
Text Notes 5025 5550 0    50   ~ 0
MODE_SEL[1-3] pins 1-2 should be linked\nwhen built as IDE activity indicator. 2-3\nwhen used in floppy mode.
Text Notes 4975 5400 0    50   ~ 0
*
Text Notes 6575 3400 0    50   ~ 0
*
Text Notes 1900 4775 0    50   ~ 0
*
Text Notes 2975 6800 0    50   ~ 0
*
Wire Wire Line
	6075 3625 6425 3625
Text Notes 1850 5875 0    50   ~ 0
**
Text Notes 1850 6425 0    50   ~ 0
**
Text Notes 4925 5725 0    50   ~ 0
**
Text Notes 5025 5875 0    50   ~ 0
With MODE_SEL[1-3] pins 2-3, built as floppy\nmode, then DRV_SEL[1-2] is used to select which\ndrive to react to (1-2 for drive A, 2-3 for B).
$Comp
L Switch:SW_Push SW1
U 1 1 63CE2533
P 6625 3125
F 0 "SW1" H 6625 3410 50  0000 C CNN
F 1 "TEST" H 6625 3319 50  0000 C CNN
F 2 "switch_cutout:SW_PUSH_6mm" H 6625 3325 50  0001 C CNN
F 3 "~" H 6625 3325 50  0001 C CNN
	1    6625 3125
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3125 6825 3125
Wire Wire Line
	6075 3125 6425 3125
Connection ~ 6900 3400
Wire Wire Line
	6900 3400 6900 3125
Wire Wire Line
	6900 3400 6900 3700
Wire Bus Line
	1100 2075 1100 7125
Wire Bus Line
	4175 2075 4175 4225
Wire Bus Line
	2925 2075 2925 4225
Wire Bus Line
	2650 2075 2650 4225
Wire Bus Line
	1400 2075 1400 4225
$EndSCHEMATC
