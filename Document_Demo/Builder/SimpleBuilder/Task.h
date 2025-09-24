#include <print>
#include <string>
class Task {
public:
	friend class TaskBuilder;
	struct CTime {
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;

		// Constructor that matches the format: {year, month, day, hour, minute, second}
		CTime(int y, int m, int d, int h, int min, int s);

		// A simple method to dump the time for verification
		virtual std::string dumpTimeString() const;
		// current time
		static CTime now();
		std::string to_string() const {
			return std::format("{}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}", year, month, day, hour, minute, second);
		}
		// frient operator
		friend bool operator>(const CTime& t1, const CTime& t2);
	};

	enum class Priority {
		Immediate,
		High,
		Medium,
		Low
	};

private: // Making member variables private is a best practice for encapsulation
	// ---------- Must Valid before the Exsitance of Task
	Priority priority;
	CTime ddl;
	std::string taskDescription;
	// ---------- Must Valid before the Exsitance of Task End

	// ---------- Can be configured later by setters and accessed by getter
	std::string taskTitle;
	std::string details;
	// ---------- Can be configured later by setters and accessed by getter End

public:
	// Constructor to initialize the "Must Valid" members
	Task(Priority p, CTime d, const std::string& desc)
	    : priority(p)
	    , ddl(d)
	    , taskDescription(desc) {
	}

	std::string dump_formated_task() const;

	// Getters for all members
	Priority getPriority() const {
		return priority;
	}

	CTime getDdl() const {
		return ddl;
	}

	const std::string& getTaskDescription() const {
		return taskDescription;
	}

	const std::string& getTaskTitle() const {
		return taskTitle;
	}

	const std::string& getDetails() const {
		return details;
	}

	// Setters for members that can be configured later
	void setTaskTitle(const std::string& title) {
		taskTitle = title;
	}

	void setDetails(const std::string& d) {
		details = d;
	}
};

// The TaskBuilder class that encapsulates the construction logic.
class TaskBuilder {
public:
	TaskBuilder() = default;

	TaskBuilder& withPriority(Task::Priority p) {
		m_priority = p;
		return *this;
	}

	TaskBuilder& withDdl(const Task::CTime& d) {
		m_ddl = d;
		return *this;
	}

	TaskBuilder& withDescription(std::string desc) {
		m_description = std::move(desc);
		return *this;
	}

	TaskBuilder& withTitle(std::string title) {
		m_title = std::move(title);
		return *this;
	}

	TaskBuilder& withDetails(std::string details) {
		m_details = std::move(details);
		return *this;
	}

	Task build() const {
		if (!m_priority || !m_ddl || !m_description) {
			throw std::runtime_error("Cannot build Task: Missing required properties.");
		}

		Task task { *m_priority, *m_ddl, *m_description };

		if (m_title) {
			task.setTaskTitle(*m_title);
		}
		if (m_details) {
			task.setDetails(*m_details);
		}

		return task; // RVO
	}

private:
	// Musts
	std::optional<Task::Priority> m_priority;
	std::optional<Task::CTime> m_ddl;
	std::optional<std::string> m_description;

	// Options
	std::optional<std::string> m_title;
	std::optional<std::string> m_details;
};