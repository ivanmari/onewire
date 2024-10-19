#ifndef BITLOW_H
#define BITLOW_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief BitLow
 *
 * At this state, data line should go to LOW after 32 TOSC cycles after entry, and transition to BitStart.
 * 
 * If the falling edge comes at a different time, we transition to BitError. 
 *
 *
 * Previous state: BitStart 
 * Next states: BitStart, BitError
 *
 */


class BitLow : public State
{
public:
    BitLow(Fsm* fsm, ASi* asi);

    static BitLow* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "BitLow";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;
    PrecisionTimer m_periodTimer;
    Switch m_sw;
};
#endif //BITLOW_H
