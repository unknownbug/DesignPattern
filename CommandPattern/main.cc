#include <iostream>
#include <list>
#include <memory>
#include <algorithm>

//命令的执行者 receiver
class Barbecuer
{
public:
    void BakeMutton() {
        std::cout << "BakeMutton" << std::endl;
    }

    void BakeChickenWing() {
        std::cout << "BakeChickenWingCmd" << std::endl;
    }
};

//命令
class ICommand
{
public:
    ICommand(Barbecuer receiver)
        : _receiver(receiver)
    {
    }
    virtual ~ICommand() {}

    std::string name() const
    {
        return _name;
    }

    virtual void excute() = 0;

protected:
    std::string _name;
    Barbecuer _receiver;
};

class BakeMuttonCmd : public ICommand
{
public:
    BakeMuttonCmd(Barbecuer receiver) : ICommand(receiver)
    {
        _name = std::string("BakeMutton");
    }

    void excute() override
    {
        _receiver.BakeMutton();
    }
};

class BakeChickenWingCmd : public ICommand
{
public:
    BakeChickenWingCmd(Barbecuer receiver) : ICommand(receiver)
    {
        _name = std::string("BakeChickenWing");
    }

    void excute() override
    {
        _receiver.BakeChickenWing();
    }
};

//命令唤醒者  invoker
class Waiter
{
public:
    //下单
    void setOrder(const std::shared_ptr<ICommand> &cmd)
    {
        //如果菜卖完了 tips:换个菜吧
        //else
        _cmds.emplace_back(cmd);
    }

    //取消订单
    void cancelOrer(const std::shared_ptr<ICommand> &cmd)
    {
        auto result = std::find(_cmds.begin(), _cmds.end(), cmd);
        if (result != _cmds.end())
        {
            std::cout << "取消了" << cmd->name() << std::endl;
            _cmds.erase(result);
        }
    }

    void notify()
    {
        for (auto cmd : _cmds)
        {
            cmd->excute();
        }
    }

private:
    std::list<std::shared_ptr<ICommand>> _cmds;
};

int main()
{
    Barbecuer barbecuer;
    Waiter waiter;

    auto muttonCmd = std::make_shared<BakeMuttonCmd>(barbecuer);
    auto chickenwingCmd = std::make_shared<BakeChickenWingCmd>(barbecuer);

    waiter.setOrder(muttonCmd);
    waiter.setOrder(chickenwingCmd);

    waiter.notify();
    
    waiter.cancelOrer(muttonCmd);

    waiter.notify();

    return 0;
}