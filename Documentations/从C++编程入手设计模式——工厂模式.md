# 从C++编程入手设计模式

## 工厂模式

​	我们马上就要迎来我们的第二个创建型设计模式：工厂方法模式（Factory Method Pattern）。换而言之，我们希望使用一个这样的接口，使用其他手段而不是直接创建的方式（说的有点奇怪，大致意思是——不是直接new，而是使用父子对象机制，给定一个判断条件让我们的工厂类选择创建具体的子类）

​	这是因为在软件开发中，直接在代码中使用 `new` 关键字创建对象会导致代码与具体类紧密耦合，降低了系统的灵活性和可扩展性。工厂方法模式通过引入工厂接口和具体工厂类，**将对象的创建过程封装起来，使得客户端代码与具体产品类解耦**，从而提高了系统的可维护性和可扩展性。

​	一个完整的工厂模式中存在四个基本的类。

1. **抽象产品（Product）**：定义产品的接口，是所有具体产品类的父类。
2. **具体产品（ConcreteProduct）**：实现了抽象产品接口的具体类，表示被创建的对象。
3. **抽象工厂（Creator）**：声明工厂方法 `factoryMethod()`，返回抽象产品类型的对象。
4. **具体工厂（ConcreteCreator）**：实现抽象工厂中的工厂方法，返回具体产品的实例。

​	很显然，抽象的产品和类是一个接口，我们所有的产品都需要满足这个接口，或者说，是属于这个产品类的对象，需要被对应的具体的工厂所创建。当然，对于小项目，笔者一般喜欢合并抽象工厂和具体工厂为工厂，这样的话直接对这工厂类发起对象创建请求即可。

### C++实现的一些要点

- **使用抽象类和虚函数**：通过定义抽象产品类和抽象工厂类，利用虚函数实现多态性，使得客户端代码可以通过基类指针或引用操作具体产品对象。
- **使用智能指针管理对象生命周期**：为了避免内存泄漏，建议使用 `std::unique_ptr` 或 `std::shared_ptr` 管理动态分配的对象。
- **将对象创建逻辑封装在工厂类中**：将具体产品类的实例化过程封装在具体工厂类中，客户端代码只需调用工厂方法获取产品对象，而无需关心具体的创建细节。

​	下面是一个非常经典的例子，但是不够好，体现不出来为什么工厂模式存在，但是绘景代码是如下的：

```cpp
#include <iostream>
#include <memory>

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a Square" << std::endl;
    }
};

class ShapeFactory {
public:
    virtual std::unique_ptr<Shape> createShape() = 0;
    virtual ~ShapeFactory() = default;
};

class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Circle>();
    }
};

class SquareFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Square>();
    }
};

int main() {
    std::unique_ptr<ShapeFactory> circleFactory = std::make_unique<CircleFactory>();
    std::unique_ptr<Shape> circle = circleFactory->createShape(); // 是一个shape
    circle->draw(); // 但是是circle，所以调用的就是circle的方法
    std::unique_ptr<ShapeFactory> squareFactory = std::make_unique<SquareFactory>();
    std::unique_ptr<Shape> square = squareFactory->createShape();
    square->draw();
    return 0;
}
```

### 一些你需要注意的事情

- **避免过度使用**：在对象创建过程简单且不会发生变化的情况下，使用工厂方法模式可能会增加系统的复杂性，导致代码冗余。（换而言之，不要到处用这个东西，除非真需要了（大量相似对象的创建））
- **合理组织类结构**：随着产品种类和工厂类的增加，类的数量也会增加，需要合理组织类结构，避免类爆炸。
- **结合其他设计模式使用**：工厂方法模式可以与其他设计模式（如单例模式、抽象工厂模式）结合使用，以满足更复杂的系统需求。

## 例子：快餐连锁店的汉堡制作系统

**背景：**

您正在为一家快餐连锁店开发一个汉堡制作系统。不同的快餐品牌（如麦当劳和汉堡王）有各自的汉堡制作方式，包括使用的面包类型、配料和包装方式。

