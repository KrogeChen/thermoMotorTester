EESchema Schematic File Version 4
EELAYER 30 0
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
L kicad_symbol_general:Conn_01x01 J2
U 1 1 5F6E9311
P 6200 3600
F 0 "J2" H 6280 3642 50  0000 L CNN
F 1 "Conn_01x01" H 6280 3551 50  0000 L CNN
F 2 "kicad_footprint_general:H_oneHole" H 6200 3600 50  0001 C CNN
F 3 "" H 6200 3600 50  0001 C CNN
	1    6200 3600
	1    0    0    -1  
$EndComp
$Comp
L kicad_symbol_general:Conn_01x01 J1
U 1 1 5F6E95BB
P 5200 3600
F 0 "J1" H 5118 3375 50  0000 C CNN
F 1 "Conn_01x01" H 5118 3466 50  0000 C CNN
F 2 "kicad_footprint_general:H_oneHole" H 5200 3600 50  0001 C CNN
F 3 "" H 5200 3600 50  0001 C CNN
	1    5200 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	6000 3870 5900 3870
Wire Wire Line
	5900 3600 6000 3600
Wire Wire Line
	5400 3600 5900 3600
Connection ~ 5900 3600
Wire Wire Line
	5900 3870 5900 3600
$Comp
L kicad_symbol_general:Conn_01x01 J3
U 1 1 5F6EB23D
P 6200 3870
F 0 "J3" H 6280 3912 50  0000 L CNN
F 1 "Conn_01x01" H 6280 3821 50  0000 L CNN
F 2 "kicad_footprint_general:H_oneHole" H 6200 3870 50  0001 C CNN
F 3 "" H 6200 3870 50  0001 C CNN
	1    6200 3870
	1    0    0    -1  
$EndComp
$EndSCHEMATC
