/*
 *  © 2021 Neil McKechnie
 *  © 2020-2021 Harald Barth
 *  © 2020-2021 Fred Decker
 *  © 2020-2021 Chris Harlow
 *  
 *  This file is part of CommandStation-EX
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CommandStation.  If not, see <https://www.gnu.org/licenses/>.
 */

// DRL: Begin
#include "DRLDefines.h"
// DRL: End

/**********************************************************************

The configuration file for DCC-EX Command Station

**********************************************************************/

/////////////////////////////////////////////////////////////////////////////////////
//  NOTE: Before connecting these boards and selecting one in this software
//        check the quick install guides!!! Some of these boards require a voltage
//        generating resistor on the current sense pin of the device. Failure to select
//        the correct resistor could damage the sense pin on your Arduino or destroy
//        the device.
//
// DEFINE MOTOR_SHIELD_TYPE BELOW ACCORDING TO THE FOLLOWING TABLE:
//
//  STANDARD_MOTOR_SHIELD : Arduino Motor shield Rev3 based on the L298 with 18V 2A per channel
//  POLOLU_MOTOR_SHIELD   : Pololu MC33926 Motor Driver (not recommended for prog track)
//  FUNDUMOTO_SHIELD      : Fundumoto Shield, no current sensing (not recommended, no short protection)
//  FIREBOX_MK1           : The Firebox MK1                    
//  FIREBOX_MK1S          : The Firebox MK1S
//  IBT_2_WITH_ARDUINO    : Arduino Motor Shield for PROG and IBT-2 for MAIN
//   |
//   +-----------------------v
//
// DRL: Begin
// {ADD_DRIVER
#if !defined(ADD_DRIVER)
// DRL: End
#define MOTOR_SHIELD_TYPE STANDARD_MOTOR_SHIELD
// Per Decker's recommendations (high accuracy waveforms for MEGA are pins 11, 12, and 13)
// This motor shield is for the PMA Tx
// DRL: Begin
// } ADD_DRIVER
#else
// { ADD_DRIVER - not
// { TRANSMITTER
#if defined(TRANSMITTER)
#if defined(ARDUINO_ARCH_ESP32)
#pragma message "Using ESP32 Tx MotorDriver"
#define PMA_TX F("PMA_Tx"), \
     new MotorDriver(25/* 3*/, 19/*12*/, UNUSED_PIN, UNUSED_PIN, UNUSED_PIN, 1.0, 1100, UNUSED_PIN), \
     new MotorDriver(23/*11*/, 18/*13*/, UNUSED_PIN, UNUSED_PIN, UNUSED_PIN, 1.0, 1100, UNUSED_PIN)
#else
#pragma message "Using AVR Tx MotorDriver"
#define PMA_TX F("PMA_Tx"), \
     new MotorDriver(3,  12, UNUSED_PIN, UNUSED_PIN, UNUSED_PIN, 1.0, 1100, UNUSED_PIN), \
     new MotorDriver(11, 13, UNUSED_PIN, UNUSED_PIN, UNUSED_PIN, 1.0, 1100, UNUSED_PIN)
#endif
#define MOTOR_SHIELD_TYPE PMA_TX 
#pragma message "Using MotorDriver PMA_Tx"
// } TRANSMITTER
#else
// { TRANSMITTER - not
#if defined(ARDUINO_ARCH_ESP32)
#pragma message "Using ESP32 Rx MotorDriver"
// EX 8874 based shield connected to a 3.3V system (like ESP32) and 12bit (4096) ADC
// numbers are GPIO numbers. comments are UNO form factor shield pin numbers
#define EX8874_SHIELD_RX   F("EX8874_Rx_ESP32"),\
 new MotorDriver(26    /* 3*/, 19/*12*/, 22, 12/*12, 9*/, 35/*35, A2*/, 1.27, 50000, UNUSED_PIN/*-33, 36, A4*/), \
 new MotorDriver(25/*23, 11*/, 18/*13*/, 21, 13/*13, 8*/, 34/*34, A3*/, 1.27, 50000, UNUSED_PIN/*-32, 39, A5*/)
