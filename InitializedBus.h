#ifndef IDLE_BUS_H
#define IDLE_BUS_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief IdleBus
 *
 * After entering into this state, the data line has been LOW for a minimum of 992 TOSC cycles.
 * So we look now for a High level, and when it is found, a transition to Syncing is triggered
 *
 *
 * Previous state: InitializingBus 
 * Next states: Syncing
 *
 */


class InitializedBus : public State
{
public:
    InitializedBus(Fsm* fsm, ASi* asi);

    static InitializedBus* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "InitializedBus";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;

	PrecisionTimer m_periodTimerLow;
    Switch m_sw;
};
#endif //IDLE_BUS_H

