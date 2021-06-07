/*
访问者模式
*/

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>

//Person相对稳定，所以male，female实现单一些
class IAction;
class Person {
protected:
    std::string _name;

public:
    std::string name() const {
        return _name;
    }

    virtual void accept(std::shared_ptr<IAction> visitor) = 0;
};

//sucess failure FallInLove
//状态类，由于状态相对不稳定，所以抽象出来进行维护
class IAction {
public:
    virtual void maleReaction(std::shared_ptr<Person> male) = 0;

    virtual void femaleReaction(std::shared_ptr<Person> female) = 0;
};


class Male : public Person, public std::enable_shared_from_this<Male>{
public:
    Male() { _name = "male"; }
    void accept(std::shared_ptr<IAction> visitor) override
    {
        if (visitor)
        {
            visitor->maleReaction(shared_from_this());
        }
    }
};

class Female : public Person, public std::enable_shared_from_this<Female> {
public:
    Female() { _name = "female"; }
    void accept(std::shared_ptr<IAction> visitor) override
    {
        if (visitor)
        {
            visitor->femaleReaction(shared_from_this());
        }
    }
};



class Sucess : public IAction
{
public:
    void maleReaction(std::shared_ptr<Person>  male) override
    {
        std::cout << male->name() << "成功时，背后有一个女人" << std::endl;
    }

    void femaleReaction(std::shared_ptr<Person>  female) override
    {
        std::cout << female->name() << "成功时，背后有一个不怎么成功的男人" << std::endl;
    }
};


class Failure : public IAction
{
public:
    void maleReaction(std::shared_ptr<Person>  male) override
    {
        std::cout << male->name() << "失败时，闷头喝酒，谁也不用劝" << std::endl;
    }

    void femaleReaction(std::shared_ptr<Person> female) override
    {
        std::cout << female->name() << "失败时，眼泪汪汪，谁也劝不了" << std::endl;
    }
};

class FallInLove : public IAction
{
public:
    void maleReaction(std::shared_ptr<Person> male) override
    {
        std::cout << male->name() << "恋爱时，凡事不懂也要装懂" << std::endl;
    }

    void femaleReaction(std::shared_ptr<Person>  female) override
    {
        std::cout << female->name() << "恋爱时，遇事懂也装不同" << std::endl;
    }
};


//对象管理
class ObjectMgr{
private:
    std::list<std::shared_ptr<Person>> _persons;
public:
    void attach(std::shared_ptr<Person> person)
    {
        _persons.emplace_back(person);
    }

    void detach(std::shared_ptr<Person> person)
    {
        //可以加一些访问判断
        auto find = std::find(_persons.begin(), _persons.end(), person);
        _persons.erase(find);
    }

    void display(std::shared_ptr<IAction> visitor)
    {
        for (auto i : _persons)
        {
            i->accept(visitor);
        }
    }
};

int main()
{
    std::shared_ptr<IAction> visitor = std::make_shared<FallInLove>();
    auto male = std::make_shared<Male>();
    auto female = std::make_shared<Female>();

    ObjectMgr mgr;
    mgr.attach(male);
    mgr.attach(female);

    mgr.display(visitor);
    return 0;
}