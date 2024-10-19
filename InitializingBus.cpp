#include "InitializingBus.h"
#include "InitializedBus.h"

#include "io_defs.h"


const int TIMEOUT = 992 * TOSC;

InitializingBus::InitializingBus(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimer(asi->getPlatform(), TIMEOUT), m_sw(DATA_LINE, HIGH, asi)
{}

InitializingBus*
InitializingBus::Instance(Fsm* fsm, ASi* asi)
{
    static InitializingBus InitializingBus(fsm, asi);
    return &InitializingBus;
}

void
InitializingBus::execute()
{
    m_periodTimer.start();

    if(m_sw.isOn())
    {
        m_periodTimer.reset();
        return;
    }

    if(m_periodTimer.expired())
    {
        m_fsm->setState(InitializedBus::Instance(m_fsm, m_asi));

        m_periodTimer.reset();
        return;
    }
}

void
InitializingBus::reset()
{
}
