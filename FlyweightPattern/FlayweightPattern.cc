/*
享元模式
运用共享技术有效地支持大量细粒度的对象。

主要区分外部状态和内部状态
内部状态：在享元对象内部并且不会随环境改变而改变的共享部分。
外部状态：虽环境改变而改变 不可以共享的状态
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Flyweight
{
public:
    virtual void Operation(int extrinsicState) = 0;
};

class ConcreteFlyweight : public Flyweight
{
public:
    // extrinsicState意指外部状态
    void Operation(int extrinsicState) override
    {
        std::cout << "共享对象：extrinsicState " << extrinsicState << std::endl;
    }
};

class UnsharedFlyweight : public Flyweight
{
public:
    void Operation(int extrinsicState) override
    {
        std::cout << "不共享对象：extrinsicState " << extrinsicState << std::endl;
    }
};

// 简而言之 根据key类型决定使用何种实例化对象, 从而实现享元
class FlyweightFactory
{
private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> _flyweights;

public:
    // 获取享元对象
    std::shared_ptr<Flyweight> getFlyweight(const std::string key)
    {
        std::shared_ptr<Flyweight> result;
        try
        {
            result = _flyweights.at(key);
        }
        catch (const std::exception &e)
        {
            //现在只有ConcreteFlyweight的初始化
            auto fly = std::make_shared<ConcreteFlyweight>();
            _flyweights.emplace(key, fly);
            return fly;
        }
        return result;
    }
};

int main()
{
    FlyweightFactory factory;
    auto fly1 = factory.getFlyweight(std::string("fly1"));
    auto fly2 = factory.getFlyweight(std::string("fly2"));
    
    fly1->Operation(20);
    return 0;
}