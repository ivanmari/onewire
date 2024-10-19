#ifndef ASI_H
#define ASI_H

#include "Platform.h"
#include "SimpleQueue.h"

const unsigned char RX_BYTE_BUFFER_SZ = 16;

class ASi
{
public:

    ASi(Platform*, SimpleQueue*);

    virtual Platform* getPlatform() const;
	
	virtual void addBit(bool value);
	virtual void resetBitBuffer();
	virtual void frameEnd();
	virtual bool frameReady() const;

	virtual bool popByte(unsigned char&);
	virtual unsigned char rxBufferSize() const;
	virtual void resetByteBuffer();

private:

    Platform* m_platform;
	SimpleQueue* m_SimpleQueue;
	char m_rx_bit_buff;
	char m_rx_bit_buff_count;
	bool m_frame_ready;
};

#endif //ASI_H
