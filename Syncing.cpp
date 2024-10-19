#include "Syncing.h"
#include "BitStart.h"
#include "InitializingBus.h"

#include "io_defs.h"

const int TIMEOUT = 1000;
const int DELTA = TIMEOUT/10;

Syncing::Syncing(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimer(asi->getPlatform(), TIMEOUT), m_sw(DATA_LINE, LOW, asi)
{}

Syncing*
Syncing::Instance(Fsm* fsm, ASi* asi)
{
    static Syncing Syncing(fsm, asi);
    return &Syncing;
}

void
Syncing::execute()
{
    m_periodTimer.start();

    if(m_sw.isOn()) /*Active low*/
    {
        if(abs(m_periodTimer.remaining()) <= DELTA)
    		{
            m_asi->resetBitBuffer();
      			m_periodTimer.reset();
      			m_fsm->setState(BitStart::Instance(m_fsm, m_asi));
      			return;
    		}
    		else
    		{
            #ifdef X86_PLAT
      			std::cout << "Sync Error: Falling edge not within DELTA -- delta = "  << m_periodTimer.remaining() << std::endl;
      			#endif
      			m_periodTimer.reset();
      			m_fsm->setState(InitializingBus::Instance(m_fsm, m_asi));
      			return;
    		}
    }
	
    if(m_periodTimer.expired() && abs(m_periodTimer.remaining()) > DELTA)
    {
        #ifdef X86_PLAT
        std::cout << "Sync Error: Timeout without falling edge -- delta = " << m_periodTimer.remaining() << std::endl;
        #endif
        m_periodTimer.reset();
        m_fsm->setState(InitializingBus::Instance(m_fsm, m_asi));
        return;
    }
}

void
Syncing::reset()
{
}
