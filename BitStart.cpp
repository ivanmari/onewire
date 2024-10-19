#include "BitStart.h"
#include "InitializingBus.h"
#include "BitError.h"
#include "BitLow.h"
#include "BitHigh.h"

#include "io_defs.h"

extern unsigned g_clock;

const int TIMEOUT_HIGH = 500;
const int TIMEOUT_LOW = 1000;
const int DELTA = TIMEOUT_HIGH/10;

BitStart::BitStart(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimerLow(asi->getPlatform(), TIMEOUT_LOW), m_periodTimerHigh(asi->getPlatform(), TIMEOUT_HIGH), m_sw(DATA_LINE, HIGH, asi)
{}

BitStart*
BitStart::Instance(Fsm* fsm, ASi* asi)
{
    static BitStart BitStart(fsm, asi);
    return &BitStart;
}

void
BitStart::execute()
{
    m_periodTimerLow.start();
    m_periodTimerHigh.start();

    if(m_sw.isOn())
    {
        if(abs(m_periodTimerLow.remaining()) <= DELTA)
    		{
    			m_periodTimerLow.reset();
    			m_periodTimerHigh.reset();
    			m_fsm->setState(BitLow::Instance(m_fsm, m_asi));
    			return;
    		}
    		else if (abs(m_periodTimerHigh.remaining()) <= DELTA)
    		{
    			m_periodTimerLow.reset();
    			m_periodTimerHigh.reset();
    			m_fsm->setState(BitHigh::Instance(m_fsm, m_asi));
    			return;
    		}
    		else
    		{
    			#ifdef X86_PLAT
    			std::cout << " Bit Start err timeout: remaining low = " << m_periodTimerLow.remaining() << " clock = " << g_clock << std::endl;
          #else
          Serial.println("BitStart err timeout");
    			#endif
    			m_periodTimerLow.reset();
    			m_periodTimerHigh.reset();
    			m_fsm->setState(BitError::Instance(m_fsm, m_asi));
    			return;			
    		}
    }

	//Last byte of frame?
    if(m_periodTimerLow.expired() && abs(m_periodTimerLow.remaining()) > DELTA)
    {
		#ifdef X86_PLAT
		//std::cout << " -- " << std::endl;
		#endif
		m_asi->frameEnd();
        m_periodTimerLow.reset();
        m_periodTimerHigh.reset();
        m_fsm->setState(InitializingBus::Instance(m_fsm, m_asi));
        return;
    }
}

void
BitStart::reset()
{
}
