#ifndef SYNCING_BUS_H
#define SYNCING_BUS_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief Syncing
 *
 * While being in this state, the data line is HIGH, and must go to LOW after 64 TOSC cycles after entering the state. 
 * If so, a transition to BitStart is triggered.
 * If the fall comes before or after 64 TOSC, we transition to BitError. 
 *
 *
 * Previous state: IdleBus 
 * Next states: BitStart, BitError
 *
 */


class Syncing : public State
{
public:
    Syncing(Fsm* fsm, ASi* asi);

    static Syncing* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "Syncing";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;
    PrecisionTimer m_periodTimer;
    Switch m_sw;
};
#endif //SYNCING_BUS_H

