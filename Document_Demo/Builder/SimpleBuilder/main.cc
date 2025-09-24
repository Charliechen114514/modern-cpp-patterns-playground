#include "./Task.h"
#include <iostream>

int main() {
	try {
		// Using the builder to create a new Task object.
		auto myTask = TaskBuilder()
		                  .withPriority(Task::Priority::High)
		                  .withDdl({ 2025, 9, 25, 10, 0, 0 })
		                  .withDescription("Complete the final project report.")
		                  .withTitle("Project Report")
		                  .withDetails("Check all data points and finalize the conclusion.")
		                  .build();

		// Accessing the properties of the built task.
		std::cout << "Task built successfully!" << std::endl;
		std::cout << "Task Description: " << myTask.dump_formated_task() << std::endl;

		// Trying to build a task without all required properties to show error handling.
		auto invalidTask = TaskBuilder()
		                       .withDescription("This will fail.")
		                       .build();

	} catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}