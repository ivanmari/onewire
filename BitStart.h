#ifndef BITSTART_H
#define BITSTART_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief BitStart
 *
 * Every bit starts at LOW, and differentiates between 1 or 0 depending on the time it rises HIGH
 * If after 32 TOSC cycles the data line goes to HIGH, a transition to BitHigh is triggered
 * If after 92 TOSC cycles the data line goes to HIGH, a transition to BitLow is triggered.
 * If the rising edge comes at a different time, we transition to BitError. 
 * If data line remains LOW for more than 64*TOSC, it may indicate the end of the frame, so a 
 * transition to InitializingBus is triggered.
 *
 * Previous states: Syncing, BitHigh, BitLow 
 * Next states: BitHigh, BitLow, BitError, InitializingBus
 *
 */


class BitStart : public State
{
public:
    BitStart(Fsm* fsm, ASi* asi);

    static BitStart* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "BitStart";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;
    PrecisionTimer m_periodTimerLow;
    PrecisionTimer m_periodTimerHigh;	
    Switch m_sw;
};
#endif //BITSTART_H

