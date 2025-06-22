# 从C++编程入手设计模式——责任链模式

​	当我们的一个请求需要多个对象去处理，但具体由谁来处理，是根据情况动态决定的。例如，一个日志系统中，可能希望把错误信息写入文件，把提示信息输出到控制台，而不是每个消息都写到所有地方。再比如，用户输入的表单需要经过多个字段的验证，每个验证器处理一项，验证失败就可以中断。

​	面对这些问题，我们希望有一种方式，让多个处理者自动接力，把请求传下去，直到有人愿意接住它，或者最终没人处理。这个思路就是“责任链模式”。

​	责任链模式的核心思想是：**将多个处理者连接成一条链，每个处理者有机会处理请求，如果不能处理就交给下一个**。使用这个模式可以做到请求发送者和处理者之间的解耦，不需要写死“谁来处理”这件事。

​	责任链的结构非常简单，处理器之间形成一个链条：

```
[ 请求 ]
   ↓
[Handler1]───→[Handler2]───→[Handler3]
   ↑              ↑              ↑
   │ 判断是否处理  │ 判断是否处理  │ 判断是否处理
```

​	每个 Handler 有机会决定是否处理当前请求。如果处理就完成了；如果不处理，就把请求传递给下一个 Handler。

​	在代码模板上，看起来就是这样的：

```cpp
#include <iostream>
#include <memory>
#include <string>

// 抽象处理者
class Handler {
protected:
    std::shared_ptr<Handler> next_;
public:
    virtual ~Handler() = default;
    void setNext(std::shared_ptr<Handler> next) {
        next_ = std::move(next);
    }
    virtual void handle(const std::string& request) {
        if (next_) {
            next_->handle(request);
        }
    }
};

// 具体处理者A
class ConcreteHandlerA : public Handler {
public:
    void handle(const std::string& request) override {
        if (request == "A") {
            std::cout << "ConcreteHandlerA handled request: " << request << '\n';
        } else {
            Handler::handle(request);
        }
    }
};

// 具体处理者B
class ConcreteHandlerB : public Handler {
public:
    void handle(const std::string& request) override {
        if (request == "B") {
            std::cout << "ConcreteHandlerB handled request: " << request << '\n';
        } else {
            Handler::handle(request);
        }
    }
};

int main() {
    auto handlerA = std::make_shared<ConcreteHandlerA>();
    auto handlerB = std::make_shared<ConcreteHandlerB>();
    handlerA->setNext(handlerB);

    handlerA->handle("A");
    handlerA->handle("B");
    handlerA->handle("C");

    return 0;
}
```

​	或者这里有一个看起来更加具体的版本：

```cpp
#include <iostream>
#include <memory>
#include <string>

struct Message {
	enum Type {
		INFO,
		WARNING,
		ERROR
	};

	Type type;
	std::string content;

	Message(Type t, std::string c)
	    : type(t), content(std::move(c)) {}
};

// 抽象处理器
struct Handler {
	std::shared_ptr<Handler> next;

	void setNext(std::shared_ptr<Handler> n) {
		next = n;
	}

	void handle(const Message& msg) {
		if (canHandle(msg)) {
			process(msg);
		} else if (next) {
			next->handle(msg);
		}
	}

	virtual ~Handler() = default;

protected:
	virtual bool canHandle(const Message& msg) = 0;
	virtual void process(const Message& msg) = 0;
};

// 文件处理器
struct FileLogger : Handler {
protected:
	bool canHandle(const Message& msg) override {
		return msg.type == Message::ERROR;
	}
	void process(const Message& msg) override {
		std::cout << "[File] " << msg.content << '\n';
	}
};

// 控制台处理器
struct ConsoleLogger : Handler {
protected:
	bool canHandle(const Message& msg) override {
		return msg.type == Message::INFO;
	}
	void process(const Message& msg) override {
		std::cout << "[Console] " << msg.content << '\n';
	}
};

// 弹窗处理器
struct GuiLogger : Handler {
protected:
	bool canHandle(const Message& msg) override {
		return msg.type == Message::WARNING;
	}
	void process(const Message& msg) override {
		std::cout << "[Popup] " << msg.content << '\n';
	}
};
```

