#ifndef BITHIGH_H
#define BITHIGH_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief BitHigh
 *
 * At this state, data line should go to LOW after 64 TOSC cycles after entry, and then transition to BitStart.
 * 
 * If the falling edge comes at a different time, we transition to BitError. 
 *
 *
 * Previous state: BitStart 
 * Next states: BitStart, BitError
 *
 */


class BitHigh : public State
{
public:
    BitHigh(Fsm* fsm, ASi* asi);

    static BitHigh* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "BitHigh";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;
    PrecisionTimer m_periodTimer;
    Switch m_sw;
};
#endif //BITHIGH_H
