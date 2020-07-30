EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "thermoTester"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 11575 4565 0    50   ~ 0
AC24V
Text Label 11575 4665 0    50   ~ 0
AC36V
Text Label 11575 4765 0    50   ~ 0
AC110V
Text Label 11575 4865 0    50   ~ 0
AC220V
Text Label 11575 4965 0    50   ~ 0
AC_N
Wire Wire Line
	11575 4565 11925 4565
Wire Wire Line
	11575 4665 11925 4665
Wire Wire Line
	11575 4765 11925 4765
Wire Wire Line
	11575 4865 11925 4865
Wire Wire Line
	11575 4965 11925 4965
Wire Wire Line
	11925 4465 11575 4465
Text Label 11575 4465 0    50   ~ 0
AC12V
$Comp
L kicad_symbol_general:Conn_01x04 J71
U 1 1 5EEE586E
P 12125 5215
F 0 "J71" H 12205 5207 50  0000 L CNN
F 1 "PM9808_L" H 12205 5116 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBVA_2,5_4-G_1x04_P5.00mm_Vertical" H 12125 5215 50  0001 C CNN
F 3 "" H 12125 5215 50  0001 C CNN
	1    12125 5215
	1    0    0    -1  
$EndComp
Wire Wire Line
	11925 5115 11575 5115
Wire Wire Line
	11925 5215 11575 5215
Wire Wire Line
	11925 5315 11575 5315
Wire Wire Line
	11925 5415 11575 5415
Text Label 11575 5115 0    50   ~ 0
L_OUT
Text Label 11575 5215 0    50   ~ 0
N_OUT
Text Label 11575 5415 0    50   ~ 0
L_FK
Text Label 11575 5315 0    50   ~ 0
N_FK
$Comp
L kicad_symbol_general:Conn_01x02 J72
U 1 1 5EF2C114
P 12125 5565
F 0 "J72" H 12205 5557 50  0000 L CNN
F 1 "actuator" H 12205 5466 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBVA_2,5_2-G_1x02_P5.00mm_Vertical" H 12125 5565 50  0001 C CNN
F 3 "" H 12125 5565 50  0001 C CNN
	1    12125 5565
	1    0    0    -1  
$EndComp
Wire Wire Line
	11925 5665 11575 5665
Wire Wire Line
	11925 5565 11575 5565
Text Label 11575 5565 0    50   ~ 0
L_ACT
Text Label 11575 5665 0    50   ~ 0
N_ACT
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K10
U 1 1 5F3B5F45
P 6000 1830
F 0 "K10" V 6725 1630 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 6650 1630 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 6000 1830 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 6000 1830 50  0001 C CNN
	1    6000 1830
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K15
U 1 1 5EC488CD
P 3000 8160
F 0 "K15" V 3725 7960 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 3650 7960 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 3000 8160 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 3000 8160 50  0001 C CNN
	1    3000 8160
	0    1    -1   0   
$EndComp
Text Label 5300 1830 0    50   ~ 0
K11CV
Text Label 5300 1430 0    50   ~ 0
AC12V
Text Label 2400 9600 0    50   ~ 0
L_FK
Text Label 2400 10000 0    50   ~ 0
N_FK
Text Label 3600 9500 2    50   ~ 0
L_ACT
Text Label 3600 9900 2    50   ~ 0
N_ACT
Text Label 5300 2230 0    50   ~ 0
CK0
$Comp
L kicad_symbol_general:Conn_01x06 J70
U 1 1 5FB11F45
P 12125 4665
F 0 "J70" H 12205 4657 50  0000 L CNN
F 1 "transformer" H 12205 4566 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBVA_2,5_6-G_1x06_P5.00mm_Vertical" H 12125 4665 50  0001 C CNN
F 3 "~" H 12125 4665 50  0001 C CNN
	1    12125 4665
	1    0    0    -1  
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K18
U 1 1 62E748DA
P 9300 4200
F 0 "K18" V 10025 4000 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 9950 4000 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 9300 4200 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 9300 4200 50  0001 C CNN
	1    9300 4200
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K17
U 1 1 62E76005
P 9300 5990
F 0 "K17" V 10025 5790 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 9950 5790 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 9300 5990 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 9300 5990 50  0001 C CNN
	1    9300 5990
	0    1    -1   0   
$EndComp
$Comp
L Diode:SM4007 D10
U 1 1 6328353B
P 14322 7995
F 0 "D10" H 14317 7820 50  0000 C CNN
F 1 "SS14" H 14322 7900 50  0000 C CNN
F 2 "kicad_footprint_general:D_SMA" H 14322 7820 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A400/SMD1N400%23DIO.pdf" H 14322 7995 50  0001 C CNN
	1    14322 7995
	1    0    0    1   
$EndComp
$Comp
L Device:Fuse_Small F10
U 1 1 5EC23853
P 14572 7995
F 0 "F10" H 14572 8180 50  0000 C CNN
F 1 "200mA" H 14572 8089 50  0000 C CNN
F 2 "kicad_footprint_general:Fuse_1812_4532Metric" H 14572 7995 50  0001 C CNN
F 3 "~" H 14572 7995 50  0001 C CNN
	1    14572 7995
	-1   0    0    -1  
$EndComp
$Comp
L Diode:1N62xxA D11
U 1 1 5EC23854
P 14172 8210
F 0 "D11" V 14122 7960 50  0000 L CNN
F 1 "SMBJ28A" V 14222 7760 50  0000 L CNN
F 2 "kicad_footprint_general:D_SMB" H 14172 8010 50  0001 C CNN
F 3 "https://www.vishay.com/docs/88301/15ke.pdf" H 14122 8210 50  0001 C CNN
	1    14172 8210
	0    -1   1    0   
