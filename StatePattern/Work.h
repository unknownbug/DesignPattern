#ifndef __WORK_H__
#define __WORK_H__

#include <iostream>
#include <memory>

class IState;

class Work {
private:
    int _hours;
    std::shared_ptr<IState> _state;

public:
    Work();
    ~Work();

    void setState(std::shared_ptr<IState> state);
    
    std::shared_ptr<IState> getState() const;
    
    void setHours(int hours);
    
    int getHours() const;

    void writeProgram();

    void finishWork();
};

#endif //__WORK_H__