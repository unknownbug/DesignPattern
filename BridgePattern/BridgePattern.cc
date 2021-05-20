/*
桥接模式： 将抽象部分与它的实现部分分离，使他们都可以独立的变化 
合成聚合复用原则 优先使用对象的合成/聚合将有助于你保持每个类被封装，并被集中在单个任务上。这样类和类继承层次会保持较小规模，并且不太可能增长为不可控制的庞然大物。
聚合： 弱的拥有关系 鸟聚合成鸟群
合成： 强的拥有关系 翅膀合成鸟
学会用对象的职责来考虑问题

当发现需要多角度去分类实现对象，而只用继承会造成大量的类增加，就可以考虑使用桥接模式了。
*/

#include <iostream>
#include <memory>

class Implementor {
public:
    virtual void operation() = 0;
};

class ConcreteImplementorA : public Implementor{
public:
    void operation() override {
        std::cout << "run ConcreteImplementorA operation.\n";
    }
};

class ConcreteImplementorB : public Implementor{
public:
    void operation() override {
        std::cout << "run ConcreteImplementorB operation.\n";
    }
};

class Abstraction {
protected:
    std::weak_ptr<Implementor> _impl;
public:
    virtual void SetImplementor(std::shared_ptr<Implementor> impl) {
        _impl = impl;
    };
    virtual void operation() = 0;
};

class RefinedAbstraction : public Abstraction{
public:
    virtual void operation() override {
        if (!_impl.expired())
        {
            auto impl = _impl.lock();
            impl->operation();
        }
    }
};

int main()
{
    auto a = std::make_shared<ConcreteImplementorA>();
    auto b = std::make_shared<ConcreteImplementorB>();

    RefinedAbstraction r;
    r.SetImplementor(a);
    r.operation();

    r.SetImplementor(b);
    r.operation();
    return 0;
}