#define EXTB9053_SHIELD_RX F("EXTB9053_Rx_ESP32_1.27"),\
 new MotorDriver(26    /* 3*/, 19/*12*/, 22, 12/*12, 9*/, 35/*35, A2*/, 1.27, 50000, UNUSED_PIN/*-33, 36, A4*/), \
 new MotorDriver(25/*23, 11*/, 18/*13*/, 21, 13/*13, 8*/, 34/*34, A3*/, 1.27, 50000, UNUSED_PIN/*-32, 39, A5*/)
#else
#pragma message "Using AVR Rx MotorDriver"
// EX 8874 based shield connected to a 5V system (like Arduino) and 10bit (1024) ADC
#define EX8874_SHIELD_RX   F("EX8874_Rx_AVR"), \
 new MotorDriver( 3, 12, UNUSED_PIN, 9, A0, 5.08, 5000, A4), \
 new MotorDriver(11, 13, UNUSED_PIN, 8, A1, 5.08, 5000, A5)
#define EXTB9053_SHIELD_RX F("EXTB9053_Rx_AVR"), \
 new MotorDriver( 3, 12, UNUSED_PIN, 9, A0, 5.08, 5000, A4), \
 new MotorDriver(11, 13, UNUSED_PIN, 8, A1, 5.08, 5000, A5)
#endif
#define MOTOR_SHIELD_TYPE EXTB9053_SHIELD_RX
#pragma message "Using MotorDriver EXTSB_SHIELD_RX"
#endif
// } RECEIVR
#endif
// }ADD_DRIVER
// DRL: End

/////////////////////////////////////////////////////////////////////////////////////
//
// The IP port to talk to a WIFI or Ethernet shield.
//
#define IP_PORT 2560

/////////////////////////////////////////////////////////////////////////////////////
//
// NOTE: Only supported on Arduino Mega
// Set to false if you not even want it on the Arduino Mega
//
#define ENABLE_WIFI true

/////////////////////////////////////////////////////////////////////////////////////
//
// DEFINE WiFi Parameters (only in effect if WIFI is on)
//
// If DONT_TOUCH_WIFI_CONF is set, all WIFI config will be done with
// the <+> commands and this sketch will not change anything over
// AT commands and the other WIFI_* defines below do not have any effect.
//#define DONT_TOUCH_WIFI_CONF
//
// WIFI_SSID is the network name IF you want to use your existing home network.
// Do NOT change this if you want to use the WiFi in Access Point (AP) mode. 
//
// If you do NOT set the WIFI_SSID and do NOT set the WIFI_PASSWORD,
// then the WiFi chip will first try to connect to the previously
// configured network and if that fails fall back to Access Point mode.
// The SSID of the AP will be automatically set to DCCEX_*.
// If you DO set the WIFI_SSID then the WiFi chip will try to connect
// to that (home) network in station (client) mode. If a WIFI_PASSWORD
// is set (recommended), that password will be used for AP mode.
// The AP mode password must be at least 8 characters long.
//
// Your SSID may not contain ``"'' (double quote, ASCII 0x22).
#define WIFI_SSID "Your network name"
//
// WIFI_PASSWORD is the network password for your home network or if
// you want to change the password from default AP mode password
// to the AP password you want. 
// Your password may not contain ``"'' (double quote, ASCII 0x22).
#define WIFI_PASSWORD "Your network passwd"
//
// WIFI_HOSTNAME: You probably don't need to change this
#define WIFI_HOSTNAME "dccex"
//
// WIFI_CHANNEL: If the line "#define ENABLE_WIFI true" is uncommented, 
// WiFi will be enabled (Mega only). The default channel is set to "1" whether
// this line exists or not. If you need to use an alternate channel (we recommend
// using only 1,6, or 11) you may change it here.
#define WIFI_CHANNEL 1

/////////////////////////////////////////////////////////////////////////////////////
//
// ENABLE_ETHERNET: Set to true if you have an Arduino Ethernet card (wired). This
// is not for Wifi. You will then need the Arduino Ethernet library as well
//
//#define ENABLE_ETHERNET true


/////////////////////////////////////////////////////////////////////////////////////
//
// DEFINE STATIC IP ADDRESS *OR* COMMENT OUT TO USE DHCP
//
//#define IP_ADDRESS { 192, 168, 1, 200 }


