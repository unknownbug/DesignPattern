#include <iostream>

/*
适配器模式
将一个类的接口转换成客户希望的另外一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的类可以一起工作。

系统的数据和行为都正确，但接口不符时，我们应该考虑用适配器，目的是使控制范围之外的一个原有对象和某个接口相匹配。适配器模式
主要应用于希望复用一些现存的类，但是接口又与复用环境要求不一致的情况。

- 类适配器模式
- 对象适配器模式

针对于已存在的类设计适配器，给client使用

*/
//火箭队的比赛，教练coach叫暂停时给后卫Guards、中锋Center、前锋Forwards分配进攻和防守任务的代码

class Player {
public:
    virtual void defensive() = 0;
    virtual void offense() = 0;
};

class ChineseCenter {
public:
    void chinese_defensive() { std::cout << "Center, fuze defen.." << std::endl; }
    void chinese_offense() { std::cout << "Center, fuze fangshou.." << std::endl; }
};

class Guards : public Player {
public:
    void defensive() override { std::cout << "guards, score score.." << std::endl; }
    void offense() override { std::cout << "guards, defense defense.." << std::endl; }
};

class CenterTranslation : public Player {
private:
    ChineseCenter _center;
public:
    void defensive() override { _center.chinese_defensive(); }
    void offense() override { _center.chinese_offense(); }
};

class Forwards : public Player {
public:
    void defensive() override { std::cout << "Forwards, score score.." << std::endl; }
    void offense() override { std::cout << "Forwards, defense defense.." << std::endl; }
};

int main() {
    return 0;
}