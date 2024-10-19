#include "SimpleQueue.h"
 
SimpleQueue::SimpleQueue(unsigned capacity)
{
	m_capacity = capacity;
	m_front = m_size = 0;
	m_rear = m_capacity - 1;  
	m_array = new unsigned char[(m_capacity * sizeof(unsigned char))];
}
 
bool
SimpleQueue::isFull() const
{
	return (m_size == m_capacity);
}
 
bool 
SimpleQueue::isEmpty() const
{
	return (m_size == 0);
}
 
bool
SimpleQueue::size() const
{
	return m_size;
}

bool 
SimpleQueue::enQueue(unsigned char item)
{
	bool ret = false;

	if (!isFull())
	{
		m_rear = (m_rear + 1) % m_capacity;
		m_array[m_rear] = item;
		m_size = m_size + 1;
		ret = true;
	}
	
	return ret;
}

bool
SimpleQueue::deQueue(unsigned char& item)
{
	bool ret = false;

	if (!isEmpty())
	{
		item = m_array[m_front];
		m_front = (m_front + 1) % m_capacity;
		m_size = m_size - 1;
		ret = true;
	}

	return ret;
}

void
SimpleQueue::reset()
{
	m_front = m_size = 0;
	m_rear = m_capacity - 1;
}
 