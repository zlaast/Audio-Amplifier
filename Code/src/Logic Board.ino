#include <Thread.h>
#include "src/constants.h"
#include "src/speakers.h"
#include "src/knob.h"

Speakers speakers_A;
Speakers speakers_B;
Knob volume;
Knob select;
Thread save_state = Thread();

void state()
{
    EEPROM.put(kAddressAttenA1, speakers_A.get_attenuation_1_());
    EEPROM.put(kAddressAttenA2, speakers_A.get_attenuation_2_());
    EEPROM.put(kAddressAttenB1, speakers_B.get_attenuation_1_());
    EEPROM.put(kAddressAttenB2, speakers_B.get_attenuation_2_());
    EEPROM.put(kAddressPhonicA, !speakers_A.check_if_stereo_());
    EEPROM.put(kAddressPhonicB, !speakers_B.check_if_stereo_());
    EEPROM.put(kAddressMuteA,   !speakers_A.check_if_muted_());
    EEPROM.put(kAddressMuteB,   !speakers_B.check_if_muted_());
}

void setup()
{
    // START I2C COMMUNICATIONS
    Wire.begin();

    delay(5);

    // SETUP SPEAKERS
    speakers_A.begin_(kPotA, kAddressMuteA, kAddressPhonicA, kAddressAttenA1, kAddressAttenA2, kPinAmpMuteA, kPinAmpStandbyA, kPinPhonicA);
    speakers_B.begin_(kPotB, kAddressMuteB, kAddressPhonicB, kAddressAttenB1, kAddressAttenB2, kPinAmpMuteB, kPinAmpStandbyB, kPinPhonicB);

    // SETUP KNOBS
    volume.begin_(kPinVolumeUp, kPinVolumeDown, kPinMuteBtn, 1);
    select.begin_(kPinSpeakerNext, kPinSpeakerPrev, kPinPhonicBtn, 5);

    // SETUP THREADS
    save_state.onRun(state);
    save_state.setInterval(kSaveStateTime);
}

void loop() 
{  
    // STATIC VARIABLES
    static int sel = kSelect_All;                   // Speaker selection (ALL, A, B)
    static bool caterpillar_run_once = false;       // My friend suggested that I put a bug in my program, and she chose a caterpillar :)
    static bool mute_run_once = false;


    // RUN THREAD
    if (save_state.shouldRun())
        save_state.run();


    // SPEAKER SELECTION
    if (select.knob_() == kCW)
    {
        ++sel;
        if (sel > kSelect_B)
            sel = kSelect_All;
    }
    else if (select.knob_() == kCCW)
    {
        --sel;
        if (sel < kSelect_All)
            sel = kSelect_B;
    }

    
    // VOLUME CONTROL
    switch (sel)
    {
        case kSelect_All:
            speakers_A.change_volume_(volume.knob_());
            speakers_B.change_volume_(volume.knob_());
            break;

        case kSelect_A:
            speakers_A.change_volume_(volume.knob_());
            break;

        case kSelect_B:
            speakers_B.change_volume_(volume.knob_());
            break;
    }


    // MUTE CONTROL
    while (digitalRead(kPinMuteBtn))
    {
        if (!mute_run_once)
        {
            mute_run_once = true;
            switch (sel)
            {
                case kSelect_All:
                    speakers_A.mute_();
                    speakers_B.mute_();
                    break;
                
                case kSelect_A:
                    speakers_A.mute_();
                    break;

                case kSelect_B:
                    speakers_B.mute_();
                    break;
            }
        }
    }
    mute_run_once = false;


    // PHONIC SELECTION
    while (digitalRead(kPinPhonicBtn))
    {
        if (!caterpillar_run_once)
        {
            caterpillar_run_once = true;
            switch (sel)
            {
                case kSelect_All:
                    speakers_A.change_phonic_();
                    speakers_B.change_phonic_();
                    break;
                
                case kSelect_A:
                    speakers_A.change_phonic_();
                    break;

                case kSelect_B:
                    speakers_B.change_phonic_();
                    break;
            }
        }
    }
    caterpillar_run_once = false;
}
