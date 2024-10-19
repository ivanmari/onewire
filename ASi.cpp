#include "ASi.h"
#include "Platform.h"
#include "io_defs.h"
#include <iomanip>
#include <iostream>
#include <bitset>


/*
    ASi: Actuator Sensor interface

*/

ASi::ASi(Platform* plat, SimpleQueue* SimpleQueue):m_platform(plat), m_SimpleQueue(SimpleQueue), m_rx_bit_buff(0), m_rx_bit_buff_count(0), m_frame_ready(false)
{

}

void
ASi::frameEnd()
{
	m_frame_ready = true;
}

bool
ASi::frameReady() const
{
	return m_frame_ready;
}

void
ASi::addBit (bool value)
{
	m_rx_bit_buff <<= 1;

	if (value)
	{
		m_rx_bit_buff |= 1;
	}
	std::bitset<8> bit_buf(m_rx_bit_buff);

	if(++m_rx_bit_buff_count == 8)
	{
		#ifdef X86_PLAT
		//std::cout << std::hex << (0xFF & (int)m_rx_bit_buff) << std::dec << std::endl;
		#endif
		m_SimpleQueue->enQueue(m_rx_bit_buff);
		resetBitBuffer();
	}
}

void
ASi::resetBitBuffer()
{
	m_rx_bit_buff = 0;
	m_rx_bit_buff_count = 0;
}

unsigned char
ASi::rxBufferSize() const
{
	return m_SimpleQueue->size();
}

void
ASi::resetByteBuffer()
{
	m_SimpleQueue->reset();
}

bool
ASi::popByte(unsigned char& value)
{
	m_frame_ready = false;
	return m_SimpleQueue->deQueue(value);
}

Platform*
ASi::getPlatform() const
{
    return m_platform;
}


