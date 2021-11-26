#include "knob.h"

void Knob::begin_(int pin_cw, int pin_ccw, int pin_switch, int ticks)
{
    this->pin_cw = pin_cw;
    this->pin_ccw = pin_ccw;
    this->pin_switch = pin_switch;
    this->ticks = ticks;

    pinMode(pin_cw, INPUT);
    pinMode(pin_ccw, INPUT);
    pinMode(pin_switch, INPUT_PULLUP);

    oldState = digitalRead(pin_cw) + digitalRead(pin_ccw);
}

int Knob::knob_()
{
    delay(3);
    int newState = digitalRead(pin_cw) + digitalRead(pin_ccw);

    // Clockwise
    if (dir[oldState][newState] == 1)
    {
        cnt_cw++;
        cnt_ccw = 0;
        if (cnt_cw > ticks)
        {
            cnt_cw = 0;
            return kCW;
        }
    }
    // Counter-Clockwise
    else if (dir[oldState][newState] == -1)
    {
        cnt_cw = 0;
        cnt_ccw++;
        if (cnt_ccw > ticks)
        {
            cnt_ccw = 0;
            return kCCW;
        }
    }

    oldState = newState;
    return 0;
}