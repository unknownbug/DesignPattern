#include <memory>
#include <iostream>

class Good : public std::enable_shared_from_this<Good>
{
public:
    std::shared_ptr<Good> getPtr()
    {
        return shared_from_this();
    }
};

class Bad
{
public:
    std::shared_ptr<Bad> getPtr()
    {
        return std::shared_ptr<Bad>(this);
    }
};

int main()
{
    std::shared_ptr<Good> good1 = std::make_shared<Good>();
    std::shared_ptr<Good> good2 = good1->getPtr();
    // std::shared_ptr<Good> good2 = good1->shared_from_this();
    std::cout << good2.use_count() << std::endl;

    try
    {
        //虽然调用了shared_from_this, 但其没被shared_ptr占有，而是一个常规对象
        Good g3;
        auto g4 = g3.shared_from_this();
    }
    catch (std::bad_weak_ptr &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}