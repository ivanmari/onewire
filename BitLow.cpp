#include "BitLow.h"
#include "BitStart.h"
#include "BitError.h"

#include "io_defs.h"

const int TIMEOUT = 500;
const int DELTA = 220;

#ifdef X86_PLAT
extern unsigned g_clock;
#endif

BitLow::BitLow(Fsm* fsm, ASi* asi):State(fsm), m_asi(asi), m_periodTimer(asi->getPlatform(), TIMEOUT), m_sw(DATA_LINE, LOW, asi)
{}

BitLow*
BitLow::Instance(Fsm* fsm, ASi* asi)
{
    static BitLow BitLow(fsm, asi);
    return &BitLow;
}

void
BitLow::execute()
{
    m_periodTimer.start();

    if(m_sw.isOn()) /*Active low*/
    {
      if(abs(m_periodTimer.remaining()) <= DELTA)
  		{
    			m_asi->addBit(false);
    			m_periodTimer.reset();
    			m_fsm->setState(BitStart::Instance(m_fsm, m_asi));
    			return;
  		}
  		else
  		{
    			#ifdef X86_PLAT
    			std::cout << " Bit Low err timeout: remaining low = " << m_periodTimer.remaining() << " clock = " << g_clock << std::endl;
    			#else
          Serial.println("BitLow err timeout");
          #endif
    			m_periodTimer.reset();
    			m_fsm->setState(BitError::Instance(m_fsm, m_asi));
    			return;
  		}
    }

    if(m_periodTimer.expired() && abs(m_periodTimer.remaining()) > DELTA)
    {
		    #ifdef X86_PLAT
		    std::cout << " Bit Low err timeout: remaining low = " << m_periodTimer.remaining() << " clock = " << g_clock << std::endl;
        #else
        Serial.println("BitStart err timeout");
        #endif
		    m_periodTimer.reset();
        m_fsm->setState(BitError::Instance(m_fsm, m_asi));
        return;
    }
}

void
BitLow::reset()
{
}
