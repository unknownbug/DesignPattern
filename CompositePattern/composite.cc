#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>

class Component {
public:
    Component(const std::string & name)
    : _name(name)
    {}
    virtual ~Component() = default;

    virtual void add(std::shared_ptr<Component> c) = 0;
    virtual void remove(std::shared_ptr<Component> c) = 0;
    virtual void display(int depth) = 0;

protected:
    std::string _name;
};

class Leaf : public Component {
public:
    Leaf(const std::string & name) : Component(name){}
    ~Leaf() = default;
    void add(std::shared_ptr<Component> c) override 
    {
        std::cout << "leaf can not add node" << std::endl;
    }

    void remove(std::shared_ptr<Component> c) override
    {
        std::cout << "leaf can not remove node" << std::endl;
    }
    
    void display(int depth) override
    {
        std::string line(depth, '-');
        std::cout << line << _name << std::endl;
    }
};

class Composite :  public Component {
public:
    Composite(const std::string & name) : Component(name){}
    ~Composite() = default;
    void add(std::shared_ptr<Component> c) override 
    {
        _children.emplace_back(c);
    }

    void remove(std::shared_ptr<Component> c) override
    {
        _children.erase(std::find(_children.begin(), _children.end(), c));
    }
    
    void display(int depth) override
    {
        std::string line(depth, '-');
        std::cout << line << _name << std::endl;
        for (auto node : _children)
        {
            node->display(depth + 2);
        }
    }

private:
    std::list<std::shared_ptr<Component>> _children; //存储子节点
};
using Node = std::shared_ptr<Component>;
int main()
{
    Node root(new Composite("root"));

    Node root_leafa(new Leaf("leafa"));
    Node root_leafb(new Leaf("leafa"));

    Node node_a(new Composite("node_a"));
    Node node_b(new Composite("node_b"));

    Node a_leafa(new Leaf("a_leafa"));
    Node b_leafb(new Leaf("b_leafb"));

    node_a->add(a_leafa);
    node_b->add(b_leafb);

    root->add(node_a);
    root->add(node_b);
    root->add(root_leafa);
    root->add(root_leafb);

    root->display(1);

    return 0;
}