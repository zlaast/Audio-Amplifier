#ifndef CONSTANTS_H
#define CONSTANTS_H

// ROTARY ENCODER: VOLUME PINS [MCU INPUTS]
const int kPinVolumeDown    =   PIN_PB0;
const int kPinVolumeUp      =   PIN_PB1;
const int kPinMuteBtn       =   PIN_PB3;

// ROTARY ENCODER: SPEAKER SELECT PINS [MCU INPUTS]
const int kPinPhonicBtn     =   PIN_PB2;
const int kPinSpeakerPrev   =   PIN_PB4;
const int kPinSpeakerNext   =   PIN_PB5;

// AUDIO SWITCHES: SIGNALS [MCU OUTPUTS]
const int kPinPhonicA       =   PIN_PB6;
const int kPinPhonicB       =   PIN_PB7;

// AMPLIFIER BOARD: SIGNALS [MCU OUTPUTS]
const int kPinAmpMuteA      =   PIN_PD0;
const int kPinAmpStandbyA   =   PIN_PD1;
const int kPinAmpMuteB      =   PIN_PD2;
const int kPinAmpStandbyB   =   PIN_PD3;

// DIGITAL POTENTIOMETER I2C ADDRESSES
const uint8_t kPotA = 0x28;
const uint8_t kPotB = 0x29;

// EEPROM ADDRESSES
const uint8_t kAddressAttenA1 = 0;
const uint8_t kAddressAttenA2 = 1;
const uint8_t kAddressAttenB1 = 2;
const uint8_t kAddressAttenB2 = 3;
const uint8_t kAddressPhonicA = 4;
const uint8_t kAddressPhonicB = 5;
const uint8_t kAddressMuteA   = 6;
const uint8_t kAddressMuteB   = 7;

// MAX AND MIN DIGITAL POT ATTENUATION VALUES
const uint8_t kMinAtten1 = 0;       // Volume 1 min attenuation (max volume)
const uint8_t kMaxAtten1 = 63;      // Volume 1 max attenuation (min volume)
const uint8_t kMinAtten2 = 64;      // Volume 2 min attenuation (max volume)
const uint8_t kMaxAtten2 = 127;     // Volume 2 max attenuation (min volume)

// CLOCKWISE AND COUNTER-CLOCKWISE RETURNS
const int8_t kCW = -1;
const int8_t kCCW = 1;

// SELECTIONS
const uint8_t kSelect_All = 0;
const uint8_t kSelect_A = 1;
const uint8_t kSelect_B = 2;

// TIMERS AND DELAYS
const long kSaveStateTime = 900000;    // 15 minutes (900000 ms)

#endif