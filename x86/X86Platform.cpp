#include "X86Platform.h"
#ifdef X86_PLAT

#include <thread>
#include <chrono>
#include <iostream>
#include <map>


using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::steady_clock;

extern std::map<unsigned, bool> g_data_samples;

bool g_last_output = false;
unsigned g_clock = 0;


X86Platform::X86Platform()
{
    //ctor
}

X86Platform::~X86Platform()
{
    //dtor
}

long
X86Platform::map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned 
X86Platform::getSystemUpTimeMinutes()
{
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count()/60000;
}

unsigned long
X86Platform::getSystemUpTimeMillis()
{
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

unsigned long
X86Platform::getSystemUpTimeMicros()
{
    return g_clock;
}

void
X86Platform::setPinMode(int pin, PinMode mode)
{
    switch(mode)
    {
    case PIN_INPUT:
        std::cout << "Pin " << pin << " set as INPUT" << std::endl;
        break;

    case PIN_OUTPUT:
        std::cout << "Pin " << pin << " set as OUTPUT" << std::endl;
        break;
    }
}

void
X86Platform::setPin(int pin, bool level)
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(150));
    if (level)
    {
        std::cout << "pin #" << pin << "-> HIGH" << std::endl;
    }
    else
    {
        std::cout << "pin #" << pin << "-> LOW" << std::endl;
    }
}

bool
X86Platform::getPin(int pin)
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(150));
    bool out = false;
	static std::map<unsigned, bool>::iterator g_data_samples_it = g_data_samples.begin();
    if(15 == pin)
    {
		if (g_data_samples_it != g_data_samples.end())
		{
			if (g_clock++ >= g_data_samples_it->first)
			{
				//std::cout << "clock: " << g_clock << " next_change: " << g_data_samples_it->first << std::endl;
				out = g_data_samples_it->second;
				g_last_output = out;
				g_data_samples_it++;
			}
			else
			{
				out = g_last_output;
			}

			
		}
		
    }
    //std::cout << "Reading pin #" << pin << " as " << out << std::endl;
    return out;
}

int
X86Platform::readAnalogPin(int pin)
{
    return 0;
}

void
X86Platform::delay(unsigned millis)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}
#endif // X86_PLAT