$EndComp
$Comp
L Device:CP_Small C10
U 1 1 5EC23855
P 13547 8195
F 0 "C10" H 13372 8295 50  0000 L CNN
F 1 "47uF" H 13347 8105 50  0000 L CNN
F 2 "kicad_footprint_general:CP_Elec_8x6.5" H 13547 8195 50  0001 C CNN
F 3 "~" H 13547 8195 50  0001 C CNN
F 4 "50V" H 13547 8195 50  0001 C CNN "Vlotage"
	1    13547 8195
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C13
U 1 1 5D968DAB
P 11147 8445
F 0 "C13" H 11197 8495 50  0000 L CNN
F 1 "1uF" H 11197 8345 50  0000 L CNN
F 2 "kicad_footprint_general:C_0603_1608Metric" H 11147 8445 50  0001 C CNN
F 3 "~" H 11147 8445 50  0001 C CNN
F 4 "50V" H 11147 8445 50  0001 C CNN "Voltage"
	1    11147 8445
	-1   0    0    -1  
$EndComp
$Comp
L Device:CP_Small C12
U 1 1 63283533
P 11472 8445
F 0 "C12" H 11672 8495 50  0000 R CNN
F 1 "220uF" H 11722 8345 50  0000 R CNN
F 2 "kicad_footprint_general:CP_Elec_6.3x5.4" H 11472 8445 50  0001 C CNN
F 3 "~" H 11472 8445 50  0001 C CNN
F 4 "10V" H 11472 8445 50  0001 C CNN "Voltage"
	1    11472 8445
	-1   0    0    -1  
$EndComp
NoConn ~ 12197 8470
$Comp
L power:GND #PWR0116
U 1 1 63283534
P 11872 8645
F 0 "#PWR0116" H 11872 8395 50  0001 C CNN
F 1 "GND" H 11877 8472 50  0000 C CNN
F 2 "" H 11872 8645 50  0001 C CNN
F 3 "" H 11872 8645 50  0001 C CNN
	1    11872 8645
	-1   0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0117
U 1 1 5D9EF352
P 13147 7995
F 0 "#PWR0117" H 13147 7845 50  0001 C CNN
F 1 "VDD" H 13164 8168 50  0000 C CNN
F 2 "" H 13147 7995 50  0001 C CNN
F 3 "" H 13147 7995 50  0001 C CNN
	1    13147 7995
	-1   0    0    -1  
$EndComp
Text Label 14997 7995 2    50   ~ 0
VIN
Text Label 14997 8470 2    50   ~ 0
GND
$Comp
L Diode:1N5819 D12
U 1 1 5D967C98
P 11872 8420
F 0 "D12" V 11822 8670 50  0000 R CNN
F 1 "SS14" V 11922 8670 50  0000 R CNN
F 2 "kicad_footprint_general:D_SMA" H 11872 8245 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 11872 8420 50  0001 C CNN
	1    11872 8420
	0    -1   1    0   
$EndComp
$Comp
L Device:L_Small L10
U 1 1 5D96A636
P 11647 8270
F 0 "L10" V 11832 8270 50  0000 C CNN
F 1 "68uH" V 11741 8270 50  0000 C CNN
F 2 "kicad_footprint_general:L_Bourns_SRN6045TA" H 11647 8270 50  0001 C CNN
F 3 "~" H 11647 8270 50  0001 C CNN
	1    11647 8270
	0    1    -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5EC23838
P 14320 9160
F 0 "#FLG0101" H 14320 9235 50  0001 C CNN
F 1 "PWR_FLAG" H 14320 9333 50  0000 C CNN
F 2 "" H 14320 9160 50  0001 C CNN
F 3 "~" H 14320 9160 50  0001 C CNN
	1    14320 9160
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5D901CDC
P 14320 9360
F 0 "#PWR0106" H 14320 9110 50  0001 C CNN
F 1 "GND" H 14325 9187 50  0000 C CNN
F 2 "" H 14320 9360 50  0001 C CNN
F 3 "" H 14320 9360 50  0001 C CNN
	1    14320 9360
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0108
U 1 1 5EC2383C
P 14770 9360
F 0 "#PWR0108" H 14770 9210 50  0001 C CNN
F 1 "VDD" H 14787 9533 50  0000 C CNN
F 2 "" H 14770 9360 50  0001 C CNN
F 3 "" H 14770 9360 50  0001 C CNN
	1    14770 9360
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 6328352F
P 14770 9160
F 0 "#FLG0103" H 14770 9235 50  0001 C CNN
F 1 "PWR_FLAG" H 14770 9333 50  0000 C CNN
F 2 "" H 14770 9160 50  0001 C CNN
F 3 "~" H 14770 9160 50  0001 C CNN
	1    14770 9160
	1    0    0    -1  
$EndComp
Wire Wire Line
	14320 9360 14320 9160
Wire Wire Line
	14770 9360 14770 9160
$Comp
L Device:C_Small C14
U 1 1 6328353F
P 10847 8445
F 0 "C14" H 10897 8495 50  0000 L CNN
F 1 "100nF" H 10847 8345 50  0000 L CNN
F 2 "kicad_footprint_general:C_0603_1608Metric" H 10847 8445 50  0001 C CNN
F 3 "~" H 10847 8445 50  0001 C CNN
F 4 "50V" H 10847 8445 50  0001 C CNN "Voltage"
	1    10847 8445
	-1   0    0    -1  
