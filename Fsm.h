#ifndef FSM_H
#define FSM_H

#ifdef X86_PLAT

#include <iostream>
#include <string>

#endif // X86_PLAT

class Fsm;

class State
{
public:

    State(Fsm* fsm):m_fsm(fsm) {}
    virtual void execute() = 0;
    virtual void reset() = 0;
#ifdef X86_PLAT
    virtual std::string getName() const = 0;
#endif // X86_PLAT

protected:

    Fsm* m_fsm;
};

class Fsm
{
public:

    Fsm():m_state(0) {}

    void run()
    {
        m_state->execute();
    }

    void setState(State* state)
    {
#ifdef X86_PLAT
        if(m_state)
        {
            //std::cout << m_state->getName() << " --> " << state->getName() << std::endl;
        }
        else
        {
            std::cout << "New state, no previous: " << state->getName() << std::endl;
        }
#endif // X86_PLAT
        this->m_state = state;
    }

    State* getState() const
    {
        return m_state;
    }

private:
    State* m_state;
};



#endif //FSM_H
