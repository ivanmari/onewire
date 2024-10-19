#include "InitializedBus.h"
#include "Syncing.h"

#include "io_defs.h"

const int IDLE_TIMEOUT = (32 + 64) * TOSC;

InitializedBus::InitializedBus(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimerLow(asi->getPlatform(), IDLE_TIMEOUT), m_sw(DATA_LINE, HIGH, asi)
{}

InitializedBus*
InitializedBus::Instance(Fsm* fsm, ASi* asi)
{
    static InitializedBus IdleBus(fsm, asi);
    return &IdleBus;
}

void
InitializedBus::execute()
{

    if(m_sw.isOn())
    {
		m_fsm->setState(Syncing::Instance(m_fsm, m_asi));

        return;
    }
}

void
InitializedBus::reset()
{
}
