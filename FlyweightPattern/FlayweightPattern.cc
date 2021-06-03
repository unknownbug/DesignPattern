/*
享元模式
运用共享技术有效地支持大量细粒度的对象。

主要区分外部状态和内部状态
内部状态：在享元对象内部并且不会随环境改变而改变的共享部分。
外部状态：虽环境改变而改变 不可以共享的状态

何时使用：
- 系统中有大量对象
- 这些对象消耗大量内存
- 这些对象的状态大部分可以外部化
- 这些对象可以按照内蕴状态分为很多组，当把外蕴对象从对象中剔除出来时，每一组对象都可以用一个对象来代替
- 系统不依赖于这些对象身份，这些对象是不可分辨的

注意事项：
- 注意划分外部状态和内部状态，否则会引起线程安全问题
- 这些类必须有一个工厂对象加以控制
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