# 从C++编程入手设计模式

## 在这之前，为什么要有设计模式

​	Design Pattern是一个非常贴近工程化的一个议题，我们首先再开始之前（尽管有一些朋友可能已经早早就掌握了设计模式，但是出于看乐子的心态还是进来看看我写的有多烂（x）），最好还是对我们讨论的对象存在一个基础的认知是比较好的。

​	我相信任何一个初学编程的朋友都遇到这个苦恼。跟其他人协作的时候，都遇到过代码写的乱七八糟（即：可修改性差，可维护性差，可扩展性差）的严重问题。当我们增加新的需求的时候，我们会面临代码混杂等若干棘手的问题。这就像是一个人盖房子，地基不牢，只能在上面打补丁——越修越没法看！最后只会再新的需求中轰然倒塌。如果我们以开始就像架构师一样，设计好一个最基本的框架，在编程的思考与实践中完善我们的框架。我们虽然可能还是无法回避史山，但是至少对于小的递增性需求，仍然游刃有余不慌不忙的扩展我们的代码。换而言之——**我们希望采用一个符合被抽象对象的实际的抽象，从而自然的完成我们的编程。**设计模式就是想要解决这个问题。

​	设计模式被视为前人经验的结晶，是解决常见设计问题的典范方案。它们不仅提升了代码的质量和可维护性，还促进了开发团队之间的协作与沟通。换而言之，他是开发团队对一个子模块的抽象方式的共同认识，大家都遵守这样的框架抽象增添修改删除代码。这样至少不会太乱。自然，这种宽泛的说法不会落实到具体的代码实现，**设计模式自身就是为了解决一类场景问题而不是特定问题而存在的，我们学习设计模式就是使用我们选择的设计模式的基本范式解决我们眼下的问题。**（使用方法论解决我们的问题）

​	设计模式说到这里，就要聊聊它包含什么了，大伙看一眼即可，**知道设计模式有什么就行！**

1. **模式名称**：每个设计模式都有一个简洁的名称，便于开发人员之间的交流和讨论。
2. **问题描述**：明确指出在特定上下文中需要解决的问题。
3. **解决方案**：提供一个通用的设计结构，用于解决上述问题。
4. **效果**：描述应用该模式后可能产生的结果，包括优点和可能的副作用。

​	设计模式也存在一定的分类，我们就是按照这个大纲一步一步的解决我们的问题：

1. **创建型模式**：关注对象的创建过程，旨在以适当的方式创建对象。例如：单例模式、工厂方法模式、抽象工厂模式、建造者模式和原型模式。
2. **结构型模式**：关注类和对象的组合，旨在实现更大的结构。例如：适配器模式、桥接模式、装饰器模式、组合模式和代理模式。
3. **行为型模式**：关注对象之间的通信和职责分配。例如：观察者模式、策略模式、命令模式、状态模式和责任链模式。

​	嗯，枯燥的概念，没关系，我们会一步一步学习具体的设计模式，然后慢慢理解他们的！

## 单例模式

​	单例模式是这样的一个模式，它实际上声明了我们的模块中全局应当**有且只有（`Have And Only Have one`）**一个的对象。举个例子，对于日志薄记系统，我们一个模块或者甚至一个系统，只应该有一个实际的日志登记对象，而不是生成一大堆日志对象混乱的向文件/标准输出输出纷杂的内容。亦或者我们需要有一个全局的配置管理器，不应当存在第二个导致两个对象配置不一致造成系统状态的不确定性（你也不想看着一个配置叫你刹车另一个配置叫你这个时候踩油门吧！）

> 当我们希望全局对象唯一的时候，这个对象就应该被设计为一个单例（单例模式的设计对象），单例的访问需要使用一个接口：全局访问点来获取该实例。

​	说了半天，无非就是两个重要的点：

1. **确保一个类只有一个实例**：通过限制类的实例化过程，防止外部创建多个实例。
2. **提供一个全局访问点**：通过一个静态方法或属性，使得其他对象可以访问该唯一实例。

这种模式适用于需要全局共享资源的场景，如配置管理器、日志记录器、数据库连接池等。

### 使用C++实现的时候，我们需要注意的内容

