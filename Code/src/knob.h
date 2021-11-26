////////////////////////////////////////////////////////////////////////
// NAME:               knob.h
//
// PURPOSE:            Controls the rotary encoders on the board
// 
// AUTHOR:              Z'Laast Allicock                     
////////////////////////////////////////////////////////////////////////

#ifndef KNOB_H
#define KNOB_H

#include <Arduino.h>
#include "constants.h"

class Knob
{
    public:
        void begin_(int pin_cw, int pin_ccw, int pin_switch, int ticks);
        int knob_();

    private:
        int pin_cw;
        int pin_ccw;
        int pin_switch;

        // Knob direction matrix
        int dir[3][3] = {{ 0,  1, -1},
                        {-1,  0,  1},
                        { 1, -1,  0}};

        int oldState = 0;       // Previous state of knob
        int ticks = 0;          // How many "ticks" the knob should rotate before triggering a change
        int cnt_cw = 0;         // Counts how many "ticks" the knob has turn cw            
        int cnt_ccw = 0;        // Counts how many "ticks" the knob has turn ccw
};

#endif