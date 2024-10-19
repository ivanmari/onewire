#include "io_defs.h"
#ifndef X86_PLAT
#include "ArduinoPlat.h"
ArduinoPlat plat;
#else
#include "x86/X86Platform.h"
X86Platform plat;
#endif // X86_PLAT 

#include "ASi.h"
#include "SimpleQueue.h"
#include "io_defs.h"
#include "InitializingBus.h"


SimpleQueue SimpleQueue(128);
ASi asi(&plat, &SimpleQueue);
Fsm fsm;


void setup() {
  Serial.begin(115200);
  fsm.setState(InitializingBus::Instance(&fsm, &asi));
  Serial.print("One Wire");
}

void loop() 
{
   fsm.run();
   if(asi.frameReady())
   {
		#ifdef X86_PLAT
		std::cout << "---" << std::endl;
		#else
		Serial.println("--");
		#endif

		unsigned char rx_byte;
		while(asi.popByte(rx_byte))
		{
			#ifdef X86_PLAT
			std::cout << std::hex << (0xFF & (int) rx_byte) << " ";
			#else
			Serial.print(rx_byte);
			Serial.print(" ");
			#endif

		}
   }
}
