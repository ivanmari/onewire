#ifndef INITIALIZING_BUS_H
#define INITIALIZING_BUS_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief InitializingBus
 *
 * While being in this state, the data line is polled for a minimum of 992 TOSC cycles.
 * Once a LOW level is found, a transition to IdleBus is triggered
 *
 *
 * Previous state: Start, BitError, BusError 
 * Next states: IdleBus
 *
 */


class InitializingBus : public State
{
public:
    InitializingBus(Fsm* fsm, ASi* asi);

    static InitializingBus* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "InitializingBus";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;
    PrecisionTimer m_periodTimer;
    Switch m_sw;
};
#endif //INITIALIZING_BUS_H

