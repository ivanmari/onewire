#include "CommandDetector.h"

CommandDetector::CommandDetector(Fsm* fsm, ASi* asi) :State(fsm), m_asi(asi)
{

}

void
CommandDetector::execute()
{
	unsigned char rx_command = 0;

	if (m_asi->rxBufferSize())
	{
		if (m_asi->popByte(rx_command))
		{
			//Transition to particular command processor
			if (rx_command == 0x5A)
			{
				//m_fsm->setState(BattCapacity::Instance(m_fsm, m_asi));
			}
		}
	}
}