### 实际应用场景

责任链模式并不仅限于日志处理，它在以下场景中也非常常见：

- 表单字段校验（每个字段一个处理器）
- 网络请求拦截器（认证、权限、压缩等）
- 中间件系统（如 Web 框架中的中间件链）
- 命令解释器或事件分发器

它的强大之处在于：**每一个节点都可以自行决定是否处理、是否继续传递**，这为灵活的处理流程提供了极大的自由度。

### 与其他设计模式的对比

**责任链模式**与某些模式在结构上可能相似，但其意图和应用方式有明显不同。

#### **与策略模式的区别：**

 策略模式侧重于“选择一个方案”，它要求用户明确设置当前使用哪一个策略。而责任链模式强调“顺序处理、传递判断”，调用者通常不关心由谁处理，处理者也可不止一个。策略是点选一个方案，责任链是顺着链找合适的方案。

#### **与装饰器模式的区别：**

 装饰器模式是“增强已有功能”，它强调在不修改原有对象的基础上添加附加行为；而责任链模式更像“责任传递”，强调每个处理器只处理自己关心的部分，然后把任务交出去。两者都用了链式结构，但目的不同。

#### **与观察者模式的区别：**

 观察者模式是“一对多”的事件广播，所有订阅者都能收到通知；而责任链是“一对一逐步传递”，请求只有一个接收者（或多个逐步处理者），而且是按顺序决定。

------

### 责任链的变体设计

虽然标准的责任链模式是单向串联、一次只处理一个处理器，但在实际应用中，可以根据业务需要进行一些“变体”设计。

**1. 所有处理器都参与处理**
 默认责任链遇到能处理的就停止传递，但有时我们希望**每个处理器都能处理自己的部分**，不影响后续。例如，在一个网页渲染系统中，每个处理器可以对页面对象做一定处理，最终效果是叠加的。

这时候我们可以取消 `if...else` 的限制，统一调用 `handle()`，不提前终止。

**2. 动态重排链条顺序**
 有些场景下，我们希望链的顺序可以动态调整，比如根据配置文件加载不同顺序的处理器、按优先级排序等。这时候链条的构造阶段就变得非常重要，链不再是硬编码。

**3. 支持回溯或逆向传递**
 有些业务希望在“正向处理”结束后，再做一次“逆向清理”或“结果回传”。比如在中间件系统中，请求是从前往后传递，响应是从后往前传递的。这种双向链的设计可以在责任链上加一个“after”阶段。

## 练习题：设计一个按日志类型分类的责任链处理系统

**题目描述：**
 请设计一个日志处理系统，它能够根据日志的类型选择合适的处理方式进行输出。系统中包含三种日志类型：

- `DISK`：需要写入磁盘
- `CONSOLE`：需要输出到控制台
- `GUI_SCREEN`：需要在图形界面上显示

每种日志类型应该由专门的处理器进行处理，系统应当自动根据日志类型选择合适的处理器完成输出。

**要求：**

1. 定义一个 `Message` 结构体，表示一条日志信息，应包含日志类型（枚举）和内容。
2. 定义一个抽象基类 `Handler`，表示日志处理器。该类应包含判断能否处理当前日志的方法 `canAccept`，和实际处理日志的方法 `processSessions`。
3. 实现三个具体的处理器类：`DiskHandler`, `ConsoleHandler`, `GuiHandler`，它们分别处理各自类型的日志。
4. 创建一个 `HandlerChain` 类，作为责任链的管理者，负责按顺序传递日志给合适的处理器。
5. 要求每条日志只由能够处理它的处理器执行一次，不可重复处理。
6. 使用 C++ 标准库中的 `std::list` 或类似结构管理处理器链条。
7. 使用 `std::println`（C++23）输出日志内容，格式如：
    `From Console: some info`
    `From Disk: critical error`

**拓展选做：**

- 支持动态添加处理器。
- 如果没有合适的处理器，输出 `"No handler for message type"`。
- 保证处理器的析构为虚函数。

> [modern-cpp-patterns-playground/ResponsibilityChain/OutputHandler at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/ResponsibilityChain/OutputHandler)