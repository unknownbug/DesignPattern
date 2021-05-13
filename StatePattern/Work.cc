#include "Work.h"
#include "State.h"

    Work::Work() 
     : _hours(9),
       _state(new ForenoonState())
    {}
    Work::~Work() {}

    void Work::setState(std::shared_ptr<IState> state) { _state = state; }
    std::shared_ptr<IState> Work::getState() const { return _state; }
    void Work::setHours(int hours) { _hours = hours; }
    int Work::getHours() const { return _hours; }

    void Work::writeProgram() {
        _state->writeProgram(*this);
    }

    void Work::finishWork() {
        std::cout << "finishWork....\n"  << std::endl;
    }