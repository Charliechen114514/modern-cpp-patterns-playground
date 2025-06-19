# 从C++编程入手设计模式——策略设计模式

​	在我们平时写程序的过程中，经常会遇到这样的情况：一个对象的某个功能可以有多种实现方式，而且可能会根据不同的场景切换这些方式。比如一只动物可以发出不同的叫声，一个排序器可以使用不同的排序算法，一个支付系统可以接入不同的支付平台。这时候，我们就可以使用“策略设计模式”。

​	策略策略，实际上就是做一个事情的策略方法。换而言之，这个设计模式用在哪些应付解决方案多变的场景。我们把某个行为（比如“怎么叫”“怎么排序”“怎么支付”）封装成一个独立的策略对象，让原本需要执行这个行为的类把这个行为委托给策略对象来完成。这样，我们可以很方便地替换行为、扩展行为，而不需要修改原来的类。

```c++
#include <iostream>
#include <functional>

class Context {
public:
    void setStrategy(std::function<void()> strat) {
        strategy = strat;
    }

    void executeStrategy() {
        if (strategy) {
            strategy();
        }
    }

private:
    std::function<void()> strategy;
};
```

​	如你所见，这就是把我们具体的实现行为替换成给定接口的函数指针。

## 策略模式的结构

从设计的角度来看，策略模式通常包含三部分：

1. **策略接口：定义某个行为的抽象，比如“排序算法”或“支付方式”。**
2. **具体策略：不同的实现，比如“冒泡排序”、“支付宝支付”。**
3. **上下文类：也就是使用这些策略的地方，内部持有一个策略接口的对象，通过它来执行行为。**

------

## 什么场景适合用策略模式

- 有多个算法可以选择，比如不同的排序方法、路径规划算法等。
- 行为需要根据不同条件动态变化，比如不同平台上的绘图方式。
- 不同业务场景下执行逻辑不同，比如不同国家的税率计算方式。

------

## 和 if-else 的区别在哪？

很多人会说：“我直接写一堆 `if-else` 或 `switch` 不也可以吗？”确实可以，但这样做有两个问题：

- 每增加一种新行为就要改动原来的代码，不利于维护。
- 所有实现都混在一起，导致类越来越臃肿，不利于阅读和测试。

而使用策略模式，每个行为单独封装起来，不但代码更清晰，还能独立测试每一个策略实现。

## 一个例子

**需求**：设计一个动物模拟器，支持不同动物发出不同的叫声。使用策略模式实现动物叫声的可变换（例如狗叫 "汪汪"，猫叫 "喵喵"）。

**要求**：

- 定义 `ISoundStrategy` 接口，有一个 `makeSound()` 函数。
- 实现 `DogSoundStrategy`、`CatSoundStrategy` 等具体策略类。
- 定义 `Animal` 类，持有一个 `ISoundStrategy*`。
- 允许运行时更换动物的叫声策略。

**示例输出**：

```
Dog: 汪汪
Cat: 喵喵
Dog changes to cat sound: 喵喵
```

> 笔者没有严格的实现这个题目的要求，但是您可以参考一下：
>
> [modern-cpp-patterns-playground/Strategy/AnimalSound at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/Strategy/AnimalSound)