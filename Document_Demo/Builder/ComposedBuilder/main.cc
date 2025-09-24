// main.cc
#include "./Task.h"
#include <iostream>

int main() {
	try {
		auto myTask = Task::builder()
		                  .mainBuilder()
		                  .withPriority(Task::Priority::High)
		                  .withDdl({ 2025, 9, 25, 10, 0, 0 })
		                  .withDescription("Complete the final project report.")
		                  .doneMain()
		                  .optional()
		                  .withTitle("Project Report")
		                  .withDetails("Check all data points and finalize the conclusion.")
		                  .doneOptional()
		                  .build();

		std::cout << "Task built successfully!" << std::endl;
		std::cout << "Task Description: " << myTask.dump_formated_task() << std::endl;

		// 尝试构造一个缺少必填属性的 Task，看看异常是否被抛出
		auto invalidTask = Task::builder()
		                       .mainBuilder()
		                       // 不设 priority 或 ddl
		                       .withDescription("This will fail.")
		                       .doneMain()
		                       .build();

	} catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
