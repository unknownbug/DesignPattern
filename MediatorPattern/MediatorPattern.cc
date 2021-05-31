#include <iostream>
#include <memory>
#include <string>
#include <map>
/*
中介者模式
用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式的相互引用，从而使其耦合松散，而且可以独立的改变它们之间的交互。
*/

//中介者类
class Colleague;
class Mediator
{
public:
    virtual void send(const std::string &message, std::shared_ptr<Colleague> colleague) = 0;
};

//同事类
class Colleague
{
protected:
    std::weak_ptr<Mediator> _mediator;
    std::string _name;

public:
    void setName(const std::string &name)
    {
        _name = name;
    }

    std::string name() const
    {
        return _name;
    }

    void setMediator(std::shared_ptr<Mediator> mediator)
    {
        _mediator = mediator;
    }

public:
    virtual void recv(const std::string &message) = 0;
    virtual void send(const std::string &message) = 0;
};

class ConcreteMediator : public Mediator
{
private:
    std::map<std::string, std::weak_ptr<Colleague>> _colleague;

public:
    void addColleague(std::shared_ptr<Colleague> colleague)
    {
        if (!colleague)
            return;
        _colleague.emplace(std::make_pair(colleague->name(), colleague));
    }

    void send(const std::string &message, std::shared_ptr<Colleague> colleague) override
    {
        for (auto i : _colleague)
        {
            if (i.second.lock()->name() != colleague->name())
                i.second.lock()->recv(message);
        }
    }
};

class ConcreteColleague1 : public Colleague, public std::enable_shared_from_this<Colleague>
{
public:
    ConcreteColleague1()
    {
        setName(std::string("colleague1"));
    }
    void recv(const std::string &message) override
    {
        std::cout << "colleague1 recv msg: " << message << std::endl;
    }

    void send(const std::string &message) override
    {
        if (!_mediator.expired())
        {
            auto mediator = _mediator.lock();
            mediator->send(message, shared_from_this());
        }
    }
};

class ConcreteColleague2 : public Colleague, public std::enable_shared_from_this<Colleague>
{
public:
    ConcreteColleague2()
    {
        setName(std::string("colleague2"));
    }
    void recv(const std::string &message) override
    {
        std::cout << "colleague2 recv msg: " << message << std::endl;
    }

    void send(const std::string &message) override
    {
        if (!_mediator.expired())
        {
            auto mediator = _mediator.lock();
            mediator->send(message, shared_from_this());
        }
    }
};

int main()
{
    auto clg1 = std::make_shared<ConcreteColleague1>();
    auto clg2 = std::make_shared<ConcreteColleague2>();

    auto mediator = std::make_shared<ConcreteMediator>();
    mediator->addColleague(clg1);
    mediator->addColleague(clg2);

    clg1->setMediator(mediator);
    clg2->setMediator(mediator);

    clg1->send("请我吃饭吗？");
    clg2->send("没钱");
    return 0;
}