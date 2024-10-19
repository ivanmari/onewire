#include "BitHigh.h"
#include "BitError.h"
#include "BitStart.h"

#include "io_defs.h"

const int TIMEOUT = 1000;
const int DELTA = TIMEOUT/7;
extern unsigned g_clock;

BitHigh::BitHigh(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimer(asi->getPlatform(), TIMEOUT), m_sw(DATA_LINE, LOW, asi)
{}

BitHigh*
BitHigh::Instance(Fsm* fsm, ASi* asi)
{
    static BitHigh BitHigh(fsm, asi);
    return &BitHigh;
}

void
BitHigh::execute()
{
    m_periodTimer.start();

    if(m_sw.isOn())
    {
        if(abs(m_periodTimer.remaining()) <= DELTA)
    		{
      			m_asi->addBit(true);
      			m_periodTimer.reset();
      			m_fsm->setState(BitStart::Instance(m_fsm, m_asi));
      			return;
    		}
    		else
    		{
    				#ifdef X86_PLAT
    				std::cout << " Bit High err timeout: remaining low = " << m_periodTimer.remaining() << " clock = " << g_clock << std::endl;
            #else
            Serial.println("BitHigh err timeout");
            #endif
        		m_periodTimer.reset();
        		m_fsm->setState(BitError::Instance(m_fsm, m_asi));
        		return;
    		}
    }

    if(m_periodTimer.expired() && abs(m_periodTimer.remaining()) > DELTA)
    {
		#ifdef X86_PLAT
		std::cout << " Bit High err timeout: remaining low = " << m_periodTimer.remaining() << " clock = " << g_clock << std::endl;
		#endif
		m_periodTimer.reset();
        m_fsm->setState(BitError::Instance(m_fsm, m_asi));
        return;
    }
}

void
BitHigh::reset()
{
}