$EndComp
$Comp
L kicad_symbol_general:XL1509 U10
U 1 1 63283540
P 12597 8320
F 0 "U10" H 12797 8570 50  0000 C CNN
F 1 "XL1509" H 12447 8570 50  0000 C CNN
F 2 "kicad_footprint_general:SOIC-8_3.9x4.9mm_P1.27mm" H 12597 8320 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps3702.pdf" H 12197 8720 50  0001 C CNN
	1    12597 8320
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C11
U 1 1 63283535
P 13322 8195
F 0 "C11" H 13372 8295 50  0000 L CNN
F 1 "1uF" H 13372 8145 50  0000 L CNN
F 2 "kicad_footprint_general:C_0805_2012Metric" H 13322 8195 50  0001 C CNN
F 3 "~" H 13322 8195 50  0001 C CNN
F 4 "50V" H 13322 8195 50  0001 C CNN "Voltage"
	1    13322 8195
	-1   0    0    -1  
$EndComp
Wire Wire Line
	14672 7995 14997 7995
Wire Wire Line
	13547 8095 13547 7995
Connection ~ 13547 7995
Wire Wire Line
	13547 7995 13322 7995
Wire Wire Line
	13322 8095 13322 7995
Connection ~ 13322 7995
Wire Wire Line
	13322 7995 13147 7995
Connection ~ 13147 7995
Wire Wire Line
	12197 7995 12197 8170
Wire Wire Line
	12197 7995 13147 7995
Wire Wire Line
	12997 8170 12997 8270
Connection ~ 12997 8270
Wire Wire Line
	12997 8270 12997 8370
Connection ~ 12997 8370
Wire Wire Line
	12997 8370 12997 8470
Wire Wire Line
	12997 8470 13322 8470
Connection ~ 12997 8470
Wire Wire Line
	13322 8295 13322 8470
Connection ~ 13322 8470
Wire Wire Line
	13322 8470 13547 8470
Wire Wire Line
	13547 8295 13547 8470
Connection ~ 13547 8470
Wire Wire Line
	12197 8270 11872 8270
Connection ~ 11872 8270
Wire Wire Line
	11872 8270 11747 8270
Wire Wire Line
	11547 8270 11472 8270
Wire Wire Line
	10847 8545 10847 8645
Wire Wire Line
	10847 8645 11147 8645
Wire Wire Line
	11872 8645 11872 8570
Wire Wire Line
	11472 8545 11472 8645
Connection ~ 11472 8645
Wire Wire Line
	11472 8645 11872 8645
Wire Wire Line
	11147 8545 11147 8645
Connection ~ 11147 8645
Wire Wire Line
	11147 8645 11472 8645
Wire Wire Line
	10847 8345 10847 8270
Connection ~ 10847 8270
Wire Wire Line
	10847 8270 10572 8270
Wire Wire Line
	11147 8345 11147 8270
Connection ~ 11147 8270
Wire Wire Line
	11472 8345 11472 8270
Connection ~ 11472 8270
Wire Wire Line
	11472 8270 11147 8270
Connection ~ 11872 8645
Wire Wire Line
	10572 8270 10572 8870
Wire Wire Line
	10572 8870 12072 8870
Wire Wire Line
	12072 8870 12072 8370
Wire Wire Line
	12072 8370 12197 8370
Connection ~ 10572 8270
Wire Wire Line
	10922 8270 10847 8270
Wire Wire Line
	11147 8270 10922 8270
Connection ~ 10922 8270
$Comp
L power:+5VD #PWR0109
U 1 1 5DEC8798
P 10922 8270
F 0 "#PWR0109" H 10922 8120 50  0001 C CNN
F 1 "+5VD" H 10937 8443 50  0000 C CNN
F 2 "" H 10922 8270 50  0001 C CNN
F 3 "" H 10922 8270 50  0001 C CNN
	1    10922 8270
	1    0    0    -1  
$EndComp
$Comp
L power:+5VD #PWR0112
U 1 1 621442F5
P 15170 9360
F 0 "#PWR0112" H 15170 9210 50  0001 C CNN
F 1 "+5VD" H 15185 9533 50  0000 C CNN
F 2 "" H 15170 9360 50  0001 C CNN
F 3 "" H 15170 9360 50  0001 C CNN
	1    15170 9360
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 63283546
P 15170 9160
F 0 "#FLG0104" H 15170 9235 50  0001 C CNN
F 1 "PWR_FLAG" H 15170 9333 50  0000 C CNN
F 2 "" H 15170 9160 50  0001 C CNN
F 3 "~" H 15170 9160 50  0001 C CNN
	1    15170 9160
	1    0    0    -1  
$EndComp
Wire Wire Line
	15170 9160 15170 9360
Wire Wire Line
	14172 8060 14172 7995
Connection ~ 14172 7995
Wire Wire Line
	14172 8360 14172 8470
Connection ~ 14172 8470
Wire Wire Line
	14172 8470 14997 8470
Wire Wire Line
	15185 5655 14935 5655
Wire Wire Line
	15185 5755 14935 5755
Text Label 14935 5655 0    50   ~ 0
GND
Text Label 14935 5755 0    50   ~ 0
VIN
$Comp
L kicad_symbol_general:Conn_01x02 J10
U 1 1 5ECC3621
P 15385 5655
F 0 "J10" H 15465 5647 50  0000 L CNN
F 1 "Power" H 15465 5556 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBVA_2,5_2-G_1x02_P5.00mm_Vertical" H 15385 5655 50  0001 C CNN
F 3 "" H 15385 5655 50  0001 C CNN
	1    15385 5655
	1    0    0    -1  
$EndComp
Wire Wire Line
	3270 5820 3455 5820
Wire Wire Line
	3270 5920 3455 5920
Wire Wire Line
	3270 6020 3455 6020
Wire Wire Line
	3270 5420 3460 5420
Text Label 3460 5420 2    50   ~ 0
CK0
Text Label 3460 5520 2    50   ~ 0
CK1
Text Label 3460 5620 2    50   ~ 0
CK2
Text Label 3455 6020 2    50   ~ 0
CK6
$Comp
L kicad_symbol_general:Conn_01x07 J21
U 1 1 5F5BF13C
P 3070 5720
F 0 "J21" H 2988 6237 50  0000 C CNN
F 1 "CK" H 2988 6146 50  0000 C CNN
F 2 "kicad_footprint_general:PhoenixContact_MCV_1,5_7-G-3.81_1x07_P3.81mm_Vertical" H 3070 5720 50  0001 C CNN
F 3 "~" H 3070 5720 50  0001 C CNN
	1    3070 5720
	-1   0    0    -1  
$EndComp
Text Label 3455 5920 2    50   ~ 0
CK5
Text Label 3455 5820 2    50   ~ 0
CK4
Text Label 3460 5720 2    50   ~ 0
CK3
Wire Wire Line
	3270 5720 3460 5720
Wire Wire Line
	3270 5620 3460 5620
Wire Wire Line
	3270 5520 3460 5520
$Comp
L kicad_symbol_general:LL4448 D26
U 1 1 61B1F394
P 3030 10740
F 0 "D26" H 2985 10835 50  0000 C CNN
F 1 "1N4148" H 2990 10920 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 3030 10565 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 3030 10740 50  0001 C CNN
	1    3030 10740
	-1   0    0    1   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K16
U 1 1 5EC07506
P 3000 10000
F 0 "K16" V 3725 9800 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 3650 9800 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 3000 10000 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 3000 10000 50  0001 C CNN
	1    3000 10000
	0    1    -1   0   
$EndComp
Text Label 10105 8270 0    50   ~ 0
+5VD
Wire Wire Line
	2700 10400 2650 10400
Wire Wire Line
	2880 10740 2650 10740
Wire Wire Line
	2650 10740 2650 10400
Connection ~ 2650 10400
Wire Wire Line
	2650 10400 2400 10400
Wire Wire Line
	3300 10400 3350 10400
Wire Wire Line
	3180 10740 3350 10740
Wire Wire Line
	3350 10740 3350 10400
Connection ~ 3350 10400
Wire Wire Line
	3350 10400 3600 10400
Text Label 3600 10400 2    50   ~ 0
+5VD
Wire Wire Line
	2400 10000 2700 10000
Wire Wire Line
	2700 9600 2400 9600
Wire Wire Line
	3300 9900 3600 9900
Wire Wire Line
	3300 9500 3600 9500
$Comp
L kicad_symbol_general:LL4448 D25
U 1 1 5F4A48D8
P 2980 8900
F 0 "D25" H 2935 8995 50  0000 C CNN
F 1 "1N4148" H 2940 9080 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 2980 8725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 2980 8900 50  0001 C CNN
	1    2980 8900
	-1   0    0    1   
$EndComp
Wire Wire Line
	2700 8560 2640 8560
Wire Wire Line
	3600 7660 3300 7660
Wire Wire Line
	2700 7760 2400 7760
Wire Wire Line
	3600 8560 3370 8560
Text Label 3600 8560 2    50   ~ 0
+5VD
Wire Wire Line
	3130 8900 3370 8900
Wire Wire Line
	3370 8900 3370 8560
Connection ~ 3370 8560
Wire Wire Line
	3370 8560 3300 8560
Wire Wire Line
	2830 8900 2640 8900
Wire Wire Line
	2640 8900 2640 8560
Connection ~ 2640 8560
Wire Wire Line
	2640 8560 2400 8560
Text Label 2400 7760 0    50   ~ 0
AC_N
$Comp
L kicad_symbol_general:LL4448 D20
U 1 1 5F55C10D
P 6000 2520
F 0 "D20" H 6020 2630 50  0000 C CNN
F 1 "1N4148" H 6010 2710 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 6000 2345 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 6000 2520 50  0001 C CNN
	1    6000 2520
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 2230 6380 2230
Wire Wire Line
	6380 2230 6380 1930
Wire Wire Line
	6380 1930 6300 1930
Wire Wire Line
	6380 2230 6670 2230
Connection ~ 6380 2230
Text Label 6670 2230 2    50   ~ 0
+5VD
Wire Wire Line
	6150 2520 6380 2520
Wire Wire Line
	6380 2520 6380 2230
Wire Wire Line
	5700 2230 5630 2230
Wire Wire Line
	5850 2520 5630 2520
Wire Wire Line
	5630 2520 5630 2230
Connection ~ 5630 2230
Wire Wire Line
	5630 2230 5300 2230
Wire Wire Line
	5700 1830 5300 1830
Wire Wire Line
	5700 1430 5300 1430
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K11
U 1 1 5F6E09E4
P 6000 3600
F 0 "K11" V 6725 3400 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 6650 3400 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 6000 3600 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 6000 3600 50  0001 C CNN
	1    6000 3600
	0    1    -1   0   
$EndComp
Text Label 5300 3600 0    50   ~ 0
K12CV
Text Label 5300 3200 0    50   ~ 0
AC24V
Text Label 5300 4000 0    50   ~ 0
CK1
$Comp
L kicad_symbol_general:LL4448 D21
U 1 1 5F6E09ED
P 6000 4290
F 0 "D21" H 6020 4400 50  0000 C CNN
F 1 "1N4148" H 6010 4480 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 6000 4115 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 6000 4290 50  0001 C CNN
	1    6000 4290
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 4000 6380 4000
Wire Wire Line
	6380 4000 6380 3700
Wire Wire Line
	6380 3700 6300 3700
Wire Wire Line
	6380 4000 6670 4000
Connection ~ 6380 4000
Wire Wire Line
	6150 4290 6380 4290
Wire Wire Line
	6380 4290 6380 4000
Wire Wire Line
	5700 4000 5630 4000
Wire Wire Line
	5850 4290 5630 4290
Wire Wire Line
	5630 4290 5630 4000
Connection ~ 5630 4000
Wire Wire Line
	5630 4000 5300 4000
Wire Wire Line
	5700 3600 5300 3600
Wire Wire Line
	5700 3200 5300 3200
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K12
U 1 1 5F6F4E3D
P 6000 5360
F 0 "K12" V 6725 5160 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 6650 5160 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 6000 5360 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 6000 5360 50  0001 C CNN
	1    6000 5360
	0    1    -1   0   
$EndComp
Text Label 5300 5360 0    50   ~ 0
K13CV
Text Label 5300 4960 0    50   ~ 0
AC36V
Text Label 5300 5760 0    50   ~ 0
CK2
$Comp
L kicad_symbol_general:LL4448 D22
U 1 1 5F6F4E46
P 6000 6050
F 0 "D22" H 6020 6160 50  0000 C CNN
F 1 "1N4148" H 6010 6240 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 6000 5875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 6000 6050 50  0001 C CNN
	1    6000 6050
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 5760 6380 5760
Wire Wire Line
	6380 5760 6380 5460
Wire Wire Line
	6380 5460 6300 5460
Wire Wire Line
	6380 5760 6670 5760
Connection ~ 6380 5760
Wire Wire Line
	6150 6050 6380 6050
Wire Wire Line
	6380 6050 6380 5760
Wire Wire Line
	5700 5760 5630 5760
Wire Wire Line
	5850 6050 5630 6050
Wire Wire Line
	5630 6050 5630 5760
Connection ~ 5630 5760
Wire Wire Line
	5630 5760 5300 5760
Wire Wire Line
	5700 5360 5300 5360
Wire Wire Line
	5700 4960 5300 4960
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K13
U 1 1 5F70EF43
P 6000 7100
F 0 "K13" V 6725 6900 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 6650 6900 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 6000 7100 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 6000 7100 50  0001 C CNN
	1    6000 7100
	0    1    -1   0   
$EndComp
Text Label 5300 7100 0    50   ~ 0
K14CV
Text Label 5300 6700 0    50   ~ 0
AC110V
Text Label 5300 7500 0    50   ~ 0
CK3
$Comp
L kicad_symbol_general:LL4448 D23
U 1 1 5F70EF4C
P 6000 7790
F 0 "D23" H 6020 7900 50  0000 C CNN
F 1 "1N4148" H 6010 7980 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 6000 7615 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 6000 7790 50  0001 C CNN
	1    6000 7790
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 7500 6380 7500
Wire Wire Line
	6380 7500 6380 7200
Wire Wire Line
	6380 7200 6300 7200
Wire Wire Line
	6380 7500 6670 7500
Connection ~ 6380 7500
Wire Wire Line
	6150 7790 6380 7790
Wire Wire Line
	6380 7790 6380 7500
Wire Wire Line
	5700 7500 5630 7500
Wire Wire Line
	5850 7790 5630 7790
Wire Wire Line
	5630 7790 5630 7500
Connection ~ 5630 7500
Wire Wire Line
	5630 7500 5300 7500
Wire Wire Line
	5700 7100 5300 7100
Wire Wire Line
	5700 6700 5300 6700
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K14
U 1 1 5F721E54
P 6000 8900
F 0 "K14" V 6725 8700 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 6650 8700 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 6000 8900 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 6000 8900 50  0001 C CNN
	1    6000 8900
	0    1    -1   0   
$EndComp
Text Label 5300 8500 0    50   ~ 0
AC220V
Text Label 5300 9300 0    50   ~ 0
CK4
$Comp
L kicad_symbol_general:LL4448 D24
U 1 1 5F721E5D
P 6000 9590
F 0 "D24" H 6020 9700 50  0000 C CNN
F 1 "1N4148" H 6010 9780 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 6000 9415 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 6000 9590 50  0001 C CNN
	1    6000 9590
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 9300 6380 9300
Wire Wire Line
	6380 9300 6380 9000
Wire Wire Line
	6380 9000 6300 9000
Wire Wire Line
	6380 9300 6670 9300
Connection ~ 6380 9300
Wire Wire Line
	6150 9590 6380 9590
Wire Wire Line
	6380 9590 6380 9300
Wire Wire Line
	5700 9300 5630 9300
Wire Wire Line
	5850 9590 5630 9590
Wire Wire Line
	5630 9590 5630 9300
Connection ~ 5630 9300
Wire Wire Line
	5630 9300 5300 9300
Wire Wire Line
	5700 8500 5300 8500
Text Label 6670 4000 2    50   ~ 0
K11CV
Text Label 6670 5760 2    50   ~ 0
K12CV
Text Label 6670 7500 2    50   ~ 0
K13CV
Text Label 6670 9300 2    50   ~ 0
K14CV
NoConn ~ 5700 8900
Wire Wire Line
	6300 1330 6810 1330
Wire Wire Line
	6810 1330 6810 3100
Wire Wire Line
	6810 8400 6300 8400
Wire Wire Line
	6300 6600 6810 6600
Connection ~ 6810 6600
Wire Wire Line
	6810 6600 6810 8400
Wire Wire Line
	6300 4860 6810 4860
Connection ~ 6810 4860
Wire Wire Line
	6810 4860 6810 6600
Wire Wire Line
	6300 3100 6810 3100
Connection ~ 6810 3100
Wire Wire Line
	6810 3100 6810 4860
Wire Wire Line
	6810 8400 7090 8400
Connection ~ 6810 8400
Text Label 3600 7660 2    50   ~ 0
N_OUT
Text Label 7090 8400 2    50   ~ 0
L_OUT
Text Label 2400 8560 0    50   ~ 0
CK5
Text Label 2400 10400 0    50   ~ 0
CK6
Wire Wire Line
	13547 8470 14172 8470
Wire Wire Line
	13547 7995 14172 7995
NoConn ~ 3300 7860
NoConn ~ 3300 8060
NoConn ~ 3300 8260
NoConn ~ 2700 8160
NoConn ~ 3300 10100
NoConn ~ 3300 9700
NoConn ~ 6300 8800
NoConn ~ 6300 8600
NoConn ~ 6300 7000
NoConn ~ 6300 6800
NoConn ~ 6300 5060
NoConn ~ 6300 5260
NoConn ~ 6300 3500
NoConn ~ 6300 3300
NoConn ~ 6300 1730
NoConn ~ 6300 1530
$Comp
L kicad_symbol_general:Conn_01x02 J11
U 1 1 5F9F9D12
P 15400 5220
F 0 "J11" H 15480 5212 50  0000 L CNN
F 1 "MOTOR" H 15480 5121 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MCV_1,5_2-G-3.81_1x02_P3.81mm_Vertical" H 15400 5220 50  0001 C CNN
F 3 "" H 15400 5220 50  0001 C CNN
	1    15400 5220
	1    0    0    -1  
$EndComp
Wire Wire Line
	15200 5320 14940 5320
Wire Wire Line
	15200 5220 14940 5220
Text Label 14940 5320 0    50   ~ 0
M_1
Text Label 14940 5220 0    50   ~ 0
M_2
Wire Wire Line
	9000 4200 8960 4200
Wire Wire Line
	8960 4200 8960 3800
Wire Wire Line
	8960 3800 9000 3800
Wire Wire Line
	8960 4200 8600 4200
Connection ~ 8960 4200
Text Label 8600 4200 0    50   ~ 0
M_1
Text Label 8600 5990 0    50   ~ 0
M_2
Wire Wire Line
	9000 5990 8960 5990
Wire Wire Line
	9000 5590 8960 5590
Wire Wire Line
	8960 5590 8960 5990
Connection ~ 8960 5990
Wire Wire Line
	8960 5990 8600 5990
Wire Wire Line
	9600 3900 10070 3900
Wire Wire Line
	10070 3900 10070 4300
Wire Wire Line
	10070 6090 9600 6090
Wire Wire Line
	9600 5690 10070 5690
Connection ~ 10070 5690
Wire Wire Line
	10070 5690 10070 6090
Wire Wire Line
	9600 4300 10070 4300
Connection ~ 10070 4300
Wire Wire Line
	10070 4300 10070 5690
$Comp
L kicad_symbol_general:LL4448 D27
U 1 1 5FAAB660
P 9300 4910
F 0 "D27" H 9255 5005 50  0000 C CNN
F 1 "1N4148" H 9260 5090 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 9300 4735 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 9300 4910 50  0001 C CNN
	1    9300 4910
	-1   0    0    1   
$EndComp
$Comp
L kicad_symbol_general:LL4448 D28
U 1 1 5FAAC26C
P 9300 6740
F 0 "D28" H 9255 6835 50  0000 C CNN
F 1 "1N4148" H 9260 6920 50  0000 C CNN
F 2 "kicad_footprint_general:D_SOD-323F" H 9300 6565 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85557/ll4148.pdf" H 9300 6740 50  0001 C CNN
	1    9300 6740
	-1   0    0    1   
$EndComp
Wire Wire Line
	9600 4600 9710 4600
Wire Wire Line
	9450 4910 9710 4910
Wire Wire Line
	9710 4910 9710 4600
Connection ~ 9710 4600
Wire Wire Line
	9710 4600 9950 4600
Wire Wire Line
	9000 4600 8960 4600
Wire Wire Line
	9150 4910 8960 4910
Wire Wire Line
	8960 4910 8960 4600
Connection ~ 8960 4600
Wire Wire Line
	8960 4600 8600 4600
Text Label 9950 4600 2    50   ~ 0
+5VD
Wire Wire Line
	9600 6390 9660 6390
Wire Wire Line
	9450 6740 9660 6740
Wire Wire Line
	9660 6740 9660 6390
Connection ~ 9660 6390
Wire Wire Line
	9660 6390 10000 6390
Wire Wire Line
	9000 6390 8940 6390
Wire Wire Line
	9150 6740 8940 6740
Wire Wire Line
	8940 6740 8940 6390
Connection ~ 8940 6390
Wire Wire Line
	8940 6390 8600 6390
Text Label 10000 6390 2    50   ~ 0
+5VD
Wire Wire Line
	10070 6090 10400 6090
Connection ~ 10070 6090
Wire Wire Line
	9600 5890 10150 5890
Wire Wire Line
	10150 3700 9600 3700
Wire Wire Line
	9600 4100 10150 4100
Connection ~ 10150 4100
Wire Wire Line
	10150 4100 10150 3700
Wire Wire Line
	9600 5490 10150 5490
Wire Wire Line
	10150 4100 10150 5490
Connection ~ 10150 5490
Wire Wire Line
	10150 5490 10150 5890
Wire Wire Line
	10150 5890 10400 5890
Connection ~ 10150 5890
Text Label 10400 5890 2    50   ~ 0
VIN
Text Label 10400 6090 2    50   ~ 0
GND
Text Label 8600 6390 0    50   ~ 0
CK7
Text Label 8600 4600 0    50   ~ 0
CK8
Wire Wire Line
	3270 6220 3450 6220
Wire Wire Line
	3270 6320 3450 6320
Text Label 3450 6320 2    50   ~ 0
CK7
Text Label 3450 6220 2    50   ~ 0
CK8
$Comp
L kicad_symbol_general:Conn_01x02 J40
U 1 1 5FC17101
P 3070 6320
F 0 "J40" H 3150 6312 50  0000 L CNN
F 1 "CK" H 3150 6221 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MCV_1,5_2-G-3.81_1x02_P3.81mm_Vertical" H 3070 6320 50  0001 C CNN
F 3 "" H 3070 6320 50  0001 C CNN
	1    3070 6320
	-1   0    0    1   
$EndComp
$Comp
L kicad_symbol_general:R_Small_US R10
U 1 1 5F29348B
P 10350 8445
F 0 "R10" H 10555 8400 50  0000 R CNN
F 1 "4.7k" H 10575 8480 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 10350 8445 50  0001 C CNN
F 3 "" H 10350 8445 50  0001 C CNN
	1    10350 8445
	-1   0    0    1   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D13
U 1 1 5F293AD8
P 10350 8645
F 0 "D13" V 10390 8885 50  0000 R CNN
F 1 "red" V 10310 8885 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 10350 8645 50  0001 C CNN
F 3 "" V 10350 8645 50  0001 C CNN
	1    10350 8645
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F2B1888
P 10350 8745
F 0 "#PWR0101" H 10350 8495 50  0001 C CNN
F 1 "GND" H 10355 8572 50  0000 C CNN
F 2 "" H 10350 8745 50  0001 C CNN
F 3 "" H 10350 8745 50  0001 C CNN
	1    10350 8745
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10350 8345 10350 8270
Connection ~ 10350 8270
Wire Wire Line
	10350 8270 10105 8270
Wire Wire Line
	10350 8270 10572 8270
$Comp
L kicad_symbol_general:R_Small_US R30
U 1 1 5F2DD794
P 1740 5500
F 0 "R30" V 1825 5680 50  0000 R CNN
F 1 "4.7k" V 1820 5510 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 5500 50  0001 C CNN
F 3 "" H 1740 5500 50  0001 C CNN
	1    1740 5500
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D30
U 1 1 5F2DDDCD
P 2040 5500
F 0 "D30" H 2130 5420 50  0000 R CNN
F 1 "red" H 1955 5410 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 5500 50  0001 C CNN
F 3 "" V 2040 5500 50  0001 C CNN
	1    2040 5500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 5500 1940 5500
Wire Wire Line
	1490 5500 1640 5500
Wire Wire Line
	2140 5500 2340 5500
$Comp
L kicad_symbol_general:R_Small_US R31
U 1 1 5F31B940
P 1740 5700
F 0 "R31" V 1825 5880 50  0000 R CNN
F 1 "4.7k" V 1820 5710 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 5700 50  0001 C CNN
F 3 "" H 1740 5700 50  0001 C CNN
	1    1740 5700
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D31
U 1 1 5F31B946
P 2040 5700
F 0 "D31" H 2130 5620 50  0000 R CNN
F 1 "red" H 1955 5610 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 5700 50  0001 C CNN
F 3 "" V 2040 5700 50  0001 C CNN
	1    2040 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 5700 1940 5700
Wire Wire Line
	1490 5700 1640 5700
Wire Wire Line
	2140 5700 2340 5700
$Comp
L kicad_symbol_general:R_Small_US R32
U 1 1 5F32A4F0
P 1740 5900
F 0 "R32" V 1825 6080 50  0000 R CNN
F 1 "4.7k" V 1820 5910 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 5900 50  0001 C CNN
F 3 "" H 1740 5900 50  0001 C CNN
	1    1740 5900
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D32
U 1 1 5F32A4F6
P 2040 5900
F 0 "D32" H 2130 5820 50  0000 R CNN
F 1 "red" H 1955 5810 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 5900 50  0001 C CNN
F 3 "" V 2040 5900 50  0001 C CNN
	1    2040 5900
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 5900 1940 5900
Wire Wire Line
	1490 5900 1640 5900
Wire Wire Line
	2140 5900 2340 5900
$Comp
L kicad_symbol_general:R_Small_US R33
U 1 1 5F339E91
P 1740 6100
F 0 "R33" V 1825 6280 50  0000 R CNN
F 1 "4.7k" V 1820 6110 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 6100 50  0001 C CNN
F 3 "" H 1740 6100 50  0001 C CNN
	1    1740 6100
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D33
U 1 1 5F339E97
P 2040 6100
F 0 "D33" H 2130 6020 50  0000 R CNN
F 1 "red" H 1955 6010 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 6100 50  0001 C CNN
F 3 "" V 2040 6100 50  0001 C CNN
	1    2040 6100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 6100 1940 6100
Wire Wire Line
	1490 6100 1640 6100
Wire Wire Line
	2140 6100 2340 6100
Wire Wire Line
	1490 5500 1490 5700
Connection ~ 1490 5700
Wire Wire Line
	1490 5700 1490 5900
Connection ~ 1490 5900
Wire Wire Line
	1490 5900 1490 6100
Connection ~ 1490 6100
Wire Wire Line
	1490 6100 1490 6300
$Comp
L kicad_symbol_general:R_Small_US R34
U 1 1 5F392041
P 1740 6300
F 0 "R34" V 1825 6480 50  0000 R CNN
F 1 "4.7k" V 1820 6310 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 6300 50  0001 C CNN
F 3 "" H 1740 6300 50  0001 C CNN
	1    1740 6300
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D34
U 1 1 5F392047
P 2040 6300
F 0 "D34" H 2130 6220 50  0000 R CNN
F 1 "red" H 1955 6210 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 6300 50  0001 C CNN
F 3 "" V 2040 6300 50  0001 C CNN
	1    2040 6300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 6300 1940 6300
Wire Wire Line
	1490 6300 1640 6300
Wire Wire Line
	2140 6300 2340 6300
Connection ~ 1490 6300
Wire Wire Line
	1490 6300 1490 6520
$Comp
L kicad_symbol_general:R_Small_US R35
U 1 1 5F3C5EB0
P 1740 6520
F 0 "R35" V 1825 6700 50  0000 R CNN
F 1 "4.7k" V 1820 6530 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 6520 50  0001 C CNN
F 3 "" H 1740 6520 50  0001 C CNN
	1    1740 6520
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D35
U 1 1 5F3C5EB6
P 2040 6520
F 0 "D35" H 2130 6440 50  0000 R CNN
F 1 "red" H 1955 6430 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 6520 50  0001 C CNN
F 3 "" V 2040 6520 50  0001 C CNN
	1    2040 6520
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 6520 1940 6520
Wire Wire Line
	1490 6520 1640 6520
Wire Wire Line
	2140 6520 2340 6520
Connection ~ 1490 6520
Wire Wire Line
	1490 6520 1490 6750
$Comp
L kicad_symbol_general:R_Small_US R36
U 1 1 5F3FC086
P 1740 6750
F 0 "R36" V 1825 6930 50  0000 R CNN
F 1 "4.7k" V 1820 6760 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 6750 50  0001 C CNN
F 3 "" H 1740 6750 50  0001 C CNN
	1    1740 6750
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D36
U 1 1 5F3FC08C
P 2040 6750
F 0 "D36" H 2130 6670 50  0000 R CNN
F 1 "red" H 1955 6660 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 6750 50  0001 C CNN
F 3 "" V 2040 6750 50  0001 C CNN
	1    2040 6750
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 6750 1940 6750
Wire Wire Line
	1490 6750 1640 6750
Wire Wire Line
	2140 6750 2340 6750
Connection ~ 1490 6750
Wire Wire Line
	1490 6750 1490 6985
$Comp
L kicad_symbol_general:R_Small_US R37
U 1 1 5F445EA4
P 1740 6985
F 0 "R37" V 1825 7165 50  0000 R CNN
F 1 "4.7k" V 1820 6995 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 6985 50  0001 C CNN
F 3 "" H 1740 6985 50  0001 C CNN
	1    1740 6985
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D37
U 1 1 5F445EAA
P 2040 6985
F 0 "D37" H 2130 6905 50  0000 R CNN
F 1 "red" H 1955 6895 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 6985 50  0001 C CNN
F 3 "" V 2040 6985 50  0001 C CNN
	1    2040 6985
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 6985 1940 6985
Wire Wire Line
	1490 6985 1640 6985
Wire Wire Line
	2140 6985 2340 6985
Connection ~ 1490 6985
Wire Wire Line
	1490 6985 1490 7200
$Comp
L kicad_symbol_general:R_Small_US R38
U 1 1 5F493904
P 1740 7200
F 0 "R38" V 1825 7380 50  0000 R CNN
F 1 "4.7k" V 1820 7210 50  0000 R CNN
F 2 "kicad_footprint_general:R_0603_1608Metric" H 1740 7200 50  0001 C CNN
F 3 "" H 1740 7200 50  0001 C CNN
	1    1740 7200
	0    -1   -1   0   
$EndComp
$Comp
L kicad_symbol_general:LED_Small D38
U 1 1 5F49390A
P 2040 7200
F 0 "D38" H 2130 7120 50  0000 R CNN
F 1 "red" H 1955 7110 50  0000 R CNN
F 2 "kicad_footprint_general:LED_0603_1608Metric" V 2040 7200 50  0001 C CNN
F 3 "" V 2040 7200 50  0001 C CNN
	1    2040 7200
	-1   0    0    1   
$EndComp
Wire Wire Line
	1840 7200 1940 7200
Wire Wire Line
	1490 7200 1640 7200
Wire Wire Line
	2140 7200 2340 7200
Wire Wire Line
	1490 5500 1250 5500
Connection ~ 1490 5500
Text Label 1250 5500 0    50   ~ 0
+5VD
Text Label 2340 5500 2    50   ~ 0
CK0
Text Label 2340 5700 2    50   ~ 0
CK1
Text Label 2340 5900 2    50   ~ 0
CK2
Text Label 2340 6100 2    50   ~ 0
CK3
Text Label 2340 6300 2    50   ~ 0
CK4
Text Label 2340 6520 2    50   ~ 0
CK5
Text Label 2340 6750 2    50   ~ 0
CK6
Text Label 2340 6985 2    50   ~ 0
CK7
Text Label 2340 7200 2    50   ~ 0
CK8
$EndSCHEMATC
