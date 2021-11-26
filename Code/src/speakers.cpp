#include "speakers.h"

void Speakers::begin_(uint8_t i2c_pot,
                      uint8_t address_muted, 
                      uint8_t address_phonic, 
                      uint8_t address_volume_1, 
                      uint8_t address_volume_2, 
                      int pin_mute, 
                      int pin_standby, 
                      int pin_phonic)
{
    // Save arguments to members
    this->i2c_pot = i2c_pot;
    this->pin_mute = pin_mute;
    this->pin_standby = pin_standby;
    this->pin_phonic = pin_phonic;

    // Retrieve data from EEPROM
    EEPROM.get(address_muted, muted);
    EEPROM.get(address_phonic, stereo);
    EEPROM.get(address_volume_1, volume_1);
    EEPROM.get(address_volume_2, volume_2);

    // Set pins to output data
    pinMode(this->pin_mute,    OUTPUT);
    pinMode(this->pin_standby, OUTPUT);
    pinMode(this->pin_phonic,  OUTPUT);

    // Write volumes to the pot
    Wire.beginTransmission(this->i2c_pot);
    Wire.write(0b10000110);
    Wire.write(volume_1);
    Wire.write(volume_2);
    Wire.endTransmission();

    // Set mute state
    mute_();

    // Set phonic state
    change_phonic_(true);
}

void Speakers::mute_()
{
    if (!muted)
    {
        speakers_on_(false);
        muted = true;
    }
    else
    {
        speakers_on_(true);
        muted = false;
    }
}

void Speakers::change_volume_(int8_t offset)
{
    if (!muted)
    {
        if (offset)
        {
            muted = false;
            volume_1 += offset;
            volume_2 += offset;

            // Volume 1 checks
            if (volume_1 > kMaxAtten2)              // Volume 1 has overflowed! So...
                volume_1 = kMinAtten1;              // ...set it back to min attenuation
            if (volume_1 > kMaxAtten1)
                volume_1 = kMaxAtten1;

            // Volume 2 checks
            if (volume_2 < kMinAtten2)
                volume_2 = kMinAtten2;
            if (volume_2 > kMaxAtten2)
                volume_2 = kMaxAtten2;

            Wire.beginTransmission(i2c_pot);
            Wire.write((uint8_t)volume_1);
            Wire.write((uint8_t)volume_2);
            Wire.endTransmission();
        }
    }
}

void Speakers::speakers_on_(bool on)
{
    if (on)
    {
        digitalWrite(pin_standby, HIGH);
        delay(150);
        digitalWrite(pin_mute, HIGH);
        speakers_on = true;
    }
    else
    {
        digitalWrite(pin_mute, LOW);
        delay(150);
        digitalWrite(pin_standby, LOW);
        speakers_on = false;
    }
}

void Speakers::change_phonic_(bool override)
{
    if (!muted)
    {
        speakers_on_(false);
        digitalWrite(pin_phonic, stereo);   // stereo is boolean. So FALSE = LOW, TRUE = HIGH
        speakers_on_(true);
        stereo = !stereo;
    }

    if (override)
    {
        speakers_on_(false);
        digitalWrite(pin_phonic, stereo);
        speakers_on_(true);
        stereo = !stereo;
    }
}