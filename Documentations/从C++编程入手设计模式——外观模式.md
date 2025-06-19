# 从C++编程入手设计模式——外观模式

## 前言

​	笔者最近疲惫于期末考试，这里挤一点牙膏更新一下设计模式的内容。

## 外观模式

​	同志们都接触过庞大的史山代码，都知道修改史山是我们经常遇到的需求之一。不过好在，大部分复杂系统想要跑通，基本的架构分层还是要有的。这也就意味着，我们对于新的需求，可以重新组装下层的模块，相互之间新的协调可以组成一个新的良好的工作的系统，我们是不需要重新专门为新需求大幅度的重写代码，这是笔者认为外观模式一个重要的功能。

​	另一方面，外观模式中一个比较重要的一点（或者说，更加现实中）的是,对于复杂的子系统我们只知道子系统可以确保的完成给定的子任务，我们希望将这些功能组合起来的时候，就直接将子系统进行有机的组合，或者说，限制客户程序员按照随意的方式调度子系统的工作（或者说，按照规范的方式对子系统进行操作）

```c++
#include <iostream>

class SubsystemA {
public:
    void operationA() {
        std::println("Subsystem A operation\n");
    }
};

class SubsystemB {
public:
    void operationB() {
        std::println("Subsystem B operation\n");
    }
};

class Facade {
public:
    void operation() {
        a.operationA();
        b.operationB();
    }

private:
    SubsystemA a;
    SubsystemB b;
};
```

​	如你所见，假设我们的A，B子系统存在先后调度的顺序要求的时候，我们就是用这个办法来进行封装，此时此刻，我们就可以把SubsystemA和SubsystemB藏到私有文件中，不可见，我们只公开Facade类，这样，我们就能将复杂的子系统协作给覆盖掉，取而代之简单的接口。

​	这个模式在实际开发中非常常见，特别是在需要与多个模块交互的时候，比如启动一个操作系统、打开一个媒体播放器、处理一个网络请求等。凡是存在目标调用顺序或者特定的私有协作方式的时候，就需要使用这个办法来屏蔽具体的实现细节。

### 举个例子：家庭影院

想象你有一个智能家庭影院系统，里面包含了以下几个设备：

- 灯光控制器
- DVD 播放器
- 音响系统
- 投影仪

如果你想要看一场电影，你可能要做很多步骤：先关灯，再打开投影仪，接着打开音响和 DVD 机。这些操作本身很简单，但流程琐碎。

如果我们为这些设备写一个“统一的控制器”，只需要调用一个 `watchMovie()` 方法，就能自动完成这些流程，是不是更方便了？

这就是外观模式的用武之地。这个内容留作练习。笔者已经放到Github上了

> [Charliechen114514/modern-cpp-patterns-playground: 🚀 A modern C++20+ practice repository showcasing classic design patterns such as Singleton, Factory, and more](https://github.com/Charliechen114514/modern-cpp-patterns-playground)

## 外观模式的适用场景

这个模式非常适合用在以下几种情况：

- 子系统非常复杂，调用方只需要常用的一些功能。
- 我们希望对子系统进行分层，把系统的使用者和内部实现解耦。
- 我们希望在不修改子系统代码的情况下，简化它的使用方式。

​	就是这样的！