#include <iostream>
#include <memory>
/*
备忘录模式
在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。
*/

/*
游戏场景 一游戏角色(game role)有生命力（vitality）、攻击力（Attack）、防御力(Defense)等数据，在打boss前和后是不一样的，我们允许玩家如果感觉与Boss决斗的效果不理想，可以让游戏恢复到决斗前。
*/

//游戏角色数据备忘录
class RoleMemento {
public:
    int _vatality;
    int _attack;
    int _defence;

public:
    RoleMemento(int vatality, int attack, int defence) 
    : _vatality(vatality),
    _attack(attack),
    _defence(defence)
    {};
};

//备忘录管理
class MementoCaretaker {
private:
    std::shared_ptr<RoleMemento> _memento;
public:
    void saveMemento(std::shared_ptr<RoleMemento> memento) {
        _memento = memento;
    }

    std::shared_ptr<RoleMemento> getMemento() {
        return _memento;
    }
};

//角色数据
class GameRole {
private:
    int _vatality; //生命力
    int _attack; //攻击力
    int _defence; //防御力

public:
    GameRole() = default;

    ~GameRole() = default;

    //游戏角色初始状态
    void getInitState() {
        _vatality = 100;
        _attack = 20;
        _defence = 30;
    }
    //数据展示
    void showState() {
        std::cout << "vatality: " << _vatality << std::endl;
        std::cout << "attack: " << _attack << std::endl;
        std::cout << "defence: " << _defence << std::endl;
    }

    void fight() {
        _vatality -= 100;
    }

    std::shared_ptr<RoleMemento> archive() {
        return std::make_shared<RoleMemento>(_vatality, _attack, _defence);
    }

    void restory(std::shared_ptr<RoleMemento> memento) {
        _vatality = memento->_vatality;
        _attack = memento->_attack;
        _defence = memento->_defence;
    }
};



int main() {
    GameRole role;
    role.getInitState();
    role.showState();

    //备忘录
    MementoCaretaker caretaker;
    caretaker.saveMemento(role.archive());

    role.fight();
    role.showState();

    role.restory(caretaker.getMemento());
    role.showState();
    return 0;
}