#### 1. **私有化构造函数**：防止外部通过 `new` 操作符创建多个实例。

​	我们需要把创建的构造函数放置到我们的私有函数部分，让我们信任的接口吐出来我们的对象访问指针。这就是把我们的Singleton放置到我们的private区域上，这样我们就没办法肆意的显示或者是隐式（这个最重要，C++喜欢自己偷摸干点事情让代码跑起来）

#### 2. **提供静态方法获取实例**：例如 `getInstance()` 方法，用于返回唯一的实例。

​	我们上面把构造函数藏了起来，但是我们的确需要访问单例，这要咋办呢？答案是让我们信任的接口吐出来我们的对象访问指针。这里的`getInstance()`只是一个指代，你像我就会使用`instance()`这个名称。

#### 3. **确保线程安全**：在多线程环境下，确保不会创建多个实例。

​	这个议题跟并发编程交叉，我们不希望在初始化的时候，因为数据竞争的问题导致重复多次的创建。举个例子：

```c++
if(!instance){
	// create this	
	instance = new Instance();
}
```

对于线程一和线程二，有如下的进程视图

```
!instance	<- 	|	!instance <-
do_create		|	do_create
```

​	在外面的线程一刚判断完准备执行do_create的汇编代码的时候，立马被CPU甩开给了线程二，这个时候线程二创建好了之后，恢复线程一的执行就会出现第二次创建（他已经过了判断了！）

​	这个时候上锁就是一个正确的抉择，这是我们后面谈论的——双重上锁机制。

### 一些经典的实现

​	饿汉和懒汉单例是我们常见的讨论的实现区别，虽然这两个名称被取出来我认为纯粹闲得慌。实际上就是说明——我们的单例是何使创建的。是类存在的时候，咱们就开始加载类呢（饿汉单例）？还是delay until we use呢？（懒汉单例）

#### **饿汉式（Eager Initialization）**

在类加载时就创建实例，线程安全，但可能导致资源浪费。

```cpp
class Singleton {
private:
    static Singleton instance;
    Singleton() {}
public:
    static Singleton& getInstance() {
        return instance;
    }
};
// 放私有文件隔离
Singleton Singleton::instance;
```

#### **懒汉式（Lazy Initialization）**

在首次使用时创建实例，需注意线程安全问题。

```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}
public:
    // 有问题！
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;
```

​	这个问题是我上面已经谈论过的为什么不安全的问题，忘记的bro自己翻上去看两眼

#### 改进版本（双重检查锁定（Double-Checked Locking））

```cpp
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;
    Singleton() {}
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;
```

​	你可以看到这样我们就把事情解决了，思考一下为什么？

> 1. **第一次检查（无锁）**：
>    `if (instance == nullptr)` 在加锁前快速判断实例是否已存在。若已存在，直接返回，避免不必要的锁竞争，提升性能。
> 2. **加锁保护**：
>    当实例未初始化时，通过 `std::lock_guard` 对互斥量 `mtx` 加锁，确保同一时间只有一个线程能进入临界区，防止多个线程同时创建实例。
> 3. **第二次检查（有锁）**：
>    在锁内再次检查 `instance == nullptr`，防止其他线程在第一次检查后、加锁前已经完成了实例化（避免重复创建）。
> 4. **内存安全**：
>    `std::mutex` 和 `std::lock_guard` 保证了 `new Singleton()` 的原子性，确保实例指针的赋值操作对其他线程可见，避免未初始化或部分初始化的对象被访问。

#### C++11以上的朋友们有福了：static一招击杀

利用 C++11 的特性，线程安全且简洁。

```cpp
class Singleton {
private:
    Singleton() {}
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};
```

------

### 优缺点一览

#### *优点：*

- **节省资源**：避免重复创建对象，节省系统资源。
- **全局访问**：提供一个全局访问点，方便管理。

#### *缺点：*

- **隐藏的全局状态**：可能导致代码难以测试和维护。
- **并发问题**：在多线程环境下，需确保线程安全。
- **生命周期管理**：在某些语言中，单例的销毁需要特别处理。

## 上coding

​	我们现在就来看一个笔者自己写的例子。这个是题目，你可以自己先试试？

**题目一：实现一个线程安全的懒汉式单例**

请使用 C++20 的特性，实现一个线程安全的懒汉式（懒加载）单例类 `Logger`。要求如下：

1. 类中包含一个 `void log(const std::string& message)` 函数，用于将日志打印到终端。
2. 单例对象要在第一次调用 `getInstance` 时创建，并保证多线程安全。
3. 禁止拷贝和移动构造。

**示例接口：**

```c++
class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& message);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
};
```

你只需要完成类的定义与实现部分，并编写一个 main 函数示例（单线程或多线程均可）来测试它。

### 看看笔者的实现

> Note：笔者的实现肯定不是最优的，也许会存在其他问题，请各位看官如果发现了任何问题，请严肃的提Issue or PR，我会深入同您探讨，共同进步！

```c++
#pragma once
#include <mutex>
#include <string>
class SimpleLogger {
public:
	/**
	 * @brief instance make the query of getting instances
	 *
	 * @return SimpleLogger& instance ref itself
	 */
	static SimpleLogger& instance();
	/**
	 * @brief log messages
	 *
	 * @param message message to log
	 */
	void log_messages(const std::string& message);

private:
	SimpleLogger();
	~SimpleLogger() = default;
	/* Logger is nether copiable and movable */
	SimpleLogger& operator=(const SimpleLogger&) = delete;
	SimpleLogger(const SimpleLogger&) = delete;
	SimpleLogger(SimpleLogger&&) = delete;
	SimpleLogger& operator=(SimpleLogger&&) = delete;
};
```

​	你可以看到笔者把我们的任何构造都放到了私有区域上，防止我们犯傻，创建了不该创建的东西，所有的实例接口都是使用`static SimpleLogger& instance();`这个静态接口进行访问。

​	`log_messages`是作为一个类正常工作的实例表达的，实际上你可以换成你自己的东西。

​	C++11开始，使用static初始化足以保证我们的线程安全的做初始化了

```c++
#include "logger.h"
#include <print>

SimpleLogger::SimpleLogger() {
	std::println("[logger: ] Logger init invoke once");
}

SimpleLogger& SimpleLogger::instance() {
	static SimpleLogger simpleLogger; // only init once
	return simpleLogger;
}

void SimpleLogger::log_messages(const std::string& message) {
	std::println("[logger: ] {}", message);
}
```

#### 测试一下？

​	这是笔者的测试文件：

```c++
#include "logger.h"
#include <string>
#include <thread>
#include <vector>
static constexpr unsigned int TEST_TIME = 50;

void test_functions(const std::string messages) {
	auto& logger_instance = SimpleLogger::instance();
	logger_instance.log_messages(messages);
}

int main() {
	std::vector<std::thread> test_threads;
	for (int i = 0; i < TEST_TIME; i++) {
		std::string result = "Hello from Times: " + std::to_string(i);
		test_threads.emplace_back(test_functions, result);
	}
	for (auto& each : test_threads) {
		each.join();
	}
}
```

```
[charliechen@Charliechen build]$ ./logger 
[logger: ] Logger init invoke once
[logger: ] Hello from Times: 0
[logger: ] Hello from Times: 1
...
[logger: ] Hello from Times: 47
[logger: ] Hello from Times: 48
[logger: ] Hello from Times: 49
```

> 实现代码：[My Implementations](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/Singleton/Logger)

## 习题

​	虽然我没这个能力和胆子随意出题，但是下面这个例题还是相当经典的：

### **配置管理器**

设计一个 `ConfigManager` 类，使用单例模式来管理配置文件。要求如下：

1. `ConfigManager` 负责从配置文件（可假设配置文件叫做 `config.txt`）读取配置项（每行一个键值对，如：`key=value`），并能返回对应的值。
2. 提供 `std::optional<std::string> getValue(const std::string& key)` 接口，返回配置项的值（如果有的话）。
3. 使用现代 C++20（如 `std::unordered_map`, `std::string_view`, `std::optional`）来简化实现。
4. 文件读取可简单处理（例如固定几行内容模拟文件读入即可）。

> 笔者也有实现：[My Implementations](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/Singleton/GlobalConfig)

# Reference

[设计模式 (计算机) - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/设计模式_(计算机))