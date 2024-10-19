#ifndef COMMAND_DETECTOR_H
#define COMMAND_DETECTOR_H

#include "Fsm.h"
#include "ASi.h"

class CommandDetector : public State
{
public:
	CommandDetector(Fsm* fsm, ASi* asi);
	static CommandDetector* Instance(Fsm* fsm, ASi* asi);

	void execute();

#ifdef X86_PLAT
	std::string getName() const
	{
		return "CommandDetector";
	}
#endif // X86_PLAT

private:
	ASi* m_asi;
};
#endif