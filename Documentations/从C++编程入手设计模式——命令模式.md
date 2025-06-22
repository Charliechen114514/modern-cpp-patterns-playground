# 从C++编程入手设计模式——命令模式

​	命令模式是一个用指令封装请求的优雅方法。换而言之，对于一个复杂的系统，当我们发现，使用一系列的指令（Command）来操作对象的时候，这个设计模式就会显得非常的实用。我们经常遇到这样的场景：用户点击一个按钮，希望执行某个操作，比如保存文件、删除一条记录、或撤销上一步操作。我们通常会写一段代码来直接响应这个按钮事件。然而，如果我们希望这个操作是可以记录、撤销、重做，甚至延迟执行的，传统的方式就变得笨拙而混乱。

​	这个时候，命令模式（Command Pattern）就派上用场了。它的核心思想很简单：把每一个操作封装成一个对象。这样，我们就可以把操作当作数据一样存储、传递、撤销甚至组合。命令模式中通常有几个角色：命令对象（Command）、接收者（Receiver）、调用者（Invoker）和客户端。命令对象负责封装“做什么”；接收者是实际干活的人；调用者是触发命令的人；客户端负责把它们组合在一起。

​	我们可以想象一个遥控器控制家电的例子。电灯是接收者，它有开和关的功能；开灯命令和关灯命令是命令对象；遥控器就是调用者，它保存着按钮和命令的映射；用户就是客户端，负责把命令装进遥控器并按下按钮。

```c++
#include <iostream>
#include <memory>
#include <vector>

// 命令接口
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

// 接收者
class Receiver {
public:
    void action() {
        std::cout << "Receiver: Executing action.\n";
    }
};

// 具体命令
class ConcreteCommand : public Command {
private:
    std::shared_ptr<Receiver> receiver;
public:
    explicit ConcreteCommand(std::shared_ptr<Receiver> r) : receiver(std::move(r)) {}
    void execute() override {
        receiver->action();
    }
};

// 调用者
class Invoker {
private:
    std::vector<std::shared_ptr<Command>> commandQueue;
public:
    void addCommand(std::shared_ptr<Command> cmd) {
        commandQueue.push_back(std::move(cmd));
    }

    void run() {
        for (const auto& cmd : commandQueue) {
            cmd->execute();
        }
        commandQueue.clear();
    }
};

int main() {
    auto receiver = std::make_shared<Receiver>();
    auto command = std::make_shared<ConcreteCommand>(receiver);
    Invoker invoker;
    invoker.addCommand(command);
    invoker.run();
    return 0;
}
```

​	如你所见，这个就是常见的命令模式的模板代码。

## 优缺点讨论

命令模式的一个好处是，它实现了调用者和接收者之间的彻底解耦。调用者并不知道命令怎么执行，它只知道有个命令对象可以被触发。这使得我们可以在不改变调用者的前提下，轻松替换命令，甚至在运行时动态改变行为。

此外，命令模式还为我们带来了其他附加功能。比如，可以将命令记录到列表中，支持撤销和重做；可以组合多个命令形成宏命令，实现批量操作；可以把命令序列化之后发到远程服务器执行，实现远程控制。

不过命令模式也有它的代价。每个操作都要定义一个命令类，当操作很多时，类的数量会迅速增加。此外，为了支持撤销，命令对象还需要记录足够的信息，这可能会带来额外的内存负担。

## 练习题：通过命令控制文本编辑器

**描述**：
 模拟一个文本编辑器，用户可以执行“添加文字”、“删除文字”等操作，每个操作为一个命令。

**要求**：

- 接收者 `TextDocument`，支持添加和删除字符
- 命令：`AddTextCommand`, `DeleteTextCommand`
- 支持撤销操作
- Invoker 为 `EditorInvoker`，负责管理执行历史

> [modern-cpp-patterns-playground/Command/TextEditor at main · Charliechen114514/modern-cpp-patterns-playground](https://github.com/Charliechen114514/modern-cpp-patterns-playground/tree/main/Command/TextEditor)