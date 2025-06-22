# 从C++编程入手设计模式——观察者模式

​	观察者模式简直就是字如其名，观察观察，观察到了告诉别人。观察手的作用如此，观察者模式的工作机制也是如此。这个模式的核心思路是：**一个对象的状态发生变化时，自动通知依赖它的其他对象，让它们自行更新**。

## 主要的组成部分

一是**被观察者**，也叫主题（Subject），它负责记录观察者并在自身状态发生变化时通知它们；换而言之，Subject作为信息的生成端，生成信息。

二是**观察者**（Observer），它主动注册到被观察者中，等待被通知，一旦收到消息就立即采取行动。这里生成端会使用远程的方式通知我们的被观察者投送信息。

​	你可以把观察者模式想象成“订阅报纸”。报社就是主题，它维护一个订阅者名单（观察者列表）。每当有新一期的报纸（数据更新）出版时，它就向所有订阅者投递（通知）。每位订阅者收到报纸后根据自己的需要决定怎么处理，是直接阅读、剪报存档还是转发朋友。这种**发布-订阅机制**就是观察者模式的最基本形式。

------

## **在 C++ 中怎么写？**

观察者模式的代码实现非常自然。我们会先定义一个抽象的观察者接口（通常叫 `Observer` 或者 `Sender`），让不同的具体观察者实现它；再定义一个主题类（通常叫 `Subject` 或 `Notifier`），它包含一个观察者列表，并负责注册、移除和通知观察者。每当主题内部数据变化（比如温度、湿度更新），它就会遍历观察者列表，挨个调用它们的“更新方法”。观察者模式的重点不在于通知的“数据内容”本身，而在于**自动通知的机制**。

------

## **选择观察者模式？**

在简单的程序中，我们可能会直接调用某些对象来执行逻辑。但如果程序复杂起来，比如某个数据更新后要引发十几种操作，硬编码这些调用就会让系统结构僵硬，维护困难。

观察者模式将“变化的主体”和“依赖的反应者”解耦。被观察者不用关心观察者是谁，它只管发出通知。观察者自己决定是否接收通知、如何响应。这让系统的**扩展性和灵活性大大提高**。

比如天气系统中新加一个“语音播报设备”，只要实现观察者接口并注册进去，其他部分代码几乎无需改动。

------

**观察者模式的几个关键词**

1. **低耦合**：主题和观察者之间不互相依赖，只通过接口通信。
2. **自动同步**：当主题数据变化时，所有观察者自动得到通知。
3. **一对多**：一个主题可以对应多个观察者。
4. **注册/注销机制**：观察者可以自由加入或离开通知流程。

------

## Example

​	可以直接看一个代码框架来解决问题

```c++
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// 观察者接口
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// 具体观察者
class ConcreteObserver : public Observer {
private:
    std::string name;
public:
    explicit ConcreteObserver(std::string n) : name(std::move(n)) {}
    void update(const std::string& message) override {
        std::cout << "Observer [" << name << "] received: " << message << '\n';
    }
};

// 主题接口
class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify(const std::string& message) = 0;
    virtual ~Subject() = default;
};

// 具体主题
class ConcreteSubject : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(std::move(observer));
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& message) override {
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }
};

int main() {
    auto subject = std::make_shared<ConcreteSubject>();

    auto obs1 = std::make_shared<ConcreteObserver>("Observer1");
    auto obs2 = std::make_shared<ConcreteObserver>("Observer2");

    subject->attach(obs1);
    subject->attach(obs2);

    subject->notify("Event 1 occurred");

    subject->detach(obs1);

    subject->notify("Event 2 occurred");

    return 0;
}
```

​	你可以使用这样的方式来作为事件驱动框架的一个根基。

## 练习题

**天气站系统**

**要求**：设计一个天气数据发布系统，天气站（WeatherStation）是“主题”，可通知多个“观察者”显示设备（如手机、网页等）。

**功能要求**：

1. 观察者可以注册/注销。
2. 当温度或湿度变化时，所有注册观察者会收到更新并打印数据。（注：这个部分笔者的参考代码没有实现，您自己酌情思考）

**提示**：

- 使用接口 `IObserver` 表示观察者，定义如 `update(float temperature, float humidity)`；
- 主题接口 `ISubject` 需要支持 `registerObserver()`、`removeObserver()`、`notifyObservers()`；
- 可以实现两个观察者类 `PhoneDisplay` 和 `WebDisplay`。

> [modern-cpp-patterns-playground/Observer/WeatherForecast at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/Observer/WeatherForecast)