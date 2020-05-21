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
Text Label 10800 6050 0    50   ~ 0
AC24V
Text Label 10800 5950 0    50   ~ 0
AC36V
Text Label 10800 5850 0    50   ~ 0
AC110V
Text Label 10800 5750 0    50   ~ 0
AC220V
Text Label 10800 5650 0    50   ~ 0
AC_N
Wire Wire Line
	10800 5750 11150 5750
Wire Wire Line
	10800 5850 11150 5850
Wire Wire Line
	10800 5950 11150 5950
Wire Wire Line
	10800 6050 11150 6050
Wire Wire Line
	10800 6150 11150 6150
Wire Wire Line
	11150 5650 10800 5650
Text Label 10800 6150 0    50   ~ 0
AC12V
$Comp
L kicad_symbol_general:Conn_01x04 J71
U 1 1 5EEE586E
P 11350 6400
F 0 "J71" H 11430 6392 50  0000 L CNN
F 1 "PM9808_L" H 11430 6301 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBA_2,5_4-G_1x04_P5.00mm_Horizontal" H 11350 6400 50  0001 C CNN
F 3 "" H 11350 6400 50  0001 C CNN
	1    11350 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	11150 6300 10800 6300
Wire Wire Line
	11150 6400 10800 6400
Wire Wire Line
	11150 6500 10800 6500
Wire Wire Line
	11150 6600 10800 6600
Text Label 10800 6600 0    50   ~ 0
L_OUT
Text Label 10800 6500 0    50   ~ 0
N_OUT
Text Label 10800 6400 0    50   ~ 0
L_FK
Text Label 10800 6300 0    50   ~ 0
N_FK
$Comp
L kicad_symbol_general:Conn_01x02 J72
U 1 1 5EF2C114
P 11350 6750
F 0 "J72" H 11430 6742 50  0000 L CNN
F 1 "actuator" H 11430 6651 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBA_2,5_2-G_1x02_P5.00mm_Horizontal" H 11350 6750 50  0001 C CNN
F 3 "" H 11350 6750 50  0001 C CNN
	1    11350 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11150 6850 10800 6850
Wire Wire Line
	11150 6750 10800 6750
Text Label 10800 6850 0    50   ~ 0
L_ACT
Text Label 10800 6750 0    50   ~ 0
N_ACT
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K16
U 1 1 5EC07506
P 7000 10050
F 0 "K16" V 7725 9850 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 9850 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 10050 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 10050 50  0001 C CNN
	1    7000 10050
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K10
U 1 1 5F3B5F45
P 7000 1550
F 0 "K10" V 7725 1350 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 1350 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 1550 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 1550 50  0001 C CNN
	1    7000 1550
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K11
U 1 1 5EC4316B
P 7000 2950
F 0 "K11" V 7725 2750 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 2750 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 2950 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 2950 50  0001 C CNN
	1    7000 2950
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K12
U 1 1 5EC442C8
P 7000 4375
F 0 "K12" V 7725 4175 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 4175 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 4375 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 4375 50  0001 C CNN
	1    7000 4375
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K13
U 1 1 5EC44D7B
P 7000 5800
F 0 "K13" V 7725 5600 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 5600 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 5800 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 5800 50  0001 C CNN
	1    7000 5800
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K14
U 1 1 5EC4590E
P 7000 7200
F 0 "K14" V 7725 7000 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 7000 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 7200 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 7200 50  0001 C CNN
	1    7000 7200
	0    1    -1   0   
$EndComp
$Comp
L kicad_symbol_general:HF115-024-2ZS4 K15
U 1 1 5EC488CD
P 7000 8625
F 0 "K15" V 7725 8425 50  0000 L CNN
F 1 "HF115-005-2ZS4" V 7650 8425 50  0000 L CNN
F 2 "kicad_footprint_general:Relay_DPDT_Schrack-RT2-FormC_RM5mm" H 7000 8625 50  0001 C CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FRT2%7F1014%7Fpdf%7FEnglish%7FENG_DS_RT2_1014.pdf%7F6-1393243-3" H 7000 8625 50  0001 C CNN
	1    7000 8625
	0    1    -1   0   
$EndComp
Wire Wire Line
	7300 1050 7650 1050
Wire Wire Line
	7650 1050 7650 2450
Wire Wire Line
	7300 2450 7650 2450
Connection ~ 7650 2450
Wire Wire Line
	7650 2450 7650 3875
Wire Wire Line
	7300 3875 7650 3875
Connection ~ 7650 3875
Wire Wire Line
	7300 5300 7650 5300
Wire Wire Line
	7650 3875 7650 5300
Connection ~ 7650 5300
Wire Wire Line
	7650 5300 7650 6700
Wire Wire Line
	7300 6700 7650 6700
Connection ~ 7650 6700
Wire Wire Line
	7650 6700 7650 6875
Wire Wire Line
	6700 1150 6425 1150
Wire Wire Line
	7300 1650 7375 1650
Text Label 7550 1650 2    50   ~ 0
+VRLY
Wire Wire Line
	6700 1550 6425 1550
Text Label 6425 1550 0    50   ~ 0
K11CV
Text Label 7550 3050 2    50   ~ 0
K11CV
Wire Wire Line
	7300 1950 7375 1950
Wire Wire Line
	7375 1950 7375 1650
Connection ~ 7375 1650
Wire Wire Line
	7375 1650 7550 1650
Wire Wire Line
	7300 3050 7550 3050
Wire Wire Line
	7300 3050 7300 3350
Connection ~ 7300 3050
Wire Wire Line
	6700 2950 6425 2950
Text Label 6425 2950 0    50   ~ 0
K12CV
Wire Wire Line
	6700 2550 6425 2550
Wire Wire Line
	6700 3975 6425 3975
Wire Wire Line
	6700 5400 6425 5400
Wire Wire Line
	6700 6800 6425 6800
Wire Wire Line
	6700 8225 6425 8225
Text Label 6425 1150 0    50   ~ 0
AC12V
Text Label 6425 2550 0    50   ~ 0
AC24V
Text Label 6425 3975 0    50   ~ 0
AC36V
Text Label 6425 5400 0    50   ~ 0
AC110V
Text Label 6425 6800 0    50   ~ 0
AC220V
Text Label 6425 8225 0    50   ~ 0
AC_N
Wire Wire Line
	7300 8125 8000 8125
Wire Wire Line
	7650 6875 7975 6875
Text Label 7975 6875 2    50   ~ 0
L_OUT
Text Label 8000 8125 2    50   ~ 0
N_OUT
Wire Wire Line
	7300 5900 7550 5900
Wire Wire Line
	7300 6200 7300 5900
Connection ~ 7300 5900
Wire Wire Line
	6700 5800 6425 5800
Text Label 7550 5900 2    50   ~ 0
K13CV
Wire Wire Line
	7300 4475 7550 4475
Wire Wire Line
	7300 4775 7300 4475
Connection ~ 7300 4475
Text Label 7550 4475 2    50   ~ 0
K12CV
Wire Wire Line
	6700 4375 6425 4375
Text Label 6425 4375 0    50   ~ 0
K13CV
Wire Wire Line
	7300 7300 7550 7300
Wire Wire Line
	7300 7600 7300 7300
Connection ~ 7300 7300
Text Label 6425 5800 0    50   ~ 0
K14CV
Text Label 7550 7300 2    50   ~ 0
K14CV
Wire Wire Line
	6700 10050 6325 10050
Wire Wire Line
	6700 9650 6325 9650
Wire Wire Line
	7300 9550 7625 9550
Wire Wire Line
	7300 9950 7650 9950
Text Label 6325 9650 0    50   ~ 0
L_FK
Text Label 6325 10050 0    50   ~ 0
N_FK
Text Label 7625 9550 2    50   ~ 0
L_ACT
Text Label 7650 9950 2    50   ~ 0
N_ACT
Wire Wire Line
	6700 1950 6425 1950
Wire Wire Line
	6700 3350 6425 3350
Wire Wire Line
	6700 4775 6425 4775
Wire Wire Line
	6700 6200 6425 6200
Wire Wire Line
	6700 7600 6425 7600
Wire Wire Line
	6700 9025 6425 9025
Wire Wire Line
	6700 10450 6400 10450
Wire Wire Line
	7300 9025 7500 9025
Wire Wire Line
	7300 10450 7500 10450
Text Label 6425 1950 0    50   ~ 0
C_CK0
Text Label 6425 3350 0    50   ~ 0
C_CK1
Text Label 6425 4775 0    50   ~ 0
C_CK2
Text Label 6425 7600 0    50   ~ 0
C_CK4
Text Label 6425 9025 0    50   ~ 0
C_CK5
Text Label 6425 6200 0    50   ~ 0
C_CK3
Text Label 6400 10450 0    50   ~ 0
C_CK6
$Comp
L kicad_symbol_general:Conn_01x06 J70
U 1 1 5FB11F45
P 11350 5850
F 0 "J70" H 11430 5842 50  0000 L CNN
F 1 "transformer" H 11430 5751 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBA_2,5_6-G_1x06_P5.00mm_Horizontal" H 11350 5850 50  0001 C CNN
F 3 "~" H 11350 5850 50  0001 C CNN
	1    11350 5850
	1    0    0    -1  
$EndComp
NoConn ~ 7300 1250
NoConn ~ 7300 1450
NoConn ~ 7300 2650
NoConn ~ 7300 2850
NoConn ~ 7300 4075
NoConn ~ 7300 4275
NoConn ~ 7300 5500
NoConn ~ 7300 5700
NoConn ~ 7300 6900
NoConn ~ 7300 7100
NoConn ~ 7300 9750
NoConn ~ 7300 10150
NoConn ~ 6700 7200
NoConn ~ 6700 8625
NoConn ~ 7300 8325
NoConn ~ 7300 8525
NoConn ~ 7300 8725
$Comp
L kicad_symbol_general:Conn_01x05 J21
U 1 1 626713F3
P 3800 6100
F 0 "J21" H 3880 6142 50  0000 L CNN
F 1 "relay" H 3880 6051 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBA_2,5_5-G_1x05_P5.00mm_Horizontal" H 3800 6100 50  0001 C CNN
F 3 "~" H 3800 6100 50  0001 C CNN
	1    3800 6100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 6300 4350 6300
Wire Wire Line
	4000 6200 4350 6200
Wire Wire Line
	4000 6100 4350 6100
Wire Wire Line
	4000 6000 4350 6000
Wire Wire Line
	4000 5900 4350 5900
Text Label 4350 5900 2    50   ~ 0
+VRLY
$Comp
L kicad_symbol_general:Conn_01x04 J22
U 1 1 62671403
P 3800 5375
F 0 "J22" H 3880 5367 50  0000 L CNN
F 1 "relay" H 3880 5276 50  0000 L CNN
F 2 "kicad_footprint_general:PhoenixContact_MSTBA_2,5_4-G_1x04_P5.00mm_Horizontal" H 3800 5375 50  0001 C CNN
F 3 "" H 3800 5375 50  0001 C CNN
	1    3800 5375
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 5575 4350 5575
Text Label 4350 5275 2    50   ~ 0
+VRLY
Wire Wire Line
	4000 5475 4350 5475
Wire Wire Line
	4000 5375 4350 5375
Text Label 4350 5375 2    50   ~ 0
C_CK0
Text Label 4350 5475 2    50   ~ 0
C_CK1
Text Label 4350 5575 2    50   ~ 0
C_CK2
Text Label 4350 6000 2    50   ~ 0
C_CK3
Text Label 4350 6100 2    50   ~ 0
C_CK4
Text Label 4350 6200 2    50   ~ 0
C_CK5
Text Label 4350 6300 2    50   ~ 0
C_CK6
Wire Wire Line
	4000 5275 4350 5275
Text Label 7500 9025 2    50   ~ 0
+VRLY
Text Label 7500 10450 2    50   ~ 0
+VRLY
$EndSCHEMATC