**任务：**

1. 定义一个抽象基类 `Burger`，包含纯虚函数 `grill()`、`prepare()` 和 `wrap()`，以及成员变量如 `name`、`bunType` 和 `condiments`。
2. 实现具体的汉堡类，如 `McDonaldsCheeseBurger` 和 `BurgerKingCheeseBurger`，分别继承自 `Burger`，并实现上述方法，输出相应的制作步骤。
3. 创建一个抽象工厂类 `BurgerJoint`，包含纯虚函数 `createBurger(const std::string& type)`，用于创建不同类型的汉堡。
4. 实现具体的工厂类，如 `McDonalds` 和 `BurgerKing`，继承自 `BurgerJoint`，根据传入的类型创建相应的汉堡实例。
5. 在主函数中，模拟客户在不同快餐店点餐的过程，使用工厂类创建汉堡对象，并调用其制作方法。

**这些要求你需要做到**

- 使用 `std::unique_ptr` 管理对象生命周期。智能指针是一个好东西，多用用！
- 保持代码的可扩展性，方便将来添加新的快餐品牌或汉堡类型。

> 实现：[modern-cpp-patterns-playground/FactoryBaseMethod/BurgerCreator at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/FactoryBaseMethod/BurgerCreator)

```c++
class AbstractBurger {
public:
	virtual void grill() = 0;
	virtual void prepare() = 0;
	virtual void wrap() = 0;
	virtual ~AbstractBurger() = default; /* this is required to the parent calss */
};
```

首先，咱们起手定义了一个抽象基类 `AbstractBurger`，其中包含了 `grill()`、`prepare()` 和 `wrap()` 三个纯虚函数，代表了制作汉堡的三个主要步骤。然后，我为麦当劳和汉堡王分别实现了具体的汉堡类，如 `McBurger`、`McCheeseBurger`、`BurgerKingBurger` 和 `BurgerKingCheeseBurger`，每个类都根据品牌和汉堡类型的不同，实现了各自的制作流程。

```c++
class BurgerProvider {
public:
	virtual std::unique_ptr<AbstractBurger> create_specifiedBurger(const std::string& specified_type) = 0;
	virtual ~BurgerProvider() = default;
};
```

为了创建这些汉堡对象，我定义了一个抽象工厂类 `BurgerProvider`，并为每个品牌实现了具体的工厂类 `McBurgerProvider` 和 `BurgerKingProvider`。这些工厂类根据传入的参数（如 "normal" 或 "cheese"）来决定创建哪种具体的汉堡对象。通过这种方式，客户端代码可以通过工厂类来创建所需的汉堡，而无需了解具体的实现细节，从而实现了对象创建的解耦。

## 习题

**背景：**

您正在开发一个通知发送系统，支持多种通知方式，如电子邮件（Email）、短信（SMS）和推送通知（Push Notification）。每种通知方式有其特定的发送逻辑和所需的参数。

**任务：**

1. 定义一个抽象基类 `Notification`，包含纯虚函数 `send(const std::string& message)`。
2. 实现具体的通知类，如 `EmailNotification`、`SMSNotification` 和 `PushNotification`，分别继承自 `Notification`，并实现发送逻辑。
3. 创建一个工厂类 `NotificationFactory`，包含静态成员函数 `createNotification(const std::string& type)`，根据传入的类型创建相应的通知对象。
4. 在主函数中，模拟发送不同类型通知的过程，使用工厂类创建通知对象，并调用其发送方法。

**要求：**

- 使用 `std::unique_ptr` 管理对象生命周期。
- 考虑每种通知方式所需的特定参数，并在创建对象时传入。
- 保持代码的可扩展性，方便将来添加新的通知方式。

> 笔者也有自己的实现：[modern-cpp-patterns-playground/FactoryBaseMethod/NotificationSystem at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/FactoryBaseMethod/NotificationSystem)