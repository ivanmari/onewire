#ifndef SimpleQueue_H
#define SimpleQueue_H

class SimpleQueue
{
public:
	SimpleQueue(unsigned int size);
	bool isFull() const;
	bool isEmpty() const;
	bool size() const;
	bool enQueue(unsigned char value);
	bool deQueue(unsigned char& value);
	void reset();

private:
	unsigned int m_front, m_rear, m_size;
	unsigned char m_capacity;
	unsigned char* m_array;
};
 
#endif //SimpleQueue_H