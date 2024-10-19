#include "BitError.h"
#include "InitializingBus.h"

#include "io_defs.h"

const int TIMEOUT = 32 * TOSC;
const int DELTA = TIMEOUT/10;

BitError::BitError(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimer(asi->getPlatform(), TIMEOUT), m_sw(DATA_LINE, LOW, asi)
{}

BitError*
BitError::Instance(Fsm* fsm, ASi* asi)
{
    static BitError BitError(fsm, asi);
    return &BitError;
}

void
BitError::execute()
{
	  m_asi->resetBitBuffer();
    if(m_sw.isOn()) /*Active low*/
    {
		m_fsm->setState(InitializingBus::Instance(m_fsm, m_asi));
		return;
    }
}

void
BitError::reset()
{
}
