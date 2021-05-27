#include <iostream>
#include <memory>
/*
职责链模式
使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这个对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
*/


class Handler {
protected:
    std::shared_ptr<Handler> _handler;
public:
    void setSuccessor(std::shared_ptr<Handler> handler) {
        _handler = handler;
    }

    virtual void request(int level) = 0;
};

class ConcreteHandler1 : public Handler{
public:
    void request(int level) override {
        if (level < 10) {
            std::cout << "ConcreteHandler1负责处理请求" << std::endl;
        } else {
            std::cout << "我帮你问问Handler2" << std::endl;
            _handler->request(level);
        }
    }
};

class ConcreteHandler2 : public Handler{
public:
    void request(int level) override {
        std::cout << "ConcreteHandler2" << std::endl;
    }
};

int main() 
{
    std::shared_ptr<Handler> handler1(new ConcreteHandler1());
    std::shared_ptr<Handler> handler2(new ConcreteHandler2());

    handler1->setSuccessor(handler2);

    handler1->request(8);
    handler1->request(20);
    return 0;
}