# 从C++编程入手设计模式——装饰器模式

​	我们今天玩装饰器模式。在写代码的时候，我们经常会遇到这样的需求：在不修改原有类的情况下，给它增加一些额外的功能。比如你已经有一个文本打印类，但现在你想让它打印出来的内容自动加上引号、变成大写，甚至加上前缀或后缀。你可能第一反应是继承，但如果装饰的方式有很多种，继承的子类就会变得非常多，既麻烦又不灵活。装饰器设计模式就是为了解决这个问题的。一句话：一个运行时继承的方案

------

## 所以，啥是装饰器模式

装饰器模式的本质，是**通过“包裹”一个已有对象，动态地给它添加一些行为**。这就像给一个人加上一件外套一样，不改变他本身，但看起来更漂亮或功能更强。用专业一点的话说，装饰器模式是一种结构型模式，它允许我们在不改变原有对象结构的基础上，动态地添加职责。

------

## 样板

```c++
#include <iostream>
#include <memory>

class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() = default;
};

class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "ConcreteComponent operation\n";
    }
};

class Decorator : public Component {
protected:
    std::shared_ptr<Component> component;
public:
    Decorator(std::shared_ptr<Component> comp) : component(std::move(comp)) {}
};

class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(std::shared_ptr<Component> comp) : Decorator(std::move(comp)) {}

    void operation() const override {
        std::cout << "ConcreteDecoratorA adds behavior\n";
        component->operation();
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(std::shared_ptr<Component> comp) : Decorator(std::move(comp)) {}

    void operation() const override {
        std::cout << "ConcreteDecoratorB adds behavior\n";
        component->operation();
    }
};

int main() {
    auto simple = std::make_shared<ConcreteComponent>();
    auto decorator1 = std::make_shared<ConcreteDecoratorA>(simple);
    auto decorator2 = std::make_shared<ConcreteDecoratorB>(decorator1);

    decorator2->operation();
    return 0;
}
```

​	如上图所示，这就是一个最简单的装饰器的样板代码。我们留心到，我们在构造函数中，动态的接受基类的指针，现在我们就能扩展原先的功能，实际上上面的decorator2是ConcreteComponent，ConcreteDecoratorA和ConcreteDecoratorB的组合，不信的话试试看上面的代码？

## 装饰器与继承的对比

装饰器模式看起来跟继承很像，因为它也复用了接口，但它比继承灵活得多。继承是**编译期的静态行为**，你一旦决定了一个类的继承关系，就很难在运行时修改。而装饰器是**运行时的动态组合**，你可以按需添加任意多层功能，不用管组合数量，也不用写一堆子类。



------

## 应用场景总结

装饰器模式非常适合用于：

- 不希望修改已有类的前提下添加功能；
- 想要用组合代替继承，提升灵活性；
- 想对某个对象添加一系列功能（如加边框、加阴影、加滚动条）；
- 希望保持开放封闭原则（对扩展开放，对修改封闭）；

在图形界面库（如 Qt、Java Swing）、流操作（如 C++ 的 `iostream`）、Java IO、甚至日志系统中，都可以看到装饰器模式的身影。

## 练习题

### 基础装饰器——文本输出装饰器

**题目描述**：
 设计一个基础的文本输出接口 `TextPrinter`，默认实现是 `PlainTextPrinter`，直接打印字符串。现在你希望加入一些装饰器：

- `QuoteDecorator`：为输出文本添加前后引号；
- `StarDecorator`：在文本两边加上星号 `***`；
- `UpperCaseDecorator`：将所有输出内容变为大写。

**要求**：

- 使用抽象基类 + 装饰器类实现；
- 所有装饰器都可以组合嵌套使用。

**提示结构**：

```c++
cpp复制编辑struct TextPrinter {
    virtual void print(const std::string& text) = 0;
    virtual ~TextPrinter() = default;
};

class PlainTextPrinter : public TextPrinter {
    void print(const std::string& text) override;
};

class TextDecorator : public TextPrinter {
protected:
    std::shared_ptr<TextPrinter> wrappee;
public:
    TextDecorator(std::shared_ptr<TextPrinter> printer);
};

class QuoteDecorator : public TextDecorator { ... };
class StarDecorator : public TextDecorator { ... };
class UpperCaseDecorator : public TextDecorator { ... };
```

> 实现的代码：[modern-cpp-patterns-playground/Decorate/TextPrinter at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/Decorate/TextPrinter)

