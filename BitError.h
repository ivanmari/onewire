#ifndef BITERROR_H
#define BITERROR_H

#include "Fsm.h"
#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief BitError
 *
 * Entered here while receiving a bit.
 * As every bit starts low, and needs a rising edge to differentiate, the error
 * will occur when the data line rises with wrong timing.
 * 
 * A transition to low will generate a transition to InitializingBus, to start fresh.
 *
 * Previous state: BitStart 
 * Next states: InitializingBus
 *
 */


class BitError : public State
{
public:
    BitError(Fsm* fsm, ASi* asi);

    static BitError* Instance(Fsm* fsm, ASi* asi);

    void execute();
    void reset();
#ifdef X86_PLAT
    std::string getName() const
    {
        return "BitError";
    }
#endif // X86_PLAT
private:

    ASi* m_asi;
    PrecisionTimer m_periodTimer;
    Switch m_sw;
};
#endif //BITERROR_H

