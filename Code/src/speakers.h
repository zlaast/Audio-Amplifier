////////////////////////////////////////////////////////////////////////
// NAME:               speakers.h
//
// PURPOSE:            Controls the speakers. Functions includes
//                     volume control, muting, abd speakers on/off
//
// AUTHOR:             Z'Laast Allicock
////////////////////////////////////////////////////////////////////////

#ifndef SPEAKERS_H
#define SPEAKERS_H

#include <Wire.h>
#include <EEPROM.h>
#include "constants.h"

class Speakers
{
    public:
        void begin_(uint8_t i2c_pot,
                    uint8_t address_muted,
                    uint8_t address_phonic,
                    uint8_t address_volume_1,
                    uint8_t address_volume_2,
                    int pin_mute,
                    int pin_standby,
                    int pin_phonic);

        bool check_if_muted_()   const { return muted;    }
        bool check_if_stereo_()  const { return stereo;   }
        int get_attenuation_1_() const { return volume_1; }
        int get_attenuation_2_() const { return volume_2; }

        void mute_();
        void change_volume_(int8_t offset);
        void change_phonic_(bool override = false);
        void speakers_on_(bool on);

    private:
        bool muted;
        bool stereo;
        bool speakers_on;
        uint8_t volume_1 = kMinAtten1;
        uint8_t volume_2 = kMinAtten2;

        uint8_t i2c_pot;                        // I2C address of digital pot
        int pin_mute;                           // Pin to turn mute on/off
        int pin_standby;                        // Pin to turn standby on/off
        int pin_phonic;                         // Pin to toggle phonics
        
};

#endif