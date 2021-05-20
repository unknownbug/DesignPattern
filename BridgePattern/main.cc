#include <memory>
#include <iostream>

//画笔

class Color {
public:
    virtual void drawColor() = 0;
};

class Red : public Color {
public:
    void drawColor() override {
        std::cout << "draw red\n";
    }
};

class Blue : public Color {
public:
    void drawColor() override {
        std::cout << "draw Blue\n";
    }
};

class Pen {
protected:
    std::weak_ptr<Color> _color;
public:
    void setColor(std::shared_ptr<Color> color) {
        _color = color;
    }

    virtual void drawColor(){
        if (!_color.expired()){
            auto color = _color.lock();
            color->drawColor();
        }
    }
};

int main()
{
    return 0;
}