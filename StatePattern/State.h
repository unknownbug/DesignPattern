#ifndef __STATE_H__
#define __STATE_H__

#include "Work.h"

class IState {
public:
    IState() = default;
    virtual ~IState() = default;

    virtual void writeProgram(Work & work) = 0;
};

class AfternoonState : public IState {
public:
    virtual void writeProgram(Work & work) override {
        if (work.getHours() < 18) {
            std::cout << "afternoon\n";
        } else {
            work.finishWork();
        }
    }
};


class NoonState : public IState {
public:
    virtual void writeProgram(Work & work) override {
        if (work.getHours() < 13) {
            std::cout << "NoonState\n";
        } else {
            work.setState(std::make_shared<AfternoonState>());
            work.writeProgram();
        }
    }
};


class ForenoonState : public IState {
public:
    virtual void writeProgram(Work & work) override {
        if (work.getHours() < 12) {
            std::cout << "ForenoonState\n";
        } else {
            work.setState(std::make_shared<NoonState>());
            work.writeProgram();
        }
    }
};



#endif //__STATE_H__