/////////////////////////////////////////////////////////////////////////////////////
//
// DEFINE LCD SCREEN USAGE BY THE BASE STATION
//
// Note: This feature requires an I2C enabled LCD screen using a Hitachi HD44780
//       controller and a commonly available PCF8574 based I2C 'backpack'.
// To enable, uncomment one of the #define lines below

// define LCD_DRIVER for I2C address 0x27, 16 cols, 2 rows
// #define LCD_DRIVER  0x27,16,2

//OR define OLED_DRIVER width,height in pixels (address auto detected)
// 128x32 or 128x64 I2C SSD1306-based devices are supported.
// Use 132,64 for a SH1106-based I2C device with a 128x64 display.
// DRL: Begin
#if defined ADD_OLED
#define OLED_DRIVER 128,32
#endif
// DRL: End

// Define scroll mode as 0, 1 or 2
//  *  #define SCROLLMODE 0 is scroll continuous (fill screen if poss),
//  *  #define SCROLLMODE 1 is by page (alternate between pages),
//  *  #define SCROLLMODE 2 is by row (move up 1 row at a time).
// DRL: Begin
#if defined ADD_OLED
#define SCROLLMODE 1
#endif
// DRL: End

/////////////////////////////////////////////////////////////////////////////////////
// DISABLE EEPROM
//
// If you do not need the EEPROM at all, you can disable all the code that saves
// data in the EEPROM. You might want to do that if you are in a Arduino UNO
// and want to use the EX-RAIL automation. Otherwise you do not have enough RAM
// to do that. Of course, then none of the EEPROM related commands work.
//
// #define DISABLE_EEPROM

/////////////////////////////////////////////////////////////////////////////////////
// REDEFINE WHERE SHORT/LONG ADDR break is. According to NMRA the last short address
// is 127 and the first long address is 128. There are manufacturers which have
// another view. Lenz CS for example have considered addresses long from 100. If
// you want to change to that mode, do 
//#define HIGHEST_SHORT_ADDR 99
// If you want to run all your locos addressed long format, you could even do a 
//#define HIGHEST_SHORT_ADDR 0
// We do not support to use the same address, for example 100(long) and 100(short)
// at the same time, there must be a border.

/////////////////////////////////////////////////////////////////////////////////////
//
// DEFINE TURNOUTS/ACCESSORIES FOLLOW NORM RCN-213
//
// According to norm RCN-213 a DCC packet with a 1 is closed/straight
// and one with a 0 is thrown/diverging.  In DCC++ Classic, and in previous
// versions of DCC++EX, a turnout throw command was implemented in the packet as 
// '1' and a close command as '0'. The #define below makes the states
// match with the norm.  But we don't want to cause havoc on existent layouts,
// so we define this only for new installations. If you don't want this,
// don't add it to your config.h.
//#define DCC_TURNOUTS_RCN_213

// By default, the driver which defines a DCC accessory decoder
// does send out the same state change on the DCC packet as it
// receives. This means a VPIN state=1 sends D=1 (close turnout
// or signal green) in the DCC packet. This can be reversed if
// necessary.
//#define HAL_ACCESSORY_COMMAND_REVERSE

// If you have issues with that the direction of the accessory commands is
// reversed (for example when converting from another CS to DCC-EX) then
// you can use this to reverse the sense of all accessory commmands sent
// over DCC++. This #define likewise inverts the behaviour of the <a> command
// for triggering DCC Accessory Decoders, so that <a addr subaddr 0> generates a
// DCC packet with D=1 (close turnout) and <a addr subaddr 1> generates D=0 
// (throw turnout).
//#define DCC_ACCESSORY_RCN_213
//
// HANDLING MULTIPLE SERIAL THROTTLES
// The command station always operates with the default Serial port.
// Diagnostics are only emitted on the default serial port and not broadcast.
// Other serial throttles may be added to the Serial1, Serial2, Serial3 ports
// which may or may not exist on your CPU. (Mega has all 3)
// To monitor a throttle on one or more serial ports, uncomment the defines below.
// NOTE: do not define here the WiFi shield serial port or your wifi will not work.
//
//#define SERIAL1_COMMANDS
//#define SERIAL2_COMMANDS
//#define SERIAL3_COMMANDS

/////////////////////////////////////////////////////////////////////////